#include <obsidian/core/data/pch.h>

#include "obsidian/core/event/event.h"

namespace ObsidianEdge
{
auto
Event::getEventName () const -> String
{
    return "Base Event";
}

auto
Event::getEventType () const -> EventType
{
    return EventType::BaseEvent;
}

auto
Event::getEventCategoryFlags () const -> EventCategory
{
    return EventCategory::EventCategoryGeneric;
}

auto
Event::getStaticType () -> EventType
{
    return EventType::BaseEvent;
}

auto
Event::toString () const -> String
{
    return "Base Event";
}

auto
Event::isInCategory (EventCategory category) const -> bool
{
    return category & getEventCategoryFlags ();
}

auto
Event::isHandled () const -> bool
{
    return m_isHandled;
}

auto
EventDispatcher::isHandled () const -> bool
{
    return m_event->m_isHandled;
}
} // namespace ObsidianEdge
