#pragma once

#include "codes/codes_mouse.h"
#include "event.h"

namespace ObsidianEdge {
/**
 * @brief General Mouse Button Event
 */
class OE_API MouseButtonEvent : public Event {
public:
    /**
     * @brief Construct a new Mouse Button Event object
     *
     * @param mouseCode Mouse Code
     */
    MouseButtonEvent(Input::MouseCode mouseCode);

    EVENT_DECLARE_HELPER(MouseButton)

    /**
     * @brief Get the Mouse Code object
     *
     * @return Input::MouseCode
     */
    [[nodiscard]] auto getMouseCode() const -> Input::MouseCode;

private:
    Input::MouseCode m_mouseCode = 0;
};

/**
 * @brief Mouse button pressed event
 */
class OE_API MouseButtonPressedEvent : public MouseButtonEvent {
public:
    /**
     * @brief Construct a new Mouse Button Pressed Event object
     *
     * @param mouseCode Mouse button pressed code \ref ObsidianEdge::Input::MouseCode
     */
    MouseButtonPressedEvent(Input::MouseCode mouseCode);

    EVENT_DECLARE_HELPER(MouseButtonPressed)
};

/**
 * @brief Mouse button released event
 */
class OE_API MouseButtonReleasedEvent : public MouseButtonEvent {
public:
    /**
     * @brief Construct a new Mouse Button Released Event object
     *
     * @param mouseCode Mouse button released code \ref ObsidianEdge::Input::MouseCode
     */
    MouseButtonReleasedEvent(Input::MouseCode mouseCode);

    EVENT_DECLARE_HELPER(MouseButtonReleased)
};

/**
 * @brief Mouse motion/moved event
 */
class OE_API MouseMovedEvent : public Event {
public:
    /**
     * @brief Construct a new Mouse Moved Event object
     *
     * @param position Position of the mouse cursor on the window
     */
    MouseMovedEvent(Vector2 position);

    EVENT_DECLARE_HELPER(MouseMoved)

    /**
     * @brief Get the position of the mouse cursor on the window
     *
     * @return Vector2 Position of the mouse cursor on the window
     */
    [[nodiscard]] auto getPosition() const -> Vector2;

    /**
     * @brief Get x position of mouse cursor
     * @warning Legacy feature: use \ref MouseMovedEvent::getPosition() instead
     *
     * @return float X position of mouse cursor
     */
    [[nodiscard]] auto getX() const -> float;

    /**
     * @brief Get y position of mouse cursor
     * @warning Legacy feature: use \ref MouseMovedEvent::getPosition() instead
     *
     * @return float Y position of mouse cursor
     */
    [[nodiscard]] auto getY() const -> float;

private:
    Vector2 m_position = {0, 0};
};

/**
 * @brief Mouse scroll event
 */
class OE_API MouseScrolledEvent : public Event {
public:
    /**
     * @brief Construct a new Mouse Scrolled Event object
     *
     * @param offset Number of steps scrolled, both x and y
     */
    MouseScrolledEvent(Vector2 offset);

    EVENT_DECLARE_HELPER(MouseScrolled)

    /**
     * @brief Get the offset of the mouse scroll
     *
     * @return Vector2 Offset of the mouse scroll
     */
    [[nodiscard]] auto getOffset() const -> Vector2;

    /**
     * @brief Get x offset of mouse scroll
     * @warning Legacy feature: use \ref MouseScrolledEvent::getOffset() instead
     *
     * @return float X offset of mouse cursor
     */
    [[nodiscard]] auto getX() const -> float;

    /**
     * @brief Get y offset of mouse scroll
     * @warning Legacy feature: use \ref MouseScrolledEvent::getOffset() instead
     *
     * @return float Y offset of mouse cursor
     */
    [[nodiscard]] auto getY() const -> float;

private:
    Vector2 m_offset{0.0f, 0.0f};
};
} // namespace ObsidianEdge
