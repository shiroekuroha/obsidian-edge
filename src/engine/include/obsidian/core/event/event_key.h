#ifndef OE_EVENT_KEY_H
#define OE_EVENT_KEY_H

#include "obsidian/core/event/codes/codes_key.h"
#include "obsidian/core/event/event.h"

namespace ObsidianEdge
{
class KeyEvent : public Event
{
public:
    KeyEvent (Input::KeyCode keyCode, int mods);

    EVENT_DECLARE_HELPER (Key)

    [[nodiscard]] auto getKeyCode () const -> Input::KeyCode;
    [[nodiscard]] auto getMods () const -> int;

private:
    Input::KeyCode m_keyCode = 0;
    int m_mods = 0;
};

class KeyPressedEvent : public KeyEvent
{
public:
    KeyPressedEvent (Input::KeyCode keyCode, int mods, bool isRepeated = false);

    EVENT_DECLARE_HELPER (KeyPressed)

    [[nodiscard]] auto isRepeated () const -> bool;

private:
    bool m_isRepeated = false;
};

class KeyReleasedEvent : public KeyEvent
{
public:
    KeyReleasedEvent (Input::KeyCode keyCode, int mods);

    EVENT_DECLARE_HELPER (KeyReleased)
};
}

#endif
