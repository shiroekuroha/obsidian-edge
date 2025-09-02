#include <engine/core/pch.h>

#include "engine/core/application/application.h"

namespace ObsidianEdge
{
Application::Application ()
{
    m_looping = true;
    m_window = std::unique_ptr<Window> (Window::create ());
    m_window->setEventCallback (std::bind (&Application::onEvent, this, std::placeholders::_1));
}

void
Application::run ()
{
    while (m_looping)
        {
            // Event Polling
            m_window->onUpdate ();
            std::for_each (m_layerStack.begin (), m_layerStack.end (), [] (Layer *layer) { layer->onUpdate (); });
        }
}

void
Application::onEvent (std::shared_ptr<Event> event)
{
    EventDispatcher eventDispatcher (event);

    eventDispatcher.dispatch<WindowClosedEvent> (([this] (WindowClosedEvent &e) {
        this->requestWindowClose (e);

        return true;
    }));

    for (auto it = m_layerStack.end (); it != m_layerStack.begin (); --it)
        {
            (*it)->onEvent (*event.get ());
            if (event.get ()->isHandled ())
                break;
        }
}

bool
Application::requestWindowClose (WindowClosedEvent &e)
{
    m_looping = false;

    return true;
}

void
Application::pushLayer (Layer *layer)
{
    m_layerStack.pushLayer (layer);
}

void
Application::pushOverlay (Layer *overlay)
{
    m_layerStack.pushOverlay (overlay);
}

void
Application::clearLayerStack ()
{
    m_layerStack.clear ();
}
} // namespace ObsidianEdge
