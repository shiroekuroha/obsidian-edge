#include "engine/core/application/application.h"

namespace ObsidianEdge {
Application::Application() {
    m_window = std::unique_ptr<Window>(Window::create());
    m_window->setEventCallback(
        std::bind(
            &Application::onEvent, this,
            std::placeholders::_1));
    m_running = true;
}

Application::~Application() {}

void Application::onEvent(Event& e) {
    EventDispatcher dispatcher(e);
    dispatcher.dispatch<WindowClosedEvent>(std::bind(
        &Application::onWindowClose, this,
        std::placeholders::_1));
}

void Application::run() {
    int r = 0, g = 0, b = 0;

    while (m_running) {
        m_window->onUpdate();
    }
}

bool Application::onWindowClose(WindowClosedEvent& e) {
    m_running = false;

    return true;
}
}  // namespace ObsidianEdge
