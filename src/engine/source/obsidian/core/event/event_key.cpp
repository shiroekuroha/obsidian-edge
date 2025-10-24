#include <obsidian/core/data/pch.h>

#include "obsidian/core/event/event_key.h"

namespace ObsidianEdge
{
KeyEvent::KeyEvent (Input::KeyCode keyCode, int mods) : m_keyCode (keyCode), m_mods (mods) {}

EVENT_DEFINE_HELPER (Key, EventCategoryInput | EventCategoryKeyboard)

auto
KeyEvent::getKeyCode () const -> Input::KeyCode
{
    return m_keyCode;
}

auto
KeyEvent::getMods () const -> int
{
    return m_mods;
}

auto
KeyEvent::toString () const -> String
{
    return "Base Key Event";
}

KeyPressedEvent::KeyPressedEvent (Input::KeyCode keyCode, int mods, bool isRepeated)
    : KeyEvent (keyCode, mods), m_isRepeated (isRepeated)
{
}

EVENT_DEFINE_HELPER (KeyPressed, EventCategoryInput | EventCategoryKeyboard)

auto
KeyPressedEvent::isRepeated () const -> bool
{
    return m_isRepeated;
}

auto
KeyPressedEvent::toString () const -> String
{
    return "Key Pressed, Key Code: " + std::to_string (getKeyCode ()) + ", mods: " + std::to_string (getMods ())
           + (isRepeated () ? ", is repeated" : "");
}

KeyReleasedEvent::KeyReleasedEvent (Input::KeyCode keyCode, int mods) : KeyEvent (keyCode, mods) {}

EVENT_DEFINE_HELPER (KeyReleased, EventCategoryInput | EventCategoryKeyboard)

auto
KeyReleasedEvent::toString () const -> String
{
    return "Key Released, Key Code: " + std::to_string (getKeyCode ()) + ", mods: " + std::to_string (getMods ());
}
}
