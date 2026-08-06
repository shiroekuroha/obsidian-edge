
#include "core/event/event_app.h"
#include <pch.h>

namespace ObsidianEdge {
EVENT_DEFINE_HELPER(WindowGainedFocus, EventCategoryApplication)

auto WindowGainedFocusEvent::toString() const -> std::string { return "Window Gained Focus"; }

EVENT_DEFINE_HELPER(WindowLostFocus, EventCategoryApplication)

auto WindowLostFocusEvent::toString() const -> std::string { return "Window Lost Focus"; }

WindowMovedEvent::WindowMovedEvent(Vector2i position) : m_position(std::move(position)) {}

EVENT_DEFINE_HELPER(WindowMoved, EventCategoryApplication)

auto WindowMovedEvent::getPosition() const -> Vector2i { return m_position; }

auto WindowMovedEvent::getX() const -> int { return m_position.x; }

auto WindowMovedEvent::getY() const -> int { return m_position.y; }

auto WindowMovedEvent::toString() const -> std::string {
    return std::string("Window Moved to x: ") + std::to_string(m_position.x) + ", y: " + std::to_string(m_position.y);
}

WindowResizedEvent::WindowResizedEvent(Point2 dimensions) : m_dimensions(std::move(dimensions)) {}

EVENT_DEFINE_HELPER(WindowResized, EventCategoryApplication)

auto WindowResizedEvent::getDimensions() const -> Point2 { return m_dimensions; }

auto WindowResizedEvent::getWidth() const -> unsigned int { return m_dimensions.x; }

auto WindowResizedEvent::getHeight() const -> unsigned int { return m_dimensions.y; }

auto WindowResizedEvent::toString() const -> std::string {
    return std::string("Window Resized to width: ") + std::to_string(m_dimensions.x) +
           ", height: " + std::to_string(m_dimensions.y);
}

EVENT_DEFINE_HELPER(WindowMaximized, EventCategoryApplication)

auto WindowMaximizedEvent::toString() const -> std::string { return "Window Maximized"; }

EVENT_DEFINE_HELPER(WindowMinimized, EventCategoryApplication)

auto WindowMinimizedEvent::toString() const -> std::string { return "Window Minimized"; }

EVENT_DEFINE_HELPER(WindowRestored, EventCategoryApplication)

auto WindowRestoredEvent::toString() const -> std::string { return "Window Restored"; }

EVENT_DEFINE_HELPER(WindowClosed, EventCategoryApplication)

auto WindowClosedEvent::toString() const -> std::string { return "Window Closed"; }

FrameBufferResizedEvent::FrameBufferResizedEvent(Point2 dimensions) : m_dimensions(std::move(dimensions)) {}

EVENT_DEFINE_HELPER(FrameBufferResized, EventCategoryApplication)

auto FrameBufferResizedEvent::getDimensions() const -> Point2 { return m_dimensions; }

auto FrameBufferResizedEvent::getWidth() const -> unsigned int { return m_dimensions.x; }

auto FrameBufferResizedEvent::getHeight() const -> unsigned int { return m_dimensions.y; }

auto FrameBufferResizedEvent::toString() const -> std::string {
    return std::string("Window Resized to width: ") + std::to_string(m_dimensions.x) +
           ", height: " + std::to_string(m_dimensions.y);
}
} // namespace ObsidianEdge
