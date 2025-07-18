#pragma once

#include <sstream>
#include <string>
#include <string_view>

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
    WindowMovedEvent () = delete;
    WindowMovedEvent (float x, float y);

    EVENT_DECLARE_HELPER (WindowMoved)

    float getX () const;
    float getY () const;

  private:
    float x, y;
};

class WindowResizedEvent : public Event
{
  public:
    WindowResizedEvent () = delete;
    WindowResizedEvent (float x, float y);

    EVENT_DECLARE_HELPER (WindowResized)

    float getX () const;
    float getY () const;

  private:
    float x, y;
};

class WindowClosedEvent : public Event
{
  public:
    EVENT_DECLARE_HELPER (WindowClosed)
};

}