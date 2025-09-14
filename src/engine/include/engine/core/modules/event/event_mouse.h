#pragma once

#include "engine/core/modules/data/vector/vector2.h"
#include "engine/core/modules/data/vector/vector2i.h"
#include "engine/core/modules/event/codes.h"
#include "engine/core/modules/event/event.h"

namespace ObsidianEdge
{
class MouseButtonEvent : public Event
{
public:
    MouseButtonEvent (Input::MouseCode mouseCode);
    virtual ~MouseButtonEvent () = default;

    EVENT_DECLARE_HELPER (MouseButton)

    Input::MouseCode getMouseCode () const;

private:
    Input::MouseCode m_mouseCode;
};

class MouseButtonPressedEvent : public MouseButtonEvent
{
public:
    MouseButtonPressedEvent (Input::MouseCode mouseCode);
    virtual ~MouseButtonPressedEvent () = default;

    EVENT_DECLARE_HELPER (MouseButtonPressed)
};

class MouseButtonReleasedEvent : public MouseButtonEvent
{
public:
    MouseButtonReleasedEvent (Input::MouseCode mouseCode);
    virtual ~MouseButtonReleasedEvent () = default;

    EVENT_DECLARE_HELPER (MouseButtonReleased)
};

class MouseMovedEvent : public Event
{
public:
    MouseMovedEvent (const Vector2 location);
    virtual ~MouseMovedEvent () = default;

    EVENT_DECLARE_HELPER (MouseMoved)

    Vector2 getLocation () const;

    float getX () const;
    float getY () const;

private:
    Vector2 m_location;
};

class MouseScrolledEvent : public Event
{
public:
    MouseScrolledEvent (const Vector2 offset);
    virtual ~MouseScrolledEvent () = default;

    EVENT_DECLARE_HELPER (MouseScrolled)

    Vector2 getOffset () const;

    float getX () const;
    float getY () const;

private:
    Vector2 m_offset;
};
}
