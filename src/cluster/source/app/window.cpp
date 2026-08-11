#include <pch.h>

#include "application/window.h"

#include "core/event/event_app.h"
#include "core/event/event_key.h"
#include "core/event/event_mouse.h"

#ifdef OE_PLATFORM_WINDOWS
#    include "platform/windows/window_windows.h"
#elif OE_PLATFORM_LINUX
#    include "platform/linux/window_linux.h"
#elif OE_PLATFORM_DARWIN
#    include "platform/mac/window_mac.h"
#endif

#define CONTROLLER_AXIS_DEADZONE 0.25

namespace ObsidianEdge {
bool Window::m_glfwInitialized = false;

static void glfwErrorCallback(int error, const char* msg) {
    OE_CORE_ERROR("GLFW Error (code {0}): {1}", error, msg);
}

Window::Window(const WindowProps& props) {
    init(props);
}

Window::~Window() {
    yeet();
}

auto Window::get() -> GLFWwindow& {
    return *m_window;
}

auto Window::getNative() -> GLFWwindow* {
    return m_window;
}

Window::operator const GLFWwindow&() const {
    return *m_window;
}

Window::operator GLFWwindow&() {
    return *m_window;
}

Window::operator const GLFWwindow*() const {
    return m_window;
}

Window::operator GLFWwindow*() {
    return m_window;
}

void Window::init(const WindowProps& props) {
    m_data.title = props.title;
    m_data.windowDimensions.x = props.windowDimensions.x;
    m_data.windowDimensions.y = props.windowDimensions.y;

    OE_CORE_INFO("Creating Window, "
                 "Title: \"{0}\", w: {1}px, "
                 "h: {2}px.",
                 m_data.title,
                 m_data.windowDimensions.x,
                 m_data.windowDimensions.y);

    if (!m_glfwInitialized) {
        int result = glfwInit();

        OE_CORE_ASSERT(result, "Failed to initialize GLFW library!");
        m_glfwInitialized = true;
    }

    m_window = glfwCreateWindow(m_data.windowDimensions.x, m_data.windowDimensions.y, m_data.title.c_str(), nullptr, nullptr);

    glfwMakeContextCurrent(m_window);
    glfwSetWindowUserPointer(m_window, &m_data);
    setVSync(true);
    glfwSetErrorCallback(glfwErrorCallback);

    int status = gladLoadGL(glfwGetProcAddress);
    OE_CORE_ASSERT(status, "Failed to initialize Glad library!");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwGetFramebufferSize(m_window, &m_data.viewportDimensions.x, &m_data.viewportDimensions.y);
    glViewport(0, 0, m_data.viewportDimensions.x, m_data.viewportDimensions.y);

    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height) -> void {
        auto* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

        glViewport(0, 0, width, height);

        data->viewportDimensions.x = width;
        data->viewportDimensions.y = height;
        data->eventCallback(std::shared_ptr<Event>(new FrameBufferResizedEvent(Point2(width, height))));
    });

    glfwSetWindowFocusCallback(m_window, [](GLFWwindow* window, int focus) -> void {
        auto* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

        if (focus) {
            data->eventCallback(std::shared_ptr<Event>(new WindowGainedFocusEvent));
        } else {
            data->eventCallback(std::shared_ptr<Event>(new WindowLostFocusEvent));
        }
    });

    glfwSetWindowPosCallback(m_window, [](GLFWwindow* window, int xpos, int ypos) -> void {
        auto* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

        data->eventCallback(std::shared_ptr<Event>(new WindowMovedEvent(Vector2i(xpos, ypos))));
    });

    glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) -> void {
        auto* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

        data->windowDimensions.x = width;
        data->windowDimensions.y = height;
        data->eventCallback(std::shared_ptr<Event>(new WindowResizedEvent(Point2(width, height))));
    });

    glfwSetWindowMaximizeCallback(m_window, [](GLFWwindow* window, int maximized) -> void {
        auto* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

        if (maximized) {
            data->eventCallback(std::shared_ptr<Event>(new WindowMaximizedEvent()));
        } else {
            data->eventCallback(std::shared_ptr<Event>(new WindowRestoredEvent()));
        }

        glfwGetWindowSize(window, &data->windowDimensions.x, &data->windowDimensions.y);
    });

    glfwSetWindowIconifyCallback(m_window, [](GLFWwindow* window, int minimized) -> void {
        auto* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

        if (minimized) {
            data->eventCallback(std::shared_ptr<Event>(new WindowMinimizedEvent()));
        } else {
            data->eventCallback(std::shared_ptr<Event>(new WindowRestoredEvent()));
        }

        glfwGetWindowSize(window, &data->windowDimensions.x, &data->windowDimensions.y);
    });

    glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) -> void {
        auto* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

        data->eventCallback(std::shared_ptr<Event>(new WindowClosedEvent));
    });

    glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) -> void {
        auto* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

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

    glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) -> void {
        auto* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

        switch (action) {
        case GLFW_PRESS:
            data->eventCallback(std::shared_ptr<Event>(new MouseButtonPressedEvent(button)));
            break;

        case GLFW_RELEASE:
            data->eventCallback(std::shared_ptr<Event>(new MouseButtonReleasedEvent(button)));
            break;

        default:
            OE_CORE_ERROR("glfwSetMouseButtonCallback, undocumented/unknow callback action");
            break;
        }
    });

    glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset) -> void {
        auto* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

        data->eventCallback(std::shared_ptr<Event>(new MouseScrolledEvent(Vector2((float)xOffset, (float)yOffset))));
    });

    glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos) -> void {
        auto* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

        data->eventCallback(std::shared_ptr<Event>(new MouseMovedEvent(Vector2((float)xpos, (float)ypos))));
    });

    glfwMakeContextCurrent(m_window);
}

void Window::yeet() {
    if (m_glfwInitialized) {
        if (m_window != nullptr) {
            glfwDestroyWindow(m_window);
        }

        glfwTerminate();
        m_glfwInitialized = false;
    }
}

void Window::update() {
    glfwPollEvents();
}

void Window::setEventCallback(const EventCallbackFn& callback) {
    m_data.eventCallback = callback;
}

auto Window::getViewportDimensions() const -> Point2 {
    return {static_cast<unsigned int>(m_data.viewportDimensions.x), static_cast<unsigned int>(m_data.viewportDimensions.y)};
}

auto Window::getWindowDimensions() const -> Point2 {
    return {static_cast<unsigned int>(m_data.windowDimensions.x), static_cast<unsigned int>(m_data.windowDimensions.y)};
}

auto Window::isVSync() const -> bool {
    return m_data.vSync;
}

void Window::setVSync(bool enabled) {
    if (enabled) {
        glfwSwapInterval(1);
    } else {
        glfwSwapInterval(0);
    }

    m_data.vSync = enabled;
}

void Window::release() {
    glfwMakeContextCurrent(nullptr);
}

void Window::acquire() {
    glfwMakeContextCurrent(m_window);
}

auto Window::create(const WindowProps& props) -> Window* {
#ifdef OE_PLATFORM_WINDOWS
    return new WindowsWindow(props);
#elif OE_PLATFORM_LINUX
    return new LinuxWindow(props);
#elif OE_PLATFORM_DARWIN
    return new MacWindow(props);
#else
    OE_CORE_ERROR("Unknown platform!");
    throw std::system_error("Unknown platform!");
#endif
}
} // namespace ObsidianEdge
