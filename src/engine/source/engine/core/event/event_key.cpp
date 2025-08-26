#include "engine/core/event/event_key.h"

namespace ObsidianEdge
{
KeyEvent::KeyEvent (Input::KeyCode keyCode) : m_keyCode (keyCode) {}

EVENT_DEFINE_HELPER (Key, EventCategoryInput | EventCategoryKeyboard)

Input::KeyCode
KeyEvent::getKeyCode () const
{
    return m_keyCode;
}

std::string
KeyEvent::toString () const
{
    return "Base Key Event";
}

KeyPressedEvent::KeyPressedEvent (Input::KeyCode keyCode, bool isRepeated) : KeyEvent (keyCode), m_isRepeated (isRepeated)
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
    return "Key Pressed, Key Code: " + std::to_string (getKeyCode ()) + (isRepeated () ? ", is repeated" : "");
}

KeyReleasedEvent::KeyReleasedEvent (Input::KeyCode keyCode) : KeyEvent (keyCode) {}

EVENT_DEFINE_HELPER (KeyReleased, EventCategoryInput | EventCategoryKeyboard)

std::string
KeyReleasedEvent::toString () const
{
    return "Key Released, Key Code: " + std::to_string (getKeyCode ());
}
}
