
#include "core/event/event_mouse.h"
#include <pch.h>

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

MouseMovedEvent::MouseMovedEvent(Vector2 position) : m_position(std::move(position)) {}

EVENT_DEFINE_HELPER(MouseMoved, EventCategoryInput | EventCategoryMouse)

auto MouseMovedEvent::getPosition() const -> Vector2 { return m_position; }

auto MouseMovedEvent::getX() const -> float { return m_position.x; }

auto MouseMovedEvent::getY() const -> float { return m_position.y; }

auto MouseMovedEvent::toString() const -> std::string {
    return "Mouse Moved to location x: " + std::to_string(getX()) + ", y: " + std::to_string(getY());
}

MouseScrolledEvent::MouseScrolledEvent(Vector2 offset) : m_offset(std::move(offset)) {}

EVENT_DEFINE_HELPER(MouseScrolled, EventCategoryInput | EventCategoryMouse)

auto MouseScrolledEvent::getOffset() const -> Vector2 { return m_offset; }

auto MouseScrolledEvent::getX() const -> float { return m_offset.x; }

auto MouseScrolledEvent::getY() const -> float { return m_offset.y; }

auto MouseScrolledEvent::toString() const -> std::string {
    return "Mouse scrolled offsetted by x: " + std::to_string(getX()) + ", y: " + std::to_string(getY());
}
} // namespace ObsidianEdge
