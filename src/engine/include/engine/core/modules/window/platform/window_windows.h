#pragma once

#include "engine/core/modules/window/window.h"

namespace ObsidianEdge
{
class WindowsWindow : public Window
{
public:
    WindowsWindow (const WindowProps &props);
    virtual ~WindowsWindow () override;

    /**
     * To be implemented when doing multi-platform instructions
     */
};
} // namespace ObsidianEdge
