#include <engine/core/pch.h>

#include "engine/core/application/application.h"

namespace ObsidianEdge
{
Application *Application::s_application = nullptr;

Application::Application ()
{
    m_looping = true;
    m_window = Window::create ();
    m_window->setEventCallback (std::bind (&Application::onEvent, this, std::placeholders::_1));

    OE_CORE_ASSERT ((s_application == nullptr), "Application is a singleton, cannot exist more than one.")
    s_application = this;

    m_imguiLayer = new ImGuiLayer;
    pushLayer (m_imguiLayer);
}

void
Application::run ()
{
    while (m_looping)
        {
            // Event Polling
            m_window->onUpdate ();
            m_imguiLayer->begin ();
            std::for_each (m_layerStack.begin (), m_layerStack.end (), [] (Layer *layer) { layer->onUpdate (); });
            std::for_each (m_layerStack.begin (), m_layerStack.end (), [] (Layer *layer) { layer->onRender (); });
            m_imguiLayer->end ();
        }
}

void
Application::onEvent (std::shared_ptr<Event> event)
{
    EventDispatcher eventDispatcher (*event.get ());

    eventDispatcher.dispatch<WindowClosedEvent> (([this] (WindowClosedEvent &e) {
        this->requestWindowClose (e);
        return true;
    }));

    std::for_each (m_layerStack.begin (), m_layerStack.end (), [event] (Layer *layer) {
        if (!event.get ()->isHandled ())
            layer->onEvent (*event.get ());
    });
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
    layer->onAttach ();
}

void
Application::pushOverlay (Layer *overlay)
{
    m_layerStack.pushOverlay (overlay);
    overlay->onAttach ();
}

void
Application::clearLayerStack ()
{
    m_layerStack.clear ();
}

Application &
Application::getApplication ()
{
    return *s_application;
}

Window &
Application::getWindow ()
{
    return *m_window;
}
} // namespace ObsidianEdge
