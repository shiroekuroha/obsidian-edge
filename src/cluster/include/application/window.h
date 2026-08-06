#pragma once

#include "core.h"

// ! This order matters!
// clang-format off
#include <glad/gl.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "core/event/event.h"
#include "core/event/event_app.h"
#include "core/event/event_key.h"
#include "core/event/event_mouse.h"
#include "core/log/log.h"

namespace ObsidianEdge {
static const unsigned int s_defaultWindowWidth = 1000;
static const unsigned int s_defaultWindowHeight = 900;

using EventCallbackFn = std::function<void(std::shared_ptr<Event>)>;

using WindowProps = struct WindowProps {
    std::string title = "Obsidian Edge";
    Vector2i windowDimensions = {s_defaultWindowWidth, s_defaultWindowHeight};
};

using WindowData = struct WindowData {
    std::string title = {};
    Vector2i windowDimensions = {s_defaultWindowWidth, s_defaultWindowHeight};
    Vector2i viewportDimensions = {0, 0};

    EventCallbackFn eventCallback;
    bool vSync;
};

class OE_API Window {
public:
    Window(const WindowProps &props = {"Obsidian Edge", {s_defaultWindowWidth, s_defaultWindowHeight}});

    Window();
    virtual ~Window();

    Window(const Window &other) = delete;
    Window(Window &&other) noexcept = delete;

    auto operator=(const Window &other) -> Window & = delete;
    auto operator=(Window &&other) noexcept -> Window & = delete;

    void update();
    void setEventCallback(const EventCallbackFn &callback);

    void setVSync(bool enabled);
    [[nodiscard]] auto isVSync() const -> bool;

    auto get() -> GLFWwindow &;
    auto getNative() -> GLFWwindow *;

    [[nodiscard]] auto getViewportDimensions() const -> Point2;
    [[nodiscard]] auto getWindowDimensions() const -> Point2;

public:
    static auto create(const WindowProps &props = WindowProps()) -> Window *;

private:
    WindowData m_data;
    GLFWwindow *m_window;

protected:
    static bool s_glfwInitialized;
};
} // namespace ObsidianEdge
