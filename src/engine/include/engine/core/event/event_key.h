#pragma once

#include "engine/core/event/codes.h"
#include "engine/core/event/event.h"

namespace ObsidianEdge
{
class KeyEvent : public Event
{
public:
    KeyEvent (Input::KeyCode keyCode);
    virtual ~KeyEvent () = default;

    EVENT_DECLARE_HELPER (Key)

    Input::KeyCode getKeyCode () const;

private:
    Input::KeyCode m_keyCode;
};

class KeyPressedEvent : public KeyEvent
{
public:
    KeyPressedEvent (Input::KeyCode keyCode, bool isRepeated = 0);
    virtual ~KeyPressedEvent () = default;

    EVENT_DECLARE_HELPER (Key)

    bool isRepeated() const;

private:
    bool m_isRepeated;
};

class KeyReleasedEvent : public KeyEvent
{
public:
    KeyReleasedEvent (Input::KeyCode keyCode);
    virtual ~KeyReleasedEvent () = default;

    EVENT_DECLARE_HELPER (KeyReleased)
};
}
