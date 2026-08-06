#include <pch.h>

#include "platform/windows/window_windows.h"

namespace ObsidianEdge {
WindowsWindow::WindowsWindow(const WindowProps& props)
    : Window::Window(props) {
    /**
     * To be implemented when doing multi-platform instructions
     */
    OE_CORE_TRACE("Windows Window Constructor!");
}

WindowsWindow::~WindowsWindow() {
    /**
     * To be implemented when doing multi-platform instructions
     */
    OE_CORE_TRACE("Windows Window Destructor!");
}

/**
 * To be implemented when doing multi-platform instructions
 */
} // namespace ObsidianEdge
