#include "engine/core/application/application.h"

#define DISPATCHER_FUNC_BIND(fn) std::bind (fn, this, std::placeholders::_1)

namespace ObsidianEdge
{
Application::Application ()
{
    m_looping = true;
    m_window = std::unique_ptr<Window> (Window::create ());
    m_window->setEventCallback (std::bind (&Application::onEvent, this, std::placeholders::_1));
}

void
Application::onEvent (std::shared_ptr<Event> event)
{
    EventDispatcher eventDispatcher (event);
    eventDispatcher.dispatch<WindowClosedEvent> (std::bind (&Application::requestWindowClose, this, std::placeholders::_1));
}

void
Application::run ()
{
    while (m_looping)
        {
            // Event Polling
            m_window->onUpdate ();
        }
}

bool
Application::requestWindowClose (WindowClosedEvent &e)
{
    m_looping = false;

    return true;
}
} // namespace ObsidianEdge
