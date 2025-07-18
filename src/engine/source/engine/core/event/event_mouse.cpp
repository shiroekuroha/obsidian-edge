#include "engine/core/event/event_mouse.h"
#include "engine/core/event/event.h"
#include "engine/core/event/input_codes.h"

namespace ObsidianEdge
{
// Class: MouseButtonPressedEvent

MouseButtonPressedEvent::MouseButtonPressedEvent (Input::MouseCode mouseCode)
    : m_mouseCode (mouseCode)
{
}

EVENT_DEFINE_HELPER (MouseButtonPressed, MouseButtonPressedEvent,
                     (EventCategoryInput | EventCategoryMouse
                      | EventCategoryMouseButton))

Input::MouseCode
MouseButtonPressedEvent::getMouseCode () const
{
    return m_mouseCode;
}

std::string
MouseButtonPressedEvent::toString () const
{
    std::stringstream sstream;
    sstream << "Mouse Button Pressed: MouseCode " << m_mouseCode;

    return sstream.str ();
}

// Class: MouseButtonPressedEvent

MouseButtonReleasedEvent::MouseButtonReleasedEvent (Input::MouseCode mouseCode)
    : m_mouseCode (mouseCode)
{
}

EVENT_DEFINE_HELPER (MouseButtonReleased, MouseButtonReleasedEvent,
                     (EventCategoryInput | EventCategoryMouse
                      | EventCategoryMouseButton))

Input::MouseCode
MouseButtonReleasedEvent::getMouseCode () const
{
    return m_mouseCode;
}

std::string
MouseButtonReleasedEvent::toString () const
{
    std::stringstream sstream;
    sstream << "Mouse Button Released: MouseCode " << m_mouseCode;

    return sstream.str ();
}

// Class: MouseMovedEvent

MouseMovedEvent::MouseMovedEvent (float x, float y) : x (x), y (y) {}

EVENT_DEFINE_HELPER (MouseMoved, MouseMovedEvent,
                     (EventCategoryInput | EventCategoryMouse))

float
MouseMovedEvent::getX () const
{
    return x;
}

float
MouseMovedEvent::getY () const
{
    return y;
}

std::string
MouseMovedEvent::toString () const
{
    std::stringstream sstream;
    sstream << "Mouse Moved: new X " << x << ", new Y " << y;

    return sstream.str ();
}

// Class: MouseScrolled

MouseScrolledEvent::MouseScrolledEvent (float xOffset, float yOffset)
    : xOffset (xOffset), yOffset (yOffset)
{
}

EVENT_DEFINE_HELPER (MouseScrolled, MouseScrolledEvent,
                     (EventCategoryInput | EventCategoryMouse))

float
MouseScrolledEvent::getXOffset () const
{
    return xOffset;
}

float
MouseScrolledEvent::getYOffset () const
{
    return yOffset;
}

std::string
MouseScrolledEvent::toString () const
{
    std::stringstream sstream;
    sstream << "Mouse Moved: new X Offset " << xOffset << ", new Y Offset "
            << yOffset;

    return sstream.str ();
}
}