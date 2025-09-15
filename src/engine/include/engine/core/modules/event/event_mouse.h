#pragma once

#include "engine/core/modules/event/codes/codes_mouse.h"
#include "engine/core/modules/event/event.h"
#include <glm/vec2.hpp>

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
    MouseMovedEvent (const glm::vec2 location);
    virtual ~MouseMovedEvent () = default;

    EVENT_DECLARE_HELPER (MouseMoved)

    glm::vec2 getLocation () const;

    float getX () const;
    float getY () const;

private:
    glm::vec2 m_location;
};

class MouseScrolledEvent : public Event
{
public:
    MouseScrolledEvent (const glm::vec2 offset);
    virtual ~MouseScrolledEvent () = default;

    EVENT_DECLARE_HELPER (MouseScrolled)

    glm::vec2 getOffset () const;

    float getX () const;
    float getY () const;

private:
    glm::vec2 m_offset;
};
}
