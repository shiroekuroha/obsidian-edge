#ifndef OE_EVENT_MOUSE_H
#define OE_EVENT_MOUSE_H

#include "obsidian/core/event/codes/codes_mouse.h"
#include "obsidian/core/event/event.h"

namespace ObsidianEdge
{
class MouseButtonEvent : public Event
{
public:
    MouseButtonEvent (Input::MouseCode mouseCode);

    EVENT_DECLARE_HELPER (MouseButton)

    [[nodiscard]] auto getMouseCode () const -> Input::MouseCode;

private:
    Input::MouseCode m_mouseCode = 0;
};

class MouseButtonPressedEvent : public MouseButtonEvent
{
public:
    MouseButtonPressedEvent (Input::MouseCode mouseCode);

    EVENT_DECLARE_HELPER (MouseButtonPressed)
};

class MouseButtonReleasedEvent : public MouseButtonEvent
{
public:
    MouseButtonReleasedEvent (Input::MouseCode mouseCode);

    EVENT_DECLARE_HELPER (MouseButtonReleased)
};

class MouseMovedEvent : public Event
{
public:
    MouseMovedEvent (const Vector2 location);

    EVENT_DECLARE_HELPER (MouseMoved)

    [[nodiscard]] auto getLocation () const -> Vector2;

    [[nodiscard]] auto getX () const -> float;
    [[nodiscard]] auto getY () const -> float;

private:
    Vector2 m_location = { 0, 0 };
};

class MouseScrolledEvent : public Event
{
public:
    MouseScrolledEvent (const Vector2 offset);

    EVENT_DECLARE_HELPER (MouseScrolled)

    [[nodiscard]] auto getOffset () const -> Vector2;

    [[nodiscard]] auto getX () const -> float;
    [[nodiscard]] auto getY () const -> float;

private:
    Vector2 m_offset = { 0, 0 };
};
}

#endif
