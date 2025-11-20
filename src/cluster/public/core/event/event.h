#pragma once

namespace ObsidianEdge {
enum class EventType : std::int8_t {
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
    GamepadButton,
    GamepadButtonPressed,
    GamepadButtonReleased,

    /// Gamepad Axis Events
    GamepadLeftJoystickMoved,
    GamepadRightJoystickMoved,
    GamepadLeftTriggerPulled,
    GamepadRightTriggerPulled,
};

enum EventCategory : std::int8_t {
    // No Category
    EventCategoryGeneric = 0,

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
class Event {
public:
    Event() = default;
    virtual ~Event() = default;

    Event(const Event &other) = default;
    Event(Event &&other) noexcept = default;

    auto operator=(const Event &other) -> Event & = default;
    auto operator=(Event &&other) noexcept -> Event & = default;

    [[nodiscard]] virtual auto getEventName() const -> std::string = 0;
    [[nodiscard]] virtual auto getEventType() const -> EventType = 0;
    [[nodiscard]] virtual auto getEventCategoryFlags() const -> EventCategory = 0;

    static auto getStaticType() -> EventType;

    // For debugging purposes
    [[nodiscard]] virtual auto toString() const -> std::string = 0;

    [[nodiscard]] auto isInCategory(EventCategory category) const -> bool;
    [[nodiscard]] auto isHandled() const -> bool;

    friend class EventDispatcher;

private:
    bool m_isHandled = false;
};

/**
 * @brief Event resolver, marking the event resolved
 */
class EventDispatcher {
public:
    EventDispatcher(Event &event) : m_event(&event) {}

    template <typename T> auto dispatch(std::function<bool(T &)> func) -> bool {
        if (m_event->getEventType() == T::getStaticType()) {
            m_event->m_isHandled |= func(static_cast<T &>(*m_event));

            return true;
        }

        return false;
    }

    [[nodiscard]] auto isHandled() const -> bool;

private:
    gsl::not_null<Event *> m_event; // Simplified
};

#define EVENT_DECLARE_HELPER(eventName)                                                                                        \
    eventName##Event() = default;                                                                                              \
    ~eventName##Event() = default;                                                                                             \
    eventName##Event(const eventName##Event &other) = default;                                                                 \
    eventName##Event(eventName##Event &&other) noexcept = default;                                                             \
    auto operator=(const eventName##Event &other)->eventName##Event & = default;                                               \
    auto operator=(eventName##Event &&other) noexcept -> eventName##Event & = default;                                         \
    [[nodiscard]] virtual auto getEventName() const -> std::string override;                                                   \
    [[nodiscard]] virtual auto getEventType() const -> EventType override;                                                     \
    static auto getStaticType() -> EventType;                                                                                  \
    [[nodiscard]] virtual auto getEventCategoryFlags() const -> EventCategory override;                                        \
    [[nodiscard]] virtual auto toString() const -> std::string override;

#define EVENT_DEFINE_HELPER(eventName, categoryFlags)                                                                          \
    auto eventName##Event::getEventName() const -> std::string { return #eventName; }                                          \
    auto eventName##Event::getEventType() const -> EventType { return EventType::eventName; }                                  \
    auto eventName##Event::getStaticType() -> EventType { return EventType::eventName; }                                       \
    auto eventName##Event::getEventCategoryFlags() const -> EventCategory { return static_cast<EventCategory>(categoryFlags); }

} // namespace ObsidianEdge
