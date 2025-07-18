#pragma once

#include "engine/core/event/event.h"
#include "engine/core/event/input_codes.h"

namespace ObsidianEdge
{
class MouseButtonPressedEvent : public Event
{
  public:
    MouseButtonPressedEvent () = delete;
    MouseButtonPressedEvent (Input::MouseCode mouseCode);

    EVENT_DECLARE_HELPER (MouseButtonPressed)

    Input::MouseCode getMouseCode () const;

  private:
    Input::MouseCode m_mouseCode;
};

class MouseButtonReleasedEvent : public Event
{
  public:
    MouseButtonReleasedEvent () = delete;
    MouseButtonReleasedEvent (Input::MouseCode mouseCode);

    EVENT_DECLARE_HELPER (MouseButtonReleased)

    Input::MouseCode getMouseCode () const;

  private:
    Input::MouseCode m_mouseCode;
};

class MouseMovedEvent : public Event
{
  public:
    MouseMovedEvent () = delete;
    MouseMovedEvent (float x, float y);

    EVENT_DECLARE_HELPER (MouseMoved)

    float getX () const;
    float getY () const;

  private:
    float x, y;
};

class MouseScrolledEvent : public Event
{
  public:
    MouseScrolledEvent () = delete;
    MouseScrolledEvent (float xOffset, float yOffset);

    EVENT_DECLARE_HELPER (MouseScrolled)

    float getXOffset () const;
    float getYOffset () const;

  private:
    float xOffset, yOffset;
};
}