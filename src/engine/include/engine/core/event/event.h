#pragma once

#include <cstdint>
#include <string_view>

#define BIT(x) (1 << x)

namespace ObsidianEdge
{

enum class EventType
{
    None = 0,

    // Windows Events
    WindowGainedFocus,
    WindowLostFocus,
    WindowMoved,
    WindowResized,
    WindowClosed,

    // Key Events
    KeyPressed,
    KeyReleased,

    // Mouse Events
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
    None = 0,

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

    // For debugging purposes, use getEventType to resolve event!
    virtual std::string_view getEventName () const = 0;

    virtual EventType getEventType () const = 0;
    virtual EventCategory getEventCategories () const = 0;

    bool isInCategory (EventCategory category) const;

    // For debugging purposes, do not use on production build
    virtual std::string toString () const = 0;

    bool isHandled = false;
};

/**
 * @brief Event resolver, marking the event resolved
 */
class EventDispatcher
{
  public:
    EventDispatcher (Event &event) : m_event (event) {}
    template <typename T, typename F>
    bool
    dispatch (const F &func)
    {
        if (m_event.getEventType () == T::getStaticType ())
            {
                m_event.isHandled |= func (static_cast<T &> (m_event));
                return true;
            }
        return false;
    }

  private:
    Event &m_event;
};

#define EVENT_DECLARE_HELPER(eventType)                                       \
    virtual std::string_view getEventName () const override;                  \
                                                                              \
    virtual EventType getEventType () const override;                         \
    virtual EventCategory getEventCategories () const override;               \
                                                                              \
    static EventType getStaticType () { return EventType::eventType; }        \
                                                                              \
    virtual std::string toString () const override;

#define EVENT_DEFINE_HELPER(eventName, eventClass, categoryFlags)             \
    std::string_view eventClass::getEventName () const { return #eventName; } \
                                                                              \
    EventType eventClass::getEventType () const                               \
    {                                                                         \
        return EventType::eventName;                                          \
    }                                                                         \
                                                                              \
    EventCategory eventClass::getEventCategories () const                     \
    {                                                                         \
        return static_cast<EventCategory> (categoryFlags);                    \
    }

} // namespace ObsidianEdge
