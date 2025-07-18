#pragma once

#include <queue>

#include "GLFW/glfw3.h"
#include "engine/core/application/window.h"
#include "engine/core/data/args.h"
#include "engine/core/event/event.h"
#include "engine/core/event/event_app.h"
#include "engine/core/event/event_key.h"
#include "engine/core/event/event_mouse.h"
#include "engine/core/log/logger.h"

namespace ObsidianEdge
{
class Application
{
public:
    Application ();
    virtual ~Application () = default;

    virtual void init (int argc, char **argv);
    virtual void run ();

    virtual void onEvent (std::shared_ptr<Event> event);
    virtual bool onWindowClose (WindowClosedEvent &e);

private:
    bool m_looping = true;

    ArgsContainer m_options;
    std::unique_ptr<Window> m_window;
    std::queue<std::shared_ptr<Event>> m_events;
};

Application *createApplication ();
} // namespace ObsidianEdge
