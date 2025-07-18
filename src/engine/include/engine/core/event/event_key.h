#pragma once

#include <sstream>
#include <string_view>

#include "engine/core/event/event.h"
#include "engine/core/event/input_codes.h"

namespace ObsidianEdge
{
class KeyPressedEvent : public Event
{
  public:
    KeyPressedEvent () = delete;
    KeyPressedEvent (Input::KeyCode keyCode, bool isRepeated = false);

    EVENT_DECLARE_HELPER (KeyPressed)

    Input::KeyCode getKeyCode () const;
    bool isRepeated () const;

  private:
    Input::KeyCode m_keyCode;
    bool m_isRepeated;
};

class KeyReleasedEvent : public Event
{
  public:
    KeyReleasedEvent () = delete;
    KeyReleasedEvent (Input::KeyCode keyCode);

    EVENT_DECLARE_HELPER (KeyReleased)

    Input::KeyCode getKeyCode () const;

  private:
    Input::KeyCode m_keyCode;
};
}