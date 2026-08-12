#include <pch.h>

#include "application/application.h"

#include "core/event/event_app.h"
#include "engine/handler.h"

namespace ObsidianEdge {
Application* Application::m_application = nullptr;

Application::Application()
    : m_window(nullptr) {
    OE_CORE_INFO("Application Constructor!");
    init();
}

Application::~Application() {
    OE_CORE_INFO("Application Destructor!");
    yeet();
}

void Application::init() {
    OE_CORE_INFO("Application Init!");
    OE_CORE_ASSERT((getNative() == nullptr), "Application is a singleton, do not create another instance.")

    initKeepers();

    m_init = true;
    m_loop = true;
    m_application = this;

    m_window = Window::create();
    m_window->setEventCallback([this](auto&& PH1) -> auto {
        onEvent(std::forward<decltype(PH1)>(PH1));
    });
}

void Application::yeet() {
    OE_CORE_INFO("Application Yeet!");

    if (m_window != nullptr) {
        m_window->yeet();
        delete m_window;
    }
}

void Application::run() {
    OE_CORE_TRACE("Begining main loop.")

    std::chrono::high_resolution_clock::time_point time = std::chrono::high_resolution_clock::now();

    while (m_loop) {
        std::chrono::duration<double> delta =
            std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - time);

        double deltaS = delta.count();
        time = std::chrono::high_resolution_clock::now();

        onUpdate(deltaS);
    }
}

void Application::pushLayer(Layer* layer) {
    m_layerStack.pushLayer(layer);
    layer->onAttach();
}

void Application::pushOverlay(Layer* overlay) {
    m_layerStack.pushOverlay(overlay);
    overlay->onAttach();
}

void Application::clearLayers() {
    std::for_each(m_layerStack.begin(), m_layerStack.end(), [](Layer* layer) -> void {
        layer->onDetach();
    });
    m_layerStack.clear();
}

void Application::onUpdate(double delta) {
    m_window->update();

    for (Layer* it : m_layerStack)
        it->onUpdate(delta);
}

void Application::onEvent(const std::shared_ptr<Event>& event) {
    EventDispatcher eventDispatcher(*event);

    eventDispatcher.dispatch<WindowClosedEvent>([this](WindowClosedEvent& event) -> bool {
        this->onWindowClose();

        return true;
    });

    for (Layer* it : m_layerStack) {
        if (!event->isHandled()) {
            it->onEvent(*event);
        } else {
            break;
        }
    }
}

void Application::onWindowClose() {
    m_loop = !(glfwWindowShouldClose(m_window->getNative()));
}

auto Application::window() -> Window& {
    return *m_window;
}

auto Application::isLooping() const -> bool {
    return m_loop;
}

auto Application::getWindow() const -> Window& {
    return *m_window;
}

auto Application::get() -> Application& {
    return *m_application;
}

auto Application::getNative() -> Application* {
    return m_application;
}
} // namespace ObsidianEdge
