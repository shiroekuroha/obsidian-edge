#pragma once

#include <string>
#include <string_view>

namespace ObsidianEdge
{
enum class EventType
{
    // Base Type
    BaseEvent = 0,

    // Windows Events
    WindowGainedFocus,
    WindowLostFocus,
    WindowMoved,
    WindowResized,
    WindowClosed,

    // Key Events
    Key,
    KeyPressed,
    KeyReleased,

    // Mouse Events
    MouseButton,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseScrolled,

    // Gamepad Events
    GamepadButtonPressed,
    GamepadButtonReleased,

    /// Gamepad Axis Events
    GamepadLeftJoystickMoved,
    GamepadRightJoystickMoved,
    GamepadLeftTriggerPulled,
    GamepadRightTriggerPulled,
};

enum EventCategory
{
    // No Category
    EventCategoryGeneric = 0,

    //
    EventCategoryApplication = 0b0000001,
    EventCategoryInput = 0b0000010,
    EventCategoryKeyboard = 0b0000100,
    EventCategoryMouse = 0b0001000,
    EventCategoryMouseButton = 0b0010000,
    EventCategoryGamepad = 0b0100000,
    EventCategoryGamepadButton = 0b1000000,
};

/**
 * @brief Base class for events
 */
class Event
{
public:
    Event () = default;
    virtual ~Event () = default;

    friend class EventDispatcher;

    // For debugging purposes, use getEventType to resolve event!
    virtual std::string_view getEventName () const = 0;
    virtual EventType getEventType () const = 0;
    static EventType getStaticType ();
    virtual EventCategory getEventCategoryFlags () const = 0;

    bool isInCategory (EventCategory category) const;
    bool isHandled () const;

    // For debugging purposes, do not use on production build
    virtual std::string toString () const = 0;

protected:
    bool m_isHandled = false;
};

/**
 * @brief Event resolver, marking the event resolved
 */
class EventDispatcher
{
public:
    EventDispatcher (std::shared_ptr<Event> event) : m_event (event) {}

    template <typename T>
    bool
    dispatch (std::function<bool (T &)> func)
    {
        if (m_event->getEventType () == T::getStaticType ())
            {
                m_event->m_isHandled |= func (static_cast<T &> (*m_event.get ()));

                return true;
            }

        return false;
    }

    bool isHandled () const;

private:
    std::shared_ptr<Event> m_event;
};

#define EVENT_DECLARE_HELPER(eventType)                                                                                    \
    virtual std::string_view getEventName () const override;                                                               \
    virtual EventType getEventType () const override;                                                                      \
    static EventType getStaticType ();                                                                                     \
    virtual EventCategory getEventCategoryFlags () const override;                                                         \
    virtual std::string toString () const override;

#define EVENT_DEFINE_HELPER(eventName, categoryFlags)                                                                      \
    std::string_view eventName##Event::getEventName () const { return #eventName; }                                        \
    EventType eventName##Event::getEventType () const { return EventType::eventName; }                                     \
    EventType eventName##Event::getStaticType () { return EventType::eventName; }                                          \
    EventCategory eventName##Event::getEventCategoryFlags () const { return static_cast<EventCategory> (categoryFlags); }

} // namespace ObsidianEdge
