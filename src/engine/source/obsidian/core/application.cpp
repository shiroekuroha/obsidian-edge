#include <obsidian/core/data/pch.h>

#include "obsidian/core/application.h"

namespace ObsidianEdge
{
Application::Application ()
{
    OE_CORE_INFO ("Application Constructor!");
    init ();
}

Application::~Application ()
{
    OE_CORE_INFO ("Application Destructor!");
    yeet ();
}

void
Application::init ()
{
    OE_CORE_INFO ("Application Init!");

    OE_CORE_ASSERT ((getNative () == nullptr), "Application is a singleton, do not create another instance.")
    if (getNative () != nullptr)
        throw std::runtime_error ("Application is a singleton, do not create another instance.");

    m_loop = true;
    s_application = this;
    m_window = Window::create ();
    m_window->setEventCallback ([this] (auto &&PH1) { onEvent (std::forward<decltype (PH1)> (PH1)); });
}

void
Application::yeet ()
{
    OE_CORE_INFO ("Application Yeet!");

    Texture::clear ();
    delete m_window;
}

void
Application::run ()
{
    while (m_loop)
        {
            /**
             * @brief Delta seconds from the last frame
             */
            std::chrono::duration<float> delta = std::chrono::duration_cast<std::chrono::duration<float>> (
                std::chrono::high_resolution_clock::now () - m_time);
            m_time = std::chrono::high_resolution_clock::now ();
            m_window->update ();

            for (Layer *it : m_layerStack)
                it->onUpdate (delta.count ());
        }
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
Application::clearLayers ()
{
    std::for_each (m_layerStack.begin (), m_layerStack.end (), [] (Layer *layer) { layer->onDetach (); });
    m_layerStack.clear ();
}

void
Application::onEvent (SharedPointer<Event> event)
{
    EventDispatcher eventDispatcher (event);

    eventDispatcher.dispatch<WindowClosedEvent> ([this] (WindowClosedEvent &event) {
        this->onWindowClose ();

        return true;
    });

    for (Layer *it : m_layerStack)
        {
            if (!event->isHandled ())
                it->onEvent (event);
            else
                break;
        }
}

void
Application::onWindowClose ()
{
    m_loop = !(true && glfwWindowShouldClose (m_window->getNative ()));
}

auto
Application::window () -> Window &
{
    return *m_window;
}

auto
Application::get () -> Application &
{
    return *s_application;
}

auto
Application::getNative () -> Application *
{
    return s_application;
}

Application *Application::s_application;
}
