
#include "core/event/event_key.h"
#include <pch.h>

#include <GLFW/glfw3.h>

namespace ObsidianEdge {
KeyEvent::KeyEvent(Input::KeyCode keyCode, int mods) : m_keyCode(keyCode), m_mods(mods) {}

EVENT_DEFINE_HELPER(Key, EventCategoryInput | EventCategoryKeyboard)

auto KeyEvent::getKeyCode() const -> Input::KeyCode { return m_keyCode; }

auto KeyEvent::getModifiers() const -> int { return m_mods; }

auto KeyEvent::hasModifier(ModKey key) const -> bool {
    switch (key) {
    case ModKey::Shift:
        return m_mods & GLFW_MOD_SHIFT;
        break;

    case ModKey::Control:
        return m_mods & GLFW_MOD_CONTROL;
        break;

    case ModKey::Alt:
        return m_mods & GLFW_MOD_ALT;
        break;

    case ModKey::Super:
        return m_mods & GLFW_MOD_SUPER;
        break;

    case ModKey::Caps_lock:
        return m_mods & GLFW_MOD_CAPS_LOCK;
        break;

    case ModKey::Num_lock:
        return m_mods & GLFW_MOD_NUM_LOCK;
        break;

    default:
        break;
    }

    return false;
}

auto KeyEvent::toString() const -> std::string { return "Base Key Event"; }

KeyPressedEvent::KeyPressedEvent(Input::KeyCode keyCode, int mods, bool isRepeated)
    : KeyEvent(keyCode, mods), m_isRepeated(isRepeated) {}

EVENT_DEFINE_HELPER(KeyPressed, EventCategoryInput | EventCategoryKeyboard)

auto KeyPressedEvent::isRepeated() const -> bool { return m_isRepeated; }

auto KeyPressedEvent::toString() const -> std::string {
    return "Key Pressed, Key Code: " + std::to_string(getKeyCode()) + ", mods: " + std::to_string(getModifiers()) +
           (isRepeated() ? ", is repeated" : "");
}

KeyReleasedEvent::KeyReleasedEvent(Input::KeyCode keyCode, int mods) : KeyEvent(keyCode, mods) {}

EVENT_DEFINE_HELPER(KeyReleased, EventCategoryInput | EventCategoryKeyboard)

auto KeyReleasedEvent::toString() const -> std::string {
    return "Key Released, Key Code: " + std::to_string(getKeyCode()) + ", mods: " + std::to_string(getModifiers());
}
} // namespace ObsidianEdge
