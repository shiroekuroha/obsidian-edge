#include <pch.h>

#include "event_mouse.h"

namespace ObsidianEdge {
MouseButtonEvent::MouseButtonEvent(Input::MouseCode mouseCode) : m_mouseCode(mouseCode) {}

EVENT_DEFINE_HELPER(MouseButton, EventCategoryInput | EventCategoryMouse | EventCategoryMouseButton)

auto MouseButtonEvent::getMouseCode() const -> Input::MouseCode { return m_mouseCode; }

auto MouseButtonEvent::toString() const -> std::string { return std::string(getEventName()); }

MouseButtonPressedEvent::MouseButtonPressedEvent(Input::MouseCode mouseCode) : MouseButtonEvent(mouseCode) {}

EVENT_DEFINE_HELPER(MouseButtonPressed, EventCategoryInput | EventCategoryMouse | EventCategoryMouseButton)

auto MouseButtonPressedEvent::toString() const -> std::string {
    return "Mouse Button Pressed, Mouse Code: " + std::to_string(getMouseCode());
}

MouseButtonReleasedEvent::MouseButtonReleasedEvent(Input::MouseCode mouseCode) : MouseButtonEvent(mouseCode) {}

EVENT_DEFINE_HELPER(MouseButtonReleased, EventCategoryInput | EventCategoryMouse | EventCategoryMouseButton)

auto MouseButtonReleasedEvent::toString() const -> std::string {
    return "Mouse Button Released, Mouse Code: " + std::to_string(getMouseCode());
}

MouseMovedEvent::MouseMovedEvent(const Vector2 location) : m_location(location) {}

EVENT_DEFINE_HELPER(MouseMoved, EventCategoryInput | EventCategoryMouse)

auto MouseMovedEvent::getLocation() const -> Vector2 { return m_location; }

auto MouseMovedEvent::getX() const -> float { return m_location.x; }

auto MouseMovedEvent::getY() const -> float { return m_location.y; }

auto MouseMovedEvent::toString() const -> std::string {
    return "Mouse Moved to location x: " + std::to_string(getX()) + ", y: " + std::to_string(getY());
}

MouseScrolledEvent::MouseScrolledEvent(const Vector2 offset) : m_offset(offset) {}

EVENT_DEFINE_HELPER(MouseScrolled, EventCategoryInput | EventCategoryMouse)

auto MouseScrolledEvent::getOffset() const -> Vector2 { return m_offset; }

auto MouseScrolledEvent::getX() const -> float { return m_offset.x; }

auto MouseScrolledEvent::getY() const -> float { return m_offset.y; }

auto MouseScrolledEvent::toString() const -> std::string {
    return "Mouse scrolled offsetted by x: " + std::to_string(getX()) + ", y: " + std::to_string(getY());
}
} // namespace ObsidianEdge
