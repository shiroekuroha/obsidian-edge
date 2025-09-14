#include <engine/core/pch.h>

#include "engine/core/modules/event/event_key.h"

namespace ObsidianEdge
{
KeyEvent::KeyEvent (Input::KeyCode keyCode, int mods) : m_keyCode (keyCode), m_mods (mods) {}

EVENT_DEFINE_HELPER (Key, EventCategoryInput | EventCategoryKeyboard)

Input::KeyCode
KeyEvent::getKeyCode () const
{
    return m_keyCode;
}

int
KeyEvent::getMods () const
{
    return m_mods;
}

std::string
KeyEvent::toString () const
{
    return "Base Key Event";
}

KeyPressedEvent::KeyPressedEvent (Input::KeyCode keyCode, int mods, bool isRepeated)
    : KeyEvent (keyCode, mods), m_isRepeated (isRepeated)
{
}

EVENT_DEFINE_HELPER (KeyPressed, EventCategoryInput | EventCategoryKeyboard)

bool
KeyPressedEvent::isRepeated () const
{
    return m_isRepeated;
}

std::string
KeyPressedEvent::toString () const
{
    return "Key Pressed, Key Code: " + std::to_string (getKeyCode ()) + ", mods: " + std::to_string (getMods ())
           + (isRepeated () ? ", is repeated" : "");
}

KeyReleasedEvent::KeyReleasedEvent (Input::KeyCode keyCode, int mods) : KeyEvent (keyCode, mods) {}

EVENT_DEFINE_HELPER (KeyReleased, EventCategoryInput | EventCategoryKeyboard)

std::string
KeyReleasedEvent::toString () const
{
    return "Key Released, Key Code: " + std::to_string (getKeyCode ()) + ", mods: " + std::to_string (getMods ());
}
}
