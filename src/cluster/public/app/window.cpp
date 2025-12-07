#include <pch.h>

#include "window.h"

#ifdef OE_PLATFORM_WINDOWS
#    include "platform/windows/window_windows.h"
#elif OE_PLATFORM_LINUX
#    include "platform/linux/window_linux.h"
#endif

#define CONTROLLER_AXIS_DEADZONE 0.25

namespace ObsidianEdge {
bool Window::s_glfwInitialized = false;

static void glfwErrorCallback(int error, const char *msg){OE_CORE_ERROR("GLFW Error (code {0}): {1}", error, msg)}

Window::Window(const WindowProps &props) {
    m_data.title = props.title;
    m_data.size.x = props.size.x;
    m_data.size.y = props.size.y;

    OE_CORE_INFO("Creating Window, "
                 "Title: {0}, w: {1}, "
                 "h: {2}",
                 m_data.title, m_data.size.x, m_data.size.y)

    if (!s_glfwInitialized) {
        int result = glfwInit();

        OE_CORE_ASSERT(result, "Failed to initialize GLFW library!")
        s_glfwInitialized = true;
    }

    m_window = glfwCreateWindow((int)m_data.size.x, (int)m_data.size.y, m_data.title.c_str(), nullptr, nullptr);

    glfwMakeContextCurrent(m_window);
    glfwSetWindowUserPointer(m_window, &m_data);
    setVSync(true);
    glfwSetErrorCallback(glfwErrorCallback);

    int status = gladLoadGL(glfwGetProcAddress);
    OE_CORE_ASSERT(status, "Failed to initialize Glad library!")

    glfwSetFramebufferSizeCallback(m_window,
                                   [](GLFWwindow *window, int width, int height) { glViewport(0, 0, width, height); });

    glfwSetWindowFocusCallback(m_window, [](GLFWwindow *window, int focus) {
        auto *data = static_cast<WindowData *>(glfwGetWindowUserPointer(window));

        if (focus)
            data->eventCallback(std::shared_ptr<Event>(new WindowGainedFocusEvent));
        else
            data->eventCallback(std::shared_ptr<Event>(new WindowLostFocusEvent));
    });

    glfwSetWindowPosCallback(m_window, [](GLFWwindow *window, int xpos, int ypos) {
        auto *data = static_cast<WindowData *>(glfwGetWindowUserPointer(window));

        data->eventCallback(std::shared_ptr<Event>(new WindowMovedEvent(Vector2i(xpos, ypos))));
    });

    glfwSetWindowSizeCallback(m_window, [](GLFWwindow *window, int width, int height) {
        auto *data = static_cast<WindowData *>(glfwGetWindowUserPointer(window));

        data->eventCallback(std::shared_ptr<Event>(new WindowResizedEvent(Vector2i(width, height))));
        data->size.x = width;
        data->size.y = height;
    });

    glfwSetWindowCloseCallback(m_window, [](GLFWwindow *window) {
        auto *data = static_cast<WindowData *>(glfwGetWindowUserPointer(window));

        data->eventCallback(std::shared_ptr<Event>(new WindowClosedEvent));
    });

    glfwSetKeyCallback(m_window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
        auto *data = static_cast<WindowData *>(glfwGetWindowUserPointer(window));

        switch (action) {
        case GLFW_PRESS:
            data->eventCallback(std::shared_ptr<Event>(new KeyPressedEvent(key, mods, false)));
            break;

        case GLFW_REPEAT:
            data->eventCallback(std::shared_ptr<Event>(new KeyPressedEvent(key, mods, true)));
            break;

        case GLFW_RELEASE:
            data->eventCallback(std::shared_ptr<Event>(new KeyReleasedEvent(key, mods)));
            break;
        default:
            break;
        }
    });

    glfwSetMouseButtonCallback(m_window, [](GLFWwindow *window, int button, int action, int mods) {
        auto *data = static_cast<WindowData *>(glfwGetWindowUserPointer(window));

        switch (action) {
        case GLFW_PRESS:
            data->eventCallback(std::shared_ptr<Event>(new MouseButtonPressedEvent(button)));
            break;

        case GLFW_RELEASE:
            data->eventCallback(std::shared_ptr<Event>(new MouseButtonReleasedEvent(button)));
            break;
        default:
            break;
        }
    });

    glfwSetScrollCallback(m_window, [](GLFWwindow *window, double xoffset, double yoffset) {
        auto *data = static_cast<WindowData *>(glfwGetWindowUserPointer(window));

        data->eventCallback(std::shared_ptr<Event>(new MouseScrolledEvent(Vector2((float)xoffset, (float)yoffset))));
    });

    glfwSetCursorPosCallback(m_window, [](GLFWwindow *window, double xpos, double ypos) {
        auto *data = static_cast<WindowData *>(glfwGetWindowUserPointer(window));

        data->eventCallback(std::shared_ptr<Event>(new MouseMovedEvent(Vector2((float)xpos, (float)ypos))));
    });
}

Window::~Window() {
    if (m_window)
        glfwDestroyWindow(m_window);

    if (s_glfwInitialized) {
        glfwTerminate();
        s_glfwInitialized = false;
    }
}

void Window::update() {
    glfwPollEvents();
    glfwSwapBuffers(m_window);
}

auto Window::getWidth() const -> unsigned int { return m_data.size.x; }
auto Window::getHeight() const -> unsigned int { return m_data.size.y; }

void Window::setEventCallback(const EventCallbackFn &callback) { m_data.eventCallback = callback; }

// Window attributes
void Window::setVSync(bool enabled) {
    if (enabled)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);

    m_data.vSync = enabled;
}

auto Window::isVSync() const -> bool { return m_data.vSync; }

auto Window::create(const WindowProps &props) -> Window * {
#ifdef OE_PLATFORM_WINDOWS
    return new WindowsWindow(props);
#elif OE_PLATFORM_LINUX
    return new LinuxWindow(props);
#else
    OE_CORE_ERROR("Unknown platform!");
    return nullptr;
#endif
}

auto Window::get() -> GLFWwindow & { return *m_window; }

auto Window::getNative() -> GLFWwindow * { return m_window; }
} // namespace ObsidianEdge
