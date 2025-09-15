#pragma once

#include "engine/core/modules/window/window.h"

namespace ObsidianEdge
{
class LinuxWindow : public Window
{
public:
    LinuxWindow (const WindowProps &props = WindowProps ());
    virtual ~LinuxWindow () override;

    /**
     * To be implemented when doing multi-platform instructions
     */
};
} // namespace ObsidianEdge
