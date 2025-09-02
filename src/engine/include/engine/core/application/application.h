#pragma once

#include "glad/gl.h"

#include "GLFW/glfw3.h"

#include "engine/core/application/window.h"
#include "engine/core/event/event.h"
#include "engine/core/event/event_app.h"
#include "engine/core/event/event_key.h"
#include "engine/core/event/event_mouse.h"
#include "engine/core/layer/layer.h"
#include "engine/core/layer/layer_stack.h"
#include "engine/core/log/logger.h"

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

private:
    bool m_looping = true;

    std::unique_ptr<Window> m_window;
    LayerStack m_layerStack;
};

Application *createApplication ();
} // namespace ObsidianEdge
