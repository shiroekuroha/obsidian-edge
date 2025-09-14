#pragma once

#include "engine/core/modules/data/vector/vector2.h"
#include "engine/core/modules/data/vector/vector2i.h"
#include "engine/core/modules/event/codes/codes_key.h"
#include "engine/core/modules/event/event.h"

namespace ObsidianEdge
{
class KeyEvent : public Event
{
public:
    KeyEvent (Input::KeyCode keyCode, int mods);
    virtual ~KeyEvent () = default;

    EVENT_DECLARE_HELPER (Key)

    Input::KeyCode getKeyCode () const;
    int getMods () const;

private:
    Input::KeyCode m_keyCode;
    int m_mods;
};

class KeyPressedEvent : public KeyEvent
{
public:
    KeyPressedEvent (Input::KeyCode keyCode, int mods, bool isRepeated = 0);
    virtual ~KeyPressedEvent () = default;

    EVENT_DECLARE_HELPER (Key)

    bool isRepeated () const;

private:
    bool m_isRepeated;
};

class KeyReleasedEvent : public KeyEvent
{
public:
    KeyReleasedEvent (Input::KeyCode keyCode, int mods);
    virtual ~KeyReleasedEvent () = default;

    EVENT_DECLARE_HELPER (KeyReleased)
};
}
