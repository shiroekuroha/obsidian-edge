#pragma once

// ! This order matters!
// clang-format off
#include "glad/gl.h"
#include "GLFW/glfw3.h"
// clang-format on

#include "engine/core/core.h"

#include "engine/core/modules/data/vector/vector2.h"
#include "engine/core/modules/data/vector/vector2i.h"
#include "engine/core/modules/event/event.h"
#include "engine/core/modules/event/event_app.h"
#include "engine/core/modules/event/event_gamepad.h"
#include "engine/core/modules/event/event_key.h"
#include "engine/core/modules/event/event_mouse.h"
#include "engine/core/modules/log/logger.h"

namespace ObsidianEdge
{
extern bool isGlfwInitialized ();

struct WindowProps
{
    std::string title;
    uint32_t width;
    uint32_t height;

    WindowProps (const std::string &title = "Obsidian Edge", uint32_t width = 1600, uint32_t height = 900)
        : title (title), width (width), height (height)
    {
    }
};

class OE_API Window
{
public:
    using EventCallbackFn = std::function<void (std::shared_ptr<Event>)>;

    Window (const WindowProps &props);
    virtual ~Window ();

    virtual void onUpdate ();

    virtual uint32_t getWidth () const;
    virtual uint32_t getHeight () const;

    virtual void setEventCallback (const EventCallbackFn &callback);
    virtual void setVSync (bool enabled);
    virtual bool isVSync () const;

    static Window *create (const WindowProps &props = WindowProps ());

    GLFWwindow &get ();
    GLFWwindow *get_ptr ();

    void refreshControllers ();
    void checkGamepadEvent ();

private:
    struct WindowData
    {
        std::string title;
        unsigned int width, height;
        bool vSync;

        EventCallbackFn eventCallback;
    };

    struct ControllerData
    {
        std::string name;
        bool present;
        unsigned char buttons[15];
    };

    GLFWwindow *m_window;
    WindowData m_data;
    ControllerData m_controllers[16] = {};
};
} // namespace ObsidianEdge
