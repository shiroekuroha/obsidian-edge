#pragma once

#include "core.h"

#include "application/window.h"
#include "core/layer/layer_stack.h"

namespace ObsidianEdge {
class OE_API Application {
public:
    Application();
    virtual ~Application();

    Application(const Application& other) = delete;
    Application(Application&& other) noexcept = delete;

    auto operator=(const Application& other) -> Application& = delete;
    auto operator=(Application&& other) noexcept -> Application& = delete;

    virtual void init();
    virtual void yeet();

    virtual void onUpdate(double delta);
    virtual void onEvent(const std::shared_ptr<Event>& event);

    virtual void onWindowClose();

    /**
     * @brief run Application's main loop.
     */
    virtual void run();

    void pushLayer(Layer* layer);
    void pushOverlay(Layer* overlay);

    void clearLayers();

    auto window() -> Window&;
    [[nodiscard]] auto isLooping() const -> bool;
    [[nodiscard]] auto getWindow() const -> Window&;
    [[nodiscard]] auto getDelta() const -> float;

    void updateDeltaClock();

    [[nodiscard]] auto getViewportDimensions() const -> Point2 {
        return getWindow().getViewportDimensions();
    }

    [[nodiscard]] auto getWindowDimensions() const -> Point2 {
        return getWindow().getWindowDimensions();
    }

    /**
     * @brief return global reference to singleton of Application.
     * @return Application& reference to application singleton.
     */
    static auto get() -> Application&;

    /**
     * @brief return global pointer to singleton of Application.
     * @return Application* pointer to application singleton.
     */
    static auto getNative() -> Application*;

private:
    bool m_init = false;
    bool m_loop = false;

    LayerStack m_layerStack;

    Window* m_window;
    static Application* m_application;
};

auto createApplication() -> ObsidianEdge::Application*;
} // namespace ObsidianEdge
