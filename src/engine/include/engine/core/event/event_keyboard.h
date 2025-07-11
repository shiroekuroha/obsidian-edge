#pragma once

#include "engine/core/event/event.h"
#include "engine/core/event/input_codes.h"

namespace ObsidianEdge {
class KeyEvent : public Event {
   public:
    Input::KeyCode getkeyCode() const { return m_keyCode; }

    EVENT_CLASS_CATEGORY(
        EventCategoryKeyboard | EventCategoryInput)

   protected:
    KeyEvent(const Input::KeyCode keyCode)
        : m_keyCode(keyCode) {}

    Input::KeyCode m_keyCode;
};

class KeyPressedEvent : public KeyEvent {
   public:
    KeyPressedEvent(
        const Input::KeyCode keyCode, bool isRepeat = false)
        : KeyEvent(keyCode), m_isRepeat(isRepeat) {}

    bool IsRepeat() const { return m_isRepeat; }

    std::string toString() const override {
        std::stringstream ss;
        ss << "KeyPressedEvent: " << m_keyCode
           << " (repeat = " << m_isRepeat << ")";
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyPressed)
   private:
    bool m_isRepeat;
};

class KeyReleasedEvent : public KeyEvent {
   public:
    KeyReleasedEvent(const Input::KeyCode keyCode)
        : KeyEvent(keyCode) {}

    std::string toString() const override {
        std::stringstream ss;
        ss << "KeyReleasedEvent: " << m_keyCode;
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyReleased)
};

class KeyTypedEvent : public KeyEvent {
   public:
    KeyTypedEvent(const Input::KeyCode keyCode)
        : KeyEvent(keyCode) {}

    std::string toString() const override {
        std::stringstream ss;
        ss << "KeyTypedEvent: " << m_keyCode;
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyTyped)
};
}  // namespace ObsidianEdge
