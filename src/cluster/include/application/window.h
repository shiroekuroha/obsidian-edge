#pragma once

#include "core.h"

// ! This order matters!
// clang-format off
#include <glad/gl.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "core/event/event.h"

namespace ObsidianEdge {
static const unsigned int S_DEFAULT_WINDOW_WIDTH = 1000;
static const unsigned int S_DEFAULT_WINDOW_HEIGHT = 900;

using EventCallbackFn = std::function<void(std::shared_ptr<Event>)>;

using WindowProps = struct WindowProps {
    std::string title = "Obsidian Edge";
    Vector2i windowDimensions = {S_DEFAULT_WINDOW_WIDTH, S_DEFAULT_WINDOW_HEIGHT};
};

using WindowData = struct WindowData {
    std::string title;
    Vector2i windowDimensions;
    Vector2i viewportDimensions;

    EventCallbackFn eventCallback;
    bool vSync;
};

class OE_API Window {
public:
    Window(const WindowProps& props = {"Obsidian Edge", {S_DEFAULT_WINDOW_WIDTH, S_DEFAULT_WINDOW_HEIGHT}});
    virtual ~Window();

    Window(const Window& other) = delete;
    Window(Window&& other) noexcept = delete;

    auto operator=(const Window& other) -> Window& = delete;
    auto operator=(Window&& other) noexcept -> Window& = delete;

    auto get() -> GLFWwindow&;
    auto getNative() -> GLFWwindow*;

    explicit operator const GLFWwindow&() const;
    explicit operator GLFWwindow&();

    explicit operator const GLFWwindow*() const;
    explicit operator GLFWwindow*();

    void init(const WindowProps& props = {"Obsidian Edge", {S_DEFAULT_WINDOW_WIDTH, S_DEFAULT_WINDOW_HEIGHT}});
    void yeet();
    void update();

    void setEventCallback(const EventCallbackFn& callback);

    [[nodiscard]] auto getViewportDimensions() const -> Point2;
    [[nodiscard]] auto getWindowDimensions() const -> Point2;

    [[nodiscard]] auto isVSync() const -> bool;
    void setVSync(bool enabled);

    /**
     * @brief Release context from current thread
     */
    void release();

    /**
     * @brief Acquire context to current thread
     */
    void acquire();

    static auto create(const WindowProps& props = WindowProps()) -> Window*;

protected:
    static bool m_glfwInitialized;

private:
    std::mutex m_mutex;

    WindowData m_data;
    GLFWwindow* m_window = nullptr;
};
} // namespace ObsidianEdge
