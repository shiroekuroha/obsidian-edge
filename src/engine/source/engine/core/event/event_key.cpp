#include "engine/core/event/event_key.h"

namespace ObsidianEdge
{
// Class: KeyPressedEvent

KeyPressedEvent::KeyPressedEvent (Input::KeyCode keyCode, bool isRepeated)
    : m_keyCode (keyCode), m_isRepeated (isRepeated)
{
}

EVENT_DEFINE_HELPER (KeyPressed, KeyPressedEvent,
                     (EventCategoryInput | EventCategoryKeyboard))

Input::KeyCode
KeyPressedEvent::getKeyCode () const
{
    return m_keyCode;
}

bool
KeyPressedEvent::isRepeated () const
{
    return m_isRepeated;
}

std::string
KeyPressedEvent::toString () const
{
    std::stringstream sstream;
    sstream << "Key Pressed: KeyCode " << m_keyCode
            << (isRepeated () ? "is repeating" : "");

    return sstream.str ();
}

// Class: KeyReleasedEvent

KeyReleasedEvent::KeyReleasedEvent (Input::KeyCode keyCode)
    : m_keyCode (keyCode)
{
}

EVENT_DEFINE_HELPER (KeyReleased, KeyReleasedEvent,
                     (EventCategoryInput | EventCategoryKeyboard))

Input::KeyCode
KeyReleasedEvent::getKeyCode () const
{
    return m_keyCode;
}

std::string
KeyReleasedEvent::toString () const
{
    std::stringstream sstream;
    sstream << "Key Released: KeyCode " << m_keyCode;

    return sstream.str ();
}
}