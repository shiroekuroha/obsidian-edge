#include "engine/core/application/window.h"

#ifdef OE_PLATFORM_WINDOWS
#include "engine/core/platform/window_windows.h"
#elif OE_PLATFORM_LINUX
#include "engine/core/platform/window_linux.h"
#endif

namespace ObsidianEdge {
static bool s_glfwInitialized = false;

void setGLFWInitialized(bool init) { s_glfwInitialized = init; }

bool isGLFWInitialized() { return s_glfwInitialized; }

static void glfwErrorCallback(int error, const char *msg){
    OE_CORE_ERROR("GLFW Error (code {0}): \"{1}\"", error, msg)}

Window::Window(const WindowProps &props) {
    m_data.title = props.title;
    m_data.width = props.width;
    m_data.height = props.height;

    OE_CORE_INFO(
        "Creating Window, Title: {0}, w: {1}, h: {2}",
        m_data.title, m_data.width, m_data.height)

    if (!isGLFWInitialized()) {
        int result = glfwInit();

        OE_CORE_ASSERT(
            result, "Failed to initialize GLFW library!")
        setGLFWInitialized(true);
    }

    m_window = glfwCreateWindow(
        (int)m_data.width, (int)m_data.height,
        m_data.title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_window);
    glfwSetWindowUserPointer(m_window, &m_data);
    setVSync(true);

    glfwSetErrorCallback(glfwErrorCallback);

    glfwSetWindowFocusCallback(
        m_window, [](GLFWwindow *window, int focus) {
            WindowData &data = *(
                WindowData *)(glfwGetWindowUserPointer(window));

            if (focus) {
                WindowGainedFocus gainedEvent;
                data.eventCallback(gainedEvent);
            } else {
                WindowLostFocus lostEvent;
                data.eventCallback(lostEvent);
            }
        });

    glfwSetWindowPosCallback(
        m_window, [](GLFWwindow *window, int xpos, int ypos) {
            WindowData &data = *(
                WindowData *)(glfwGetWindowUserPointer(window));

            WindowMoved event(xpos, ypos);
            data.eventCallback(event);
        });

    glfwSetWindowSizeCallback(
        m_window,
        [](GLFWwindow *window, int width, int height) {
            WindowData &data = *(
                WindowData *)(glfwGetWindowUserPointer(window));

            WindowResizedEvent event(width, height);
            data.eventCallback(event);
        });

    glfwSetWindowCloseCallback(
        m_window, [](GLFWwindow *window) {
            WindowData &data = *(
                WindowData *)(glfwGetWindowUserPointer(window));

            WindowClosedEvent event;
            data.eventCallback(event);
        });

    glfwSetKeyCallback(
        m_window, [](GLFWwindow *window, int key, int scancode,
                     int action, int mods) {
            WindowData &data = *(
                WindowData *)(glfwGetWindowUserPointer(window));

            KeyPressedEvent downEvent(key, 0);
            KeyReleasedEvent upEvent(key);
            KeyPressedEvent repEvent(key, 1);

            switch (action) {
                case GLFW_PRESS:
                    data.eventCallback(downEvent);
                    break;

                case GLFW_RELEASE:
                    data.eventCallback(upEvent);
                    break;

                case GLFW_REPEAT:
                    data.eventCallback(repEvent);
                    break;
            }
        });

    glfwSetMouseButtonCallback(
        m_window, [](GLFWwindow *window, int button, int action,
                     int mods) {
            WindowData &data = *(
                WindowData *)(glfwGetWindowUserPointer(window));

            MouseButtonPressedEvent downEvent(button);
            MouseButtonReleasedEvent upEvent(button);

            switch (action) {
                case GLFW_PRESS:
                    data.eventCallback(downEvent);
                    break;

                case GLFW_RELEASE:
                    data.eventCallback(upEvent);
                    break;
            }
        });

    glfwSetScrollCallback(
        m_window,
        [](GLFWwindow *window, double xoffset, double yoffset) {
            WindowData &data = *(
                WindowData *)(glfwGetWindowUserPointer(window));

            MouseScrolledEvent event(
                (float)xoffset, (float)yoffset);
            data.eventCallback(event);
        });

    glfwSetCursorPosCallback(
        m_window,
        [](GLFWwindow *window, double xpos, double ypos) {
            WindowData &data = *(
                WindowData *)(glfwGetWindowUserPointer(window));

            MouseMovedEvent event((float)xpos, (float)ypos);
            data.eventCallback(event);
        });

    OE_CORE_TRACE("Base Window Constructor!")
}

Window::~Window() {
    if (m_window) glfwDestroyWindow(m_window);

    if (isGLFWInitialized()) {
        glfwTerminate();
        setGLFWInitialized(false);
    }

    OE_CORE_TRACE("Base Window Destructor!")
}

void Window::onUpdate() {
    glfwPollEvents();
    glfwSwapBuffers(m_window);
}

uint32_t Window::getWidth() const { return m_data.width; }
uint32_t Window::getHeight() const { return m_data.height; }

void Window::setEventCallback(const EventCallbackFn &callback) {
    m_data.eventCallback = callback;
}

// Window attributes
void Window::setVSync(bool enabled) {
    if (enabled)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);

    m_data.vSync = enabled;
}

bool Window::isVSync() const { return m_data.vSync; }

Window *Window::create(const WindowProps &props) {
#ifdef OE_PLATFORM_WINDOWS
    return new WindowsWindow(props);
#elif OE_PLATFORM_LINUX
    return new LinuxWindow(props);
#else
    OE_CORE_ERROR("Unknown platform!");
    return nullptr;
#endif
}
}  // namespace ObsidianEdge