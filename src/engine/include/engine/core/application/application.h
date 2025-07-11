#pragma once

#include "GLFW/glfw3.h"
#include "engine/core/application/window.h"
#include "engine/core/event/event_application.h"
#include "engine/core/log/logger.h"

namespace ObsidianEdge {
class Application {
   public:
    Application();
    virtual ~Application();

    virtual void onEvent(Event& e);
    virtual void run();

   private:
    bool onWindowClose(WindowClosedEvent& e);

    std::unique_ptr<Window> m_window;
    bool m_running = true;
};

Application* createApplication();
}  // namespace ObsidianEdge
