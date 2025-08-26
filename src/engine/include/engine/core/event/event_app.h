#pragma once

#include "engine/core/data/vector/vector2i.h"
#include "engine/core/event/event.h"

namespace ObsidianEdge
{
class WindowGainedFocusEvent : public Event
{
public:
    EVENT_DECLARE_HELPER (WindowGainedFocus)
};

class WindowLostFocusEvent : public Event
{
public:
    EVENT_DECLARE_HELPER (WindowLostFocus)
};

class WindowMovedEvent : public Event
{
public:
    WindowMovedEvent (const Vector2i location);
    virtual ~WindowMovedEvent () = default;

    EVENT_DECLARE_HELPER (WindowMoved)

    Vector2i getLocation () const;

    int getX () const;
    int getY () const;

private:
    Vector2i m_location;
};

class WindowResizedEvent : public Event
{
public:
    WindowResizedEvent (const Vector2i size);
    virtual ~WindowResizedEvent () = default;

    EVENT_DECLARE_HELPER (WindowResized)

    Vector2i getSize () const;

    int getWidth () const;
    int getHeight () const;

private:
    Vector2i m_size;
};

class WindowClosedEvent : public Event
{
public:
    EVENT_DECLARE_HELPER (WindowClosed)
};
}
