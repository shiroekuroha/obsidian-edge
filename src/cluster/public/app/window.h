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
using EventCallbackFn = std::function<void(std::shared_ptr<Event>)>;

static const int s_defaultWindowWidth = 1920;
static const int s_defaultWindowHeight = 1080;

struct WindowProps {
    std::string title = {};
    Vector2i size = {s_defaultWindowWidth, s_defaultWindowHeight};
};

struct WindowData {
    std::string title = {};
    Vector2i size = {s_defaultWindowWidth, s_defaultWindowHeight};

    EventCallbackFn eventCallback;
    bool vSync;
};

class Window {
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

    [[nodiscard]] auto getWidth() const -> unsigned int;
    [[nodiscard]] auto getHeight() const -> unsigned int;

public:
    static auto create(const WindowProps &props = WindowProps()) -> Window *;

private:
    WindowData m_data;
    GLFWwindow *m_window;

protected:
    static bool s_glfwInitialized;
};
} // namespace ObsidianEdge
