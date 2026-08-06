#pragma once

#include "event.h"

namespace ObsidianEdge {
/**
 * @brief Window gained focus
 */
class OE_API WindowGainedFocusEvent : public Event {
public:
    EVENT_DECLARE_HELPER(WindowGainedFocus)
};

/**
 * @brief Window lost focus
 */
class OE_API WindowLostFocusEvent : public Event {
public:
    EVENT_DECLARE_HELPER(WindowLostFocus)
};

/**
 * @brief Window moved to new position
 */
class OE_API WindowMovedEvent : public Event {
public:
    /**
     * @brief Construct a new Window Moved Event object
     *
     * @param position Position of the window
     */
    WindowMovedEvent(Vector2i position);

    EVENT_DECLARE_HELPER(WindowMoved)

    /**
     * @brief Get the Position of the window
     *
     * @return Vector2i Position of the window
     */
    [[nodiscard]] auto getPosition() const -> Vector2i;

    /**
     * @brief Get x position of the window
     * @warning Legacy Feature: use \ref ObsidianEdge::WindowMovedEvent::getPosition()
     *
     * @return int X position of the window
     */
    [[nodiscard]] auto getX() const -> int;

    /**
     * @brief Get y position of the window
     * @warning Legacy Feature: use \ref ObsidianEdge::WindowMovedEvent::getPosition()
     *
     * @return int Y position of the window
     */
    [[nodiscard]] auto getY() const -> int;

private:
    Vector2i m_position = {0, 0};
};

/**
 * @brief Window resized to new dimensions
 */
class OE_API WindowResizedEvent : public Event {
public:
    /**
     * @brief Construct a new Window Resized Event object
     *
     * @param dimensions New dimensions of the window
     */
    WindowResizedEvent(Point2 dimensions);

    EVENT_DECLARE_HELPER(WindowResized)

    /**
     * @brief Get the Dimensions of the window
     *
     * @return Point2 Dimensions of the window
     */
    [[nodiscard]] auto getDimensions() const -> Point2;

    /**
     * @brief Get the Width of the window
     * @warning Legacy Feature: use \ref ObsidianEdge::WindowResizedEvent::getDimensions()
     *
     * @return unsigned int X Dimension of the window
     */
    [[nodiscard]] auto getWidth() const -> unsigned int;

    /**
     * @brief Get the Height of the window
     * @warning Legacy Feature: use \ref ObsidianEdge::WindowResizedEvent::getDimensions()
     *
     * @return unsigned int Y Dimension of the window
     */
    [[nodiscard]] auto getHeight() const -> unsigned int;

private:
    Point2 m_dimensions = {0, 0};
};

/**
 * @brief Window maximized event
 */
class OE_API WindowMaximizedEvent : public Event {
public:
    EVENT_DECLARE_HELPER(WindowMaximized)
};

/**
 * @brief Window minimized event
 *
 */
class OE_API WindowMinimizedEvent : public Event {
public:
    EVENT_DECLARE_HELPER(WindowMinimized)
};

/**
 * @brief Window restored event, minimized/maximized -> normal
 */
class OE_API WindowRestoredEvent : public Event {
public:
    EVENT_DECLARE_HELPER(WindowRestored)
};

/**
 * @brief Window closed event
 */
class OE_API WindowClosedEvent : public Event {
public:
    EVENT_DECLARE_HELPER(WindowClosed)
};

/**
 * @brief Frame buffer resized, DPI changes and for rendering window size
 */
class OE_API FrameBufferResizedEvent : public Event {
public:
    /**
     * @brief Construct a new Frame Buffer Resized Event object
     *
     * @param dimensions New dimensions of the frame buffer
     */
    FrameBufferResizedEvent(Point2 dimensions);

    EVENT_DECLARE_HELPER(FrameBufferResized)

    /**
     * @brief Get the Dimensions of the frame buffer
     *
     * @return Point2 Dimensions of the frame buffer
     */
    [[nodiscard]] auto getDimensions() const -> Point2;

    /**
     * @brief Get the Width of the frame buffer
     * @warning Legacy Feature: use \ref ObsidianEdge::FrameBufferResizedEvent::getDimensions()
     *
     * @return unsigned int X dimension of the frame buffer
     */
    [[nodiscard]] auto getWidth() const -> unsigned int;

    /**
     * @brief Get the Height of the frame buffer
     * @warning Legacy Feature: use \ref ObsidianEdge::FrameBufferResizedEvent::getDimensions()
     *
     * @return unsigned int Y dimension of the frame buffer
     */
    [[nodiscard]] auto getHeight() const -> unsigned int;

private:
    Point2 m_dimensions{0, 0};
};
} // namespace ObsidianEdge
