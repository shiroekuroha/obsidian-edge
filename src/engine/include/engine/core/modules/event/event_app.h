#pragma once

#include "engine/core/modules/event/event.h"
#include <glm/vec2.hpp>

namespace ObsidianEdge
{
class WindowGainedFocusEvent : public Event
{
public:
    EVENT_DECLARE_HELPER (WindowGainedFocus)
};

class WindowLostFocusEvent : public Event
{
public:
    EVENT_DECLARE_HELPER (WindowLostFocus)
};

class WindowMovedEvent : public Event
{
public:
    WindowMovedEvent (const glm::ivec2 location);
    virtual ~WindowMovedEvent () = default;

    EVENT_DECLARE_HELPER (WindowMoved)

    glm::ivec2 getLocation () const;

    int getX () const;
    int getY () const;

private:
    glm::ivec2 m_location;
};

class WindowResizedEvent : public Event
{
public:
    WindowResizedEvent (const glm::ivec2 size);
    virtual ~WindowResizedEvent () = default;

    EVENT_DECLARE_HELPER (WindowResized)

    glm::ivec2 getSize () const;

    int getWidth () const;
    int getHeight () const;

private:
    glm::ivec2 m_size;
};

class WindowClosedEvent : public Event
{
public:
    EVENT_DECLARE_HELPER (WindowClosed)
};
}
