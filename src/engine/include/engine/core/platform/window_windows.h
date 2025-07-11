#pragma once

#include "engine/core/application/window.h"
#include "engine/core/event/event_application.h"
#include "engine/core/event/event_keyboard.h"
#include "engine/core/event/event_mouse.h"

namespace ObsidianEdge {
class WindowsWindow : public Window {
   public:
    WindowsWindow(const WindowProps& props);
    virtual ~WindowsWindow() override;

    /**
     * To be implemented when doing multi-platform instructions
     */
};
}  // namespace ObsidianEdge
