#include <pch.h>

#include "platform/mac/window_mac.h"

namespace ObsidianEdge {
MacWindow::MacWindow(const WindowProps& props)
    : Window::Window(props) {
    /**
     * To be implemented when doing multi-platform instructions
     */
    OE_CORE_TRACE("Linux Window Constructor!");
}

MacWindow::~MacWindow() {
    Window::~Window();
    /**
     * To be implemented when doing multi-platform instructions
     */
    OE_CORE_TRACE("Linux Window Destructor!");
}

/**
 * To be implemented when doing multi-platform instructions
 */
} // namespace ObsidianEdge
