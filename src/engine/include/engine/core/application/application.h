#pragma once

// ! This order matters!
// clang-format off
#include <glad/gl.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "engine/core/core.h"
#include "engine/core/modules/event/event.h"
#include "engine/core/modules/event/event_app.h"
#include "engine/core/modules/event/event_key.h"
#include "engine/core/modules/event/event_mouse.h"
#include "engine/core/modules/layer/layer.h"
#include "engine/core/modules/layer/layer_stack.h"
#include "engine/core/modules/log/logger.h"
#include "engine/core/modules/window/window.h"

namespace ObsidianEdge
{
class OE_API Application
{
public:
    Application ();
    virtual ~Application () = default;

    virtual void run ();

    virtual void onEvent (std::shared_ptr<Event> event);
    virtual bool requestWindowClose (WindowClosedEvent &e);

    void pushLayer (Layer *layer);
    void pushOverlay (Layer *overlay);

    void clearLayerStack ();

    static Application &getApplication ();
    Window &getWindow ();

private:
    bool m_looping = true;
    Window *m_window;

    LayerStack m_layerStack;

private:
    static Application *s_application;
};

Application *createApplication ();
} // namespace ObsidianEdge
