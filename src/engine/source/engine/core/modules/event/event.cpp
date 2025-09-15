#include <engine/core/pch.h>

#include "engine/core/modules/event/event.h"

namespace ObsidianEdge
{
std::string_view
Event::getEventName () const
{
    return "Base Event";
}

EventType
Event::getEventType () const
{
    return EventType::BaseEvent;
}

EventType
Event::getStaticType ()
{
    return EventType::BaseEvent;
}

EventCategory
Event::getEventCategoryFlags () const
{
    return EventCategory::EventCategoryGeneric;
}

bool
Event::isInCategory (EventCategory category) const
{
    return category & getEventCategoryFlags ();
}

bool
Event::isHandled () const
{
    return m_isHandled;
}

std::string
Event::toString () const
{
    return "Base Event";
}

bool
EventDispatcher::isHandled () const
{
    return m_event.m_isHandled;
}
} // namespace ObsidianEdge
