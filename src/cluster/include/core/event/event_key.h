#pragma once

#include "codes/codes_key.h"
#include "event.h"

namespace ObsidianEdge {
/**
 * @brief Modifier key encapsulated, for internal use only
 */
enum class OE_API ModKey : uint8_t { None = 0, Shift, Control, Alt, Super, Caps_lock, Num_lock };

/**
 * @brief General key event
 */
class OE_API KeyEvent : public Event {
public:
    /**
     * @brief Construct a new Key Event object
     *
     * @param keyCode Key code of the event \ref ObsidianEdge::Input::KeyCode
     * @param mods Key modifiers of the event \ref ObsidianEdge::ModKey
     */
    KeyEvent(Input::KeyCode keyCode, int mods);

    EVENT_DECLARE_HELPER(Key)

    /**
     * @brief Get the Key Code object
     *
     * @return Input::KeyCode Key code recorded in the event
     */
    [[nodiscard]] auto getKeyCode() const -> Input::KeyCode;

    /**
     * @brief Get the Modifiers object
     *
     * @return int Key modifier flags, contains multiple modifiers
     */
    [[nodiscard]] auto getModifiers() const -> int;

    /**
     * @brief Check if modkey is in the key modifier list
     *
     * @param modkey Modifier key to check
     * @return true Modifier key is being held down
     * @return false Modifier key is not being held down
     */
    [[nodiscard]] auto hasModifier(ModKey modkey) const -> bool;

private:
    Input::KeyCode m_keyCode = 0;
    int m_mods = 0;
};

/**
 * @brief Key pressed event
 */
class OE_API KeyPressedEvent : public KeyEvent {
public:
    /**
     * @brief Construct a new Key Pressed Event object
     *
     * @param keyCode Key code of key pressed
     * @param mods Key modifiers list
     * @param isRepeated Is the key being hold down?
     */
    KeyPressedEvent(Input::KeyCode keyCode, int mods, bool isRepeated = false);

    EVENT_DECLARE_HELPER(KeyPressed)

    /**
     * @brief Check if the event is standalone or a follow up of previous event. I.E. being held down
     *
     * @return true Key is being held down
     * @return false Key first occurrence
     */
    [[nodiscard]] auto isRepeated() const -> bool;

private:
    bool m_isRepeated = false;
};

/**
 * @brief Key released event
 */
class OE_API KeyReleasedEvent : public KeyEvent {
public:
    /**
     * @brief Construct a new Key Released Event object
     *
     * @param keyCode Key code of key released
     * @param mods Key modifiers list
     */
    KeyReleasedEvent(Input::KeyCode keyCode, int mods);

    EVENT_DECLARE_HELPER(KeyReleased)
};
} // namespace ObsidianEdge
