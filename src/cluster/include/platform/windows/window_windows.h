#pragma once

#include "application/window.h"

namespace ObsidianEdge {
class OE_API WindowsWindow : public Window {
public:
    WindowsWindow(const WindowProps &props = WindowProps());

    WindowsWindow() = delete;
    ~WindowsWindow() override;

    WindowsWindow(const WindowsWindow &other) = delete;
    WindowsWindow(WindowsWindow &&other) noexcept = delete;

    auto operator=(const WindowsWindow &other) -> WindowsWindow & = delete;
    auto operator=(WindowsWindow &&other) noexcept -> WindowsWindow & = delete;

    /**
     * To be implemented when doing multi-platform instructions
     */
};
} // namespace ObsidianEdge
