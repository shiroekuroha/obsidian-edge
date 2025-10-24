#include <obsidian/core/data/pch.h>

#include "obsidian/core/event/event_app.h"

namespace ObsidianEdge
{
EVENT_DEFINE_HELPER (WindowGainedFocus, EventCategoryApplication)

auto
WindowGainedFocusEvent::toString () const -> String
{
    return "Window Gained Focus";
}

EVENT_DEFINE_HELPER (WindowLostFocus, EventCategoryApplication)

auto
WindowLostFocusEvent::toString () const -> String
{
    return "Window Lost Focus";
}

WindowMovedEvent::WindowMovedEvent (const Vector2i location) : m_location (location) {}

EVENT_DEFINE_HELPER (WindowMoved, EventCategoryApplication)

auto
WindowMovedEvent::getLocation () const -> Vector2i
{
    return m_location;
}

auto
WindowMovedEvent::getX () const -> int
{
    return m_location.x;
}

auto
WindowMovedEvent::getY () const -> int
{
    return m_location.y;
}

auto
WindowMovedEvent::toString () const -> String
{
    return String ("Window Moved to x: ") + std::to_string (m_location.x) + ", y: " + std::to_string (m_location.y);
}

WindowResizedEvent::WindowResizedEvent (const Vector2i size) : m_size (size) {}

EVENT_DEFINE_HELPER (WindowResized, EventCategoryApplication)

auto
WindowResizedEvent::getSize () const -> Vector2i
{
    return m_size;
}

auto
WindowResizedEvent::getWidth () const -> int
{
    return m_size.x;
}

auto
WindowResizedEvent::getHeight () const -> int
{
    return m_size.y;
}

auto
WindowResizedEvent::toString () const -> String
{
    return String ("Window Resized to width: ") + std::to_string (m_size.x) + ", height: " + std::to_string (m_size.y);
}

EVENT_DEFINE_HELPER (WindowClosed, EventCategoryApplication)

auto
WindowClosedEvent::toString () const -> String
{
    return "Window Closed";
}
}
