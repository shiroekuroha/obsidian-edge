#pragma once

#include "event.h"

namespace ObsidianEdge {
class WindowGainedFocusEvent : public Event {
public:
    EVENT_DECLARE_HELPER(WindowGainedFocus)
};

class WindowLostFocusEvent : public Event {
public:
    EVENT_DECLARE_HELPER(WindowLostFocus)
};

class WindowMovedEvent : public Event {
public:
    WindowMovedEvent(const Vector2i location);

    EVENT_DECLARE_HELPER(WindowMoved)

    [[nodiscard]] auto getLocation() const -> Vector2i;

    [[nodiscard]] auto getX() const -> int;
    [[nodiscard]] auto getY() const -> int;

private:
    Vector2i m_location = {0, 0};
};

class WindowResizedEvent : public Event {
public:
    WindowResizedEvent(const Vector2i size);

    EVENT_DECLARE_HELPER(WindowResized)

    [[nodiscard]] auto getSize() const -> Vector2i;

    [[nodiscard]] auto getWidth() const -> int;
    [[nodiscard]] auto getHeight() const -> int;

private:
    Vector2i m_size = {0, 0};
};

class WindowClosedEvent : public Event {
public:
    EVENT_DECLARE_HELPER(WindowClosed)
};
} // namespace ObsidianEdge
