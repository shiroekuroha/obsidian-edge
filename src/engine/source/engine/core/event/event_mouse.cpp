#include "engine/core/event/event_mouse.h"

namespace ObsidianEdge
{
MouseButtonEvent::MouseButtonEvent (Input::MouseCode mouseCode) : m_mouseCode (mouseCode) {}

EVENT_DEFINE_HELPER (MouseButton, EventCategoryInput | EventCategoryMouse | EventCategoryMouseButton)

Input::MouseCode
MouseButtonEvent::getMouseCode () const
{
    return m_mouseCode;
}

std::string
MouseButtonEvent::toString () const
{
    return std::string (getEventName ());
}

MouseButtonPressedEvent::MouseButtonPressedEvent (Input::MouseCode mouseCode) : MouseButtonEvent (mouseCode) {}

EVENT_DEFINE_HELPER (MouseButtonPressed, EventCategoryInput | EventCategoryMouse | EventCategoryMouseButton)

std::string
MouseButtonPressedEvent::toString () const
{
    return "Mouse Button Pressed, Mouse Code: " + std::to_string (getMouseCode ());
}

MouseButtonReleasedEvent::MouseButtonReleasedEvent (Input::MouseCode mouseCode) : MouseButtonEvent (mouseCode) {}

EVENT_DEFINE_HELPER (MouseButtonReleased, EventCategoryInput | EventCategoryMouse | EventCategoryMouseButton)

std::string
MouseButtonReleasedEvent::toString () const
{
    return "Mouse Button Released, Mouse Code: " + std::to_string (getMouseCode ());
}

MouseMovedEvent::MouseMovedEvent (const Vector2 location) : m_location (location) {}

EVENT_DEFINE_HELPER (MouseMoved, EventCategoryInput | EventCategoryMouse)

Vector2
MouseMovedEvent::getLocation () const
{
    return m_location;
}

float
MouseMovedEvent::getX () const
{
    return m_location.x;
}

float
MouseMovedEvent::getY () const
{
    return m_location.y;
}

std::string
MouseMovedEvent::toString () const
{
    return "Mouse Moved to location x: " + std::to_string (getX ()) + ", y: " + std::to_string (getY ());
}

MouseScrolledEvent::MouseScrolledEvent (const Vector2 offset) : m_offset (offset) {}

EVENT_DEFINE_HELPER (MouseScrolled, EventCategoryInput | EventCategoryMouse)

Vector2
MouseScrolledEvent::getOffset () const
{
    return m_offset;
}

float
MouseScrolledEvent::getX () const
{
    return m_offset.x;
}

float
MouseScrolledEvent::getY () const
{
    return m_offset.y;
}

std::string
MouseScrolledEvent::toString () const
{
    return "Mouse scrolled offsetted by x: " + std::to_string (getX ()) + ", y: " + std::to_string (getY ());
}
}
