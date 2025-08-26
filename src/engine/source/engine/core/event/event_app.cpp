#include "engine/core/event/event_app.h"

namespace ObsidianEdge
{
EVENT_DEFINE_HELPER (WindowGainedFocus, EventCategoryApplication)

std::string
WindowGainedFocusEvent::toString () const
{
    return std::string ("Window Gained Focus");
}

EVENT_DEFINE_HELPER (WindowLostFocus, EventCategoryApplication)

std::string
WindowLostFocusEvent::toString () const
{
    return std::string ("Window Lost Focus");
}

WindowMovedEvent::WindowMovedEvent (const Vector2i location) : m_location (location) {}

EVENT_DEFINE_HELPER (WindowMoved, EventCategoryApplication)

Vector2i
WindowMovedEvent::getLocation () const
{
    return m_location;
}

int
WindowMovedEvent::getX () const
{
    return m_location.x;
}

int
WindowMovedEvent::getY () const
{
    return m_location.y;
}

std::string
WindowMovedEvent::toString () const
{
    return std::string ("Window Moved to x: ") + std::to_string (m_location.x) + ", y: " + std::to_string (m_location.y);
}

WindowResizedEvent::WindowResizedEvent (const Vector2i size) : m_size (size) {}

EVENT_DEFINE_HELPER (WindowResized, EventCategoryApplication)

Vector2i
WindowResizedEvent::getSize () const
{
    return m_size;
}

int
WindowResizedEvent::getWidth () const
{
    return m_size.x;
}

int
WindowResizedEvent::getHeight () const
{
    return m_size.y;
}

std::string
WindowResizedEvent::toString () const
{
    return std::string ("Window Resized to width: ") + std::to_string (m_size.x) + ", height: " + std::to_string (m_size.y);
}

EVENT_DEFINE_HELPER (WindowClosed, EventCategoryApplication)

std::string
WindowClosedEvent::toString () const
{
    return std::string ("Window Closed");
}
}
