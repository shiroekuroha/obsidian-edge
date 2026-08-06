#include <pch.h>

#include "application/application.h"
#include "engine/handler_default.h"
#include "engine/render.h"

namespace ObsidianEdge {
Application *Application::s_application = nullptr;

Application::Application() {
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

    m_init = true;
    m_loop = true;
    s_application = this;

    m_window.reset(Window::create());
    m_window->setEventCallback([this](auto &&PH1) -> auto { onEvent(std::forward<decltype(PH1)>(PH1)); });
}

void Application::yeet() { OE_CORE_INFO("Application Yeet!"); }

void Application::run() {
    initKeepers();

    std::atomic<bool> isRunning = true;

    MeshHandler mesh({{

                          {{-0.5f, -0.5f, 0.0f, 1.0f}, {0.0f, 0.0f}},

                          {{0.5f, -0.5f, 0.0f, 1.0f}, {1.0f, 0.0f}},

                          {{-0.5f, 0.5f, 0.0f, 1.0f}, {0.0f, 1.0f}}},
                      {0, 1, 2}});

    RenderObjData data = {1, mesh, MaterialHandler(1)};

    std::vector<RenderObjData> alphaBuffer = {data};
    std::vector<RenderObjData> omegaBuffer = {data};
    std::atomic<std::vector<RenderObjData> *> currentBuffer = &alphaBuffer;
    std::atomic<bool> swapReady = false;

    std::thread renderThread(renderLoop, getWindow().getNative(), std::ref(isRunning), std::ref(currentBuffer),
                             std::ref(swapReady));

    while (m_loop) {
        /**
         * @brief Delta seconds from the last frame
         */
        double delta = getDelta();
        updateDeltaClock();

        m_window->update();
        onUpdate(delta);

        for (Layer *it : m_layerStack)
            it->onUpdate(delta);
    }

    isRunning = false;
    renderThread.join();
}

void Application::pushLayer(Layer *layer) {
    m_layerStack.pushLayer(layer);
    layer->onAttach();
}

void Application::pushOverlay(Layer *overlay) {
    m_layerStack.pushOverlay(overlay);
    overlay->onAttach();
}

void Application::clearLayers() {
    std::for_each(m_layerStack.begin(), m_layerStack.end(), [](Layer *layer) -> void { layer->onDetach(); });
    m_layerStack.clear();
}

void Application::onUpdate(double delta) {}

void Application::onEvent(const std::shared_ptr<Event> &event) {
    EventDispatcher eventDispatcher(*event);

    eventDispatcher.dispatch<WindowClosedEvent>([this](WindowClosedEvent &event) -> bool {
        this->onWindowClose();

        return true;
    });

    for (Layer *it : m_layerStack) {
        if (!event->isHandled())
            it->onEvent(*event);
        else
            break;
    }
}

void Application::onWindowClose() { m_loop = !(glfwWindowShouldClose(m_window->getNative())); }

auto Application::window() -> Window & { return *m_window; }

auto Application::isLooping() const -> bool { return m_loop; }

auto Application::getWindow() const -> Window & { return *m_window; }

auto Application::getDelta() const -> float {
    std::chrono::duration<float> delta =
        std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::high_resolution_clock::now() - m_time);

    return delta.count();
}

void Application::updateDeltaClock() { m_time = std::chrono::high_resolution_clock::now(); }

auto Application::get() -> Application & { return *s_application; }

auto Application::getNative() -> Application * { return s_application; }
} // namespace ObsidianEdge
