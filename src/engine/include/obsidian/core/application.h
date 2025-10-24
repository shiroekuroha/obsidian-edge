#ifndef OE_APPLICATION_H
#define OE_APPLICATION_H

#include <chrono>

#include "obsidian/core/core.h"

#include "obsidian/core/event/event_app.h"
#include "obsidian/core/event/event_key.h"
#include "obsidian/core/event/event_mouse.h"
#include "obsidian/core/layer/layer_stack.h"
#include "obsidian/core/log/log.h"
#include "obsidian/core/render/primitives/texture.h"
#include "obsidian/core/window/window.h"

namespace ObsidianEdge
{
class Application
{
public:
    Application ();
    virtual ~Application ();

    Application (const Application &other) = delete;
    Application (Application &&other) noexcept = delete;

    auto operator= (const Application &other) -> Application & = delete;
    auto operator= (Application &&other) noexcept -> Application & = delete;

    virtual void init ();
    virtual void yeet ();

    virtual void onEvent (SharedPointer<Event> event);
    virtual void onWindowClose ();

    /**
     * @brief run Application's main loop.
     */
    virtual void run ();

    void pushLayer (Layer *layer);
    void pushOverlay (Layer *overlay);

    void clearLayers ();

    auto window () -> Window &;

public:
    /**
     * @brief return global reference to singleton of Application.
     * @return Application& reference to application singleton.
     */
    static auto get () -> Application &;

    /**
     * @brief return global pointer to singleton of Application.
     * @return Application* pointer to application singleton.
     */
    static auto getNative () -> Application *;

private:
    std::chrono::high_resolution_clock::time_point m_time = std::chrono::high_resolution_clock::now ();
    bool m_loop = false;

    Window *m_window = nullptr;
    LayerStack m_layerStack;

private:
    static Application *s_application;
};

auto createApplication () -> ObsidianEdge::Application *;
}

#endif
