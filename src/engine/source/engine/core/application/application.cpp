#include "engine/core/application/application.h"

#define DISPATCHER_FUNC_BIND(fn)                               \
    std::bind (fn, this, std::placeholders::_1)

namespace ObsidianEdge
{
Application::Application ()
{
    m_looping = true;
    m_window = std::unique_ptr<Window> (Window::create ());
    m_window->setEventCallback (std::bind (
        &Application::onEvent, this, std::placeholders::_1));
}

void
Application::onEvent (std::shared_ptr<Event> event)
{
    m_events.push (event);
}

void
Application::init (int argc, char **argv)
{
    m_options.set (argc, argv);
}

void
Application::run ()
{
    while (false)
        {
            // Event Polling
            m_window->onUpdate ();

            // Handle Events
            while (!m_events.empty ())
                {
                    EventDispatcher dispatcher (
                        *m_events.front ().get ());

                    dispatcher.dispatch<WindowClosedEvent> (
                        DISPATCHER_FUNC_BIND (
                            &Application::onWindowClose));

                    m_events.pop ();
                }
        }
}

bool
Application::onWindowClose (WindowClosedEvent &e)
{
    m_looping = false;

    return true;
}
} // namespace ObsidianEdge
