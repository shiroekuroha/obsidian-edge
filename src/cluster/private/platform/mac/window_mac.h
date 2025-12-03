#pragma once

#include "app/window.h"

namespace ObsidianEdge {
class MacWindow : public Window {
public:
    MacWindow(const WindowProps &props = WindowProps());

    MacWindow() = delete;
    ~MacWindow() override;

    MacWindow(const MacWindow &other) = delete;
    MacWindow(MacWindow &&other) noexcept = delete;

    auto operator=(const MacWindow &other) -> MacWindow & = delete;
    auto operator=(MacWindow &&other) noexcept -> MacWindow & = delete;

    /**
     * To be implemented when doing multi-platform instructions
     */
};
} // namespace ObsidianEdge
