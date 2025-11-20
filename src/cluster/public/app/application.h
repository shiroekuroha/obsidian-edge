#pragma once

#include "app/window.h"
#include "core/layer/layer_stack.h"

namespace ObsidianEdge {
enum class RenderAPI : std::int8_t {
    OpenGL = 0, //* Compat API < ! default ! >
    Vulkan,     //* Linux / Android
    DirectX11,  //* Windows
    DirectX12,  //* Windows
    Metal,      //* Mac / IOS
};

/**
 * @brief Application object, singleton.
 */
class Application {
public:
    Application();
    virtual ~Application();

    Application(const Application &other) = delete;
    Application(Application &&other) noexcept = delete;

    auto operator=(const Application &other) -> Application & = delete;
    auto operator=(Application &&other) noexcept -> Application & = delete;

    virtual void init();
    virtual void yeet();

    virtual void onEvent(const std::shared_ptr<Event> &event);
    virtual void onWindowClose();

    /**
     * @brief run Application's main loop.
     */
    virtual void run();

    void pushLayer(Layer *layer);
    void pushOverlay(Layer *overlay);

    void clearLayers();

    auto window() -> Window &;

public:
    /**
     * @brief return global reference to singleton of Application.
     * @return Application& reference to application singleton.
     */
    static auto get() -> Application &;

    /**
     * @brief return global pointer to singleton of Application.
     * @return Application* pointer to application singleton.
     */
    static auto getNative() -> Application *;

private:
    std::chrono::high_resolution_clock::time_point m_time = std::chrono::high_resolution_clock::now();
    bool m_loop = false;

    Window *m_window = nullptr;
    LayerStack m_layerStack;

private:
    static Application *s_application;
};

auto createApplication() -> ObsidianEdge::Application *;
} // namespace ObsidianEdge
