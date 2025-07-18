#include "engine/core/application/window.h"

#ifdef OE_PLATFORM_WINDOWS
#include "engine/core/platform/window_windows.h"
#elif OE_PLATFORM_LINUX
#include "engine/core/platform/window_linux.h"
#endif

namespace ObsidianEdge
{
static bool s_glfwInitialized = false;

void
setGLFWInitialized (bool init)
{
    s_glfwInitialized = init;
}

bool
isGLFWInitialized ()
{
    return s_glfwInitialized;
}

static void
glfwErrorCallback (int error, const char *msg){
    OE_CORE_ERROR ("GLFW Error (code {0}): "
                   "\"{1}\"",
                   error, msg)
}

Window::Window (const WindowProps &props)
{
    m_data.title = props.title;
    m_data.width = props.width;
    m_data.height = props.height;

    OE_CORE_INFO ("Creating Window, "
                  "Title: {0}, w: {1}, "
                  "h: {2}",
                  m_data.title, m_data.width, m_data.height)

    if (!isGLFWInitialized ())
        {
            int result = glfwInit ();

            OE_CORE_ASSERT (
                result, "Failed to initialize GLFW library!")
            setGLFWInitialized (true);

            /**
             * @brief This is for Glad, but not working right
             * now.
             *
             * int status =
             * gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
             * OE_CORE_ASSERT (status,"Failed to initialize
             * GLAD!")
             */
        }

    m_window = glfwCreateWindow (
        (int)m_data.width, (int)m_data.height,
        m_data.title.c_str (), nullptr, nullptr);

    glfwMakeContextCurrent (m_window);

    glfwSetWindowUserPointer (m_window, &m_data);

    setVSync (true);

    glfwSetErrorCallback (glfwErrorCallback);

    glfwSetWindowFocusCallback (
        m_window, [] (GLFWwindow *window, int focus) {
            WindowData &data
                = *(WindowData *)(glfwGetWindowUserPointer (
                    window));

            if (focus)
                {
                    data.eventCallback (std::shared_ptr<Event> (
                        new WindowGainedFocusEvent));
                }
            else
                {
                    data.eventCallback (std::shared_ptr<Event> (
                        new WindowLostFocusEvent));
                }
        });

    glfwSetWindowPosCallback (
        m_window, [] (GLFWwindow *window, int xpos, int ypos) {
            WindowData &data
                = *(WindowData *)(glfwGetWindowUserPointer (
                    window));

            data.eventCallback (std::shared_ptr<Event> (
                new WindowMovedEvent (xpos, ypos)));
        });

    glfwSetWindowSizeCallback (m_window, [] (GLFWwindow *window,
                                             int width,
                                             int height) {
        WindowData &data = *(
            WindowData *)(glfwGetWindowUserPointer (window));

        data.eventCallback (std::shared_ptr<Event> (
            new WindowResizedEvent (width, height)));
    });

    glfwSetWindowCloseCallback (
        m_window, [] (GLFWwindow *window) {
            WindowData &data
                = *(WindowData *)(glfwGetWindowUserPointer (
                    window));

            data.eventCallback (
                std::shared_ptr<Event> (new WindowClosedEvent));
        });

    glfwSetKeyCallback (m_window, [] (GLFWwindow *window,
                                      int key, int scancode,
                                      int action, int mods) {
        WindowData &data = *(
            WindowData *)(glfwGetWindowUserPointer (window));

        switch (action)
            {
            case GLFW_PRESS:
                data.eventCallback (std::shared_ptr<Event> (
                    new KeyPressedEvent (key, 0)));
                break;

            case GLFW_REPEAT:
                data.eventCallback (std::shared_ptr<Event> (
                    new KeyPressedEvent (key, 1)));
                break;

            case GLFW_RELEASE:
                data.eventCallback (std::shared_ptr<Event> (
                    new KeyReleasedEvent (key)));
                break;
            }
    });

    glfwSetMouseButtonCallback (
        m_window, [] (GLFWwindow *window, int button,
                      int action, int mods) {
            WindowData &data
                = *(WindowData *)(glfwGetWindowUserPointer (
                    window));

            switch (action)
                {
                case GLFW_PRESS:
                    data.eventCallback (std::shared_ptr<Event> (
                        new MouseButtonPressedEvent (button)));
                    break;

                case GLFW_RELEASE:
                    data.eventCallback (std::shared_ptr<Event> (
                        new MouseButtonReleasedEvent (button)));
                    break;
                }
        });

    glfwSetScrollCallback (m_window, [] (GLFWwindow *window,
                                         double xoffset,
                                         double yoffset) {
        WindowData &data = *(
            WindowData *)(glfwGetWindowUserPointer (window));

        data.eventCallback (
            std::shared_ptr<Event> (new MouseScrolledEvent (
                (float)xoffset, (float)yoffset)));
    });

    glfwSetCursorPosCallback (m_window, [] (GLFWwindow *window,
                                            double xpos,
                                            double ypos) {
        WindowData &data = *(
            WindowData *)(glfwGetWindowUserPointer (window));

        data.eventCallback (std::shared_ptr<Event> (
            new MouseMovedEvent ((float)xpos, (float)ypos)));
    });
}

Window::~Window ()
{
    if (m_window)
        glfwDestroyWindow (m_window);

    if (isGLFWInitialized ())
        {
            glfwTerminate ();
            setGLFWInitialized (false);
        }
}

void
Window::onUpdate ()
{
    glfwPollEvents ();
    glfwSwapBuffers (m_window);
}

uint32_t
Window::getWidth () const
{
    return m_data.width;
}
uint32_t
Window::getHeight () const
{
    return m_data.height;
}

void
Window::setEventCallback (const EventCallbackFn &callback)
{
    m_data.eventCallback = callback;
}

// Window attributes
void
Window::setVSync (bool enabled)
{
    if (enabled)
        glfwSwapInterval (1);
    else
        glfwSwapInterval (0);

    m_data.vSync = enabled;
}

bool
Window::isVSync () const
{
    return m_data.vSync;
}

Window *
Window::create (const WindowProps &props)
{
#ifdef OE_PLATFORM_WINDOWS
    return new WindowsWindow (props);
#elif OE_PLATFORM_LINUX
    return new LinuxWindow (props);
#else
    OE_CORE_ERROR ("Unknown platform!");
    return nullptr;
#endif
}
} // namespace ObsidianEdge