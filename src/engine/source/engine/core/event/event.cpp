#include "engine/core/event/event.h"

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
    return EventType::None;
}

EventCategory
Event::getEventCategories () const
{
    return None;
}

bool
Event::isInCategory (EventCategory category) const
{
    return category & getEventCategories ();
}

std::string
Event::toString () const
{
    return "Base Event";
}

} // namespace ObsidianEdge