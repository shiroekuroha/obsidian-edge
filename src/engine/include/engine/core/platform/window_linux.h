#pragma once

#include "engine/core/application/window.h"
#include "engine/core/event/event_application.h"
#include "engine/core/event/event_keyboard.h"
#include "engine/core/event/event_mouse.h"

namespace ObsidianEdge {
class LinuxWindow : public Window {
   public:
    LinuxWindow(const WindowProps &props = WindowProps());
    virtual ~LinuxWindow() override;

    /**
     * To be implemented when doing multi-platform instructions
     */
};
}  // namespace ObsidianEdge
