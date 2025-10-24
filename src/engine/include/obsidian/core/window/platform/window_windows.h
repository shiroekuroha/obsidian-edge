#ifndef OE_WINDOW_WINDOWS_H
#define OE_WINDOW_WINDOWS_H

#include "obsidian/core/window/window.h"

namespace ObsidianEdge
{
class WindowsWindow : public Window
{
public:
    WindowsWindow (const WindowProps &props = WindowProps ());

    WindowsWindow () = delete;
    ~WindowsWindow () override;

    WindowsWindow (const WindowsWindow &other) = delete;
    WindowsWindow (WindowsWindow &&other) noexcept = delete;

    auto operator= (const WindowsWindow &other) -> WindowsWindow & = delete;
    auto operator= (WindowsWindow &&other) noexcept -> WindowsWindow & = delete;

    /**
     * To be implemented when doing multi-platform instructions
     */
};
} // namespace ObsidianEdge

#endif
