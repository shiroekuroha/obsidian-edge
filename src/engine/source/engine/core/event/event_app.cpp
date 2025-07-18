#include "engine/core/event/event_app.h"

namespace ObsidianEdge
{
// Class: WindowGainedFocusEvent

EVENT_DEFINE_HELPER (WindowGainedFocus, WindowGainedFocusEvent,
                     EventCategoryApplication)

std::string
WindowGainedFocusEvent::toString () const
{
    return "Window Gained Focus!";
}

// Class: WindowLostFocusEvent

EVENT_DEFINE_HELPER (WindowLostFocus, WindowLostFocusEvent,
                     EventCategoryApplication)

std::string
WindowLostFocusEvent::toString () const
{
    return "Window Lost Focus!";
}

// Class: WindowMovedEvent

WindowMovedEvent::WindowMovedEvent (float x, float y) : x (x), y (y) {}

EVENT_DEFINE_HELPER (WindowMoved, WindowMovedEvent, EventCategoryApplication)

std::string
WindowMovedEvent::toString () const
{
    std::stringstream sstream;
    sstream << "Window Moved: new X " << getX () << ", new Y " << getY ();

    return sstream.str ();
}

float
WindowMovedEvent::getX () const
{
    return x;
}

float
WindowMovedEvent::getY () const
{
    return y;
}

// Class: WindowResizedEvent

WindowResizedEvent::WindowResizedEvent (float x, float y) : x (x), y (y) {}

EVENT_DEFINE_HELPER (WindowResized, WindowResizedEvent,
                     EventCategoryApplication)

std::string
WindowResizedEvent::toString () const
{
    std::stringstream sstream;
    sstream << "Window Resized: new Width " << getX () << ", new Height "
            << getY ();

    return sstream.str ();
}

float
WindowResizedEvent::getX () const
{
    return x;
}

float
WindowResizedEvent::getY () const
{
    return y;
}

// Class: WindowClosedEvent

EVENT_DEFINE_HELPER (WindowClosed, WindowClosedEvent, EventCategoryApplication)

std::string
WindowClosedEvent::toString () const
{
    std::stringstream sstream;
    sstream << "Window Resized Closed!";

    return sstream.str ();
}
}