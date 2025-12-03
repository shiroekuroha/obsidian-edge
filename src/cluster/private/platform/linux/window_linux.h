#pragma once

#include "app/window.h"

namespace ObsidianEdge {
class LinuxWindow : public Window {
public:
    LinuxWindow(const WindowProps &props = WindowProps());

    LinuxWindow() = delete;
    ~LinuxWindow() override;

    LinuxWindow(const LinuxWindow &other) = delete;
    LinuxWindow(LinuxWindow &&other) noexcept = delete;

    auto operator=(const LinuxWindow &other) -> LinuxWindow & = delete;
    auto operator=(LinuxWindow &&other) noexcept -> LinuxWindow & = delete;

    /**
     * To be implemented when doing multi-platform instructions
     */
};
} // namespace ObsidianEdge
