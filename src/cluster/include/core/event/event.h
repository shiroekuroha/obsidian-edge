#pragma once

#include "core.h"

namespace ObsidianEdge {
/**
 * @brief Event Type, static types, for event dynamic recognition
 */
enum class OE_API EventType : uint8_t {
    // Base Type
    BaseEvent = 0,

    // Windows Events
    /** @brief Window Gained Focus */ WindowGainedFocus,
    /** @brief Window Lost Focus */ WindowLostFocus,
    /** @brief Window Moved */ WindowMoved,
    /** @brief Window Resized */ WindowResized,
    /** @brief Window Closed */ WindowClosed,
    /** @brief Window Maximized */ WindowMaximized,
    /** @brief Window Minimized */ WindowMinimized,
    /** @brief Changed from Maximized or Minimized */ WindowRestored,

    /** @brief Change based on Window Size and DPI */ FrameBufferResized,

    // Key Events
    /** @brief Key */ Key,
    /** @brief Key Pressed */ KeyPressed,
    /** @brief Key Released */ KeyReleased,

    // Mouse Events
    /** @brief Mouse Button */ MouseButton,
    /** @brief Mouse Button Pressed */ MouseButtonPressed,
    /** @brief Mouse Button Released */ MouseButtonReleased,
    /** @brief Mouse Moved */ MouseMoved,
    /** @brief Mouse Scrolled */ MouseScrolled,

    // Gamepad Events
    /** @brief Gamepad Button */ GamepadButton,
    /** @brief Gamepad Button Pressed */ GamepadButtonPressed,
    /** @brief Gamepad Button Released */ GamepadButtonReleased,

    /// Gamepad Axis Events
    /** @brief Gamepad Left Joystick Moved */ GamepadLeftJoystickMoved,
    /** @brief Gamepad Right Joystick Moved */ GamepadRightJoystickMoved,
    /** @brief Gamepad Left Trigger Pulled */ GamepadLeftTriggerPulled,
    /** @brief Gamepad Right Trigger Pulled */ GamepadRightTriggerPulled,
};

/**
 * @brief Event Category, static categories, for event filtering
 */
enum OE_API EventCategory : uint8_t {
    // No Category
    EventCategoryGeneric = 0,

    /** @brief Event Category Application */ EventCategoryApplication = 0b0000001,
    /** @brief Event Category Input */ EventCategoryInput = 0b0000010,
    /** @brief Event Category Keyboard */ EventCategoryKeyboard = 0b0000100,
    /** @brief Event Category Mouse */ EventCategoryMouse = 0b0001000,
    /** @brief Event Category MouseButton */ EventCategoryMouseButton = 0b0010000,
    /** @brief Event Category Gamepad */ EventCategoryGamepad = 0b0100000,
    /** @brief Event Category Gamepad Button */ EventCategoryGamepadButton = 0b1000000,
};

/**
 * @brief Base class for Events
 */
class OE_API Event {
public:
    Event() = default;
    virtual ~Event() = default;
    /**
     * @brief Copy Construct a new Event object
     *
     * @param other
     */
    Event(const Event& other) = default;

    /**
     * @brief Move Construct a new Event object
     *
     * @param other
     */
    Event(Event&& other) noexcept = default;

    /**
     * @brief Copy Assignment
     *
     * @param other
     * @return Event&
     */
    auto operator=(const Event& other) -> Event& = default;

    /**
     * @brief Move Assignment
     *
     * @param other
     * @return Event&
     */
    auto operator=(Event&& other) noexcept -> Event& = default;

    /**
     * @brief Get the Event Name, for debugging
     *
     * @return std::string
     */
    [[nodiscard]] virtual auto getEventName() const -> std::string = 0;

    /**
     * @brief Get the Event Type
     *
     * @return EventType
     */
    [[nodiscard]] virtual auto getEventType() const -> EventType = 0;

    /**
     * @brief Get the Event Category Flags
     *
     * @return EventCategory
     */
    [[nodiscard]] virtual auto getEventCategoryFlags() const -> EventCategory = 0;

    /**
     * @brief Get the Static Type of class
     *
     * @return EventType
     */
    static auto getStaticType() -> EventType;

    /**
     * @brief String message for displaying events
     *
     * @return std::string
     */
    [[nodiscard]] virtual auto toString() const -> std::string = 0;

    /**
     * @brief Filtering event based on it's category flags
     *
     * @param category
     * @return true is in one or more categories
     * @return false is not in any categories
     */
    [[nodiscard]] auto isInCategory(EventCategory category) const -> bool;

    /**
     * @brief Check if event is handled, if not pass event to children
     *
     * @return true
     * @return false
     */
    [[nodiscard]] auto isHandled() const -> bool;

    friend class EventDispatcher;

private:
    bool m_isHandled = false;
};

/**
 * @brief Event resolver, marking the event resolved
 */
class OE_API EventDispatcher {
public:
    /**
     * @brief Construct a new Event Dispatcher object
     *
     * @param event object to resolve
     */
    EventDispatcher(Event& event)
        : m_event(&event) {}

    /**
     * @brief Passing a function to handle the event, function can return true to mark the event as resolved
     *
     * @tparam T
     * @param func
     * @return true
     * @return false
     */
    template <typename T> auto dispatch(std::function<bool(T&)> func) -> bool {
        if (m_event->getEventType() == T::getStaticType()) {
            m_event->m_isHandled |= func(static_cast<T&>(*m_event));

            return true;
        }

        return false;
    }

    /**
     * @brief Check if event already resolved
     *
     * @return true resolved
     * @return false not yet resolve
     */
    [[nodiscard]] auto isHandled() const -> bool;

private:
    Event* m_event; // Simplified
};

/**
 * @brief Generate overloaded functions declaration for derived class
 */
#define EVENT_DECLARE_HELPER(eventName)                                                 \
    eventName##Event() = default;                                                       \
    ~eventName##Event() = default;                                                      \
    eventName##Event(const eventName##Event& other) = default;                          \
    eventName##Event(eventName##Event&& other) noexcept = default;                      \
    auto operator=(const eventName##Event& other)->eventName##Event& = default;         \
    auto operator=(eventName##Event&& other) noexcept -> eventName##Event& = default;   \
    [[nodiscard]] virtual auto getEventName() const -> std::string override;            \
    [[nodiscard]] virtual auto getEventType() const -> EventType override;              \
    static auto getStaticType() -> EventType;                                           \
    [[nodiscard]] virtual auto getEventCategoryFlags() const -> EventCategory override; \
    [[nodiscard]] virtual auto toString() const -> std::string override;

/**
 * @brief Generate overloaded functions definition for derived class
 */
#define EVENT_DEFINE_HELPER(eventName, categoryFlags)                       \
    auto eventName##Event::getEventName() const -> std::string {            \
        return #eventName;                                                  \
    }                                                                       \
    auto eventName##Event::getEventType() const -> EventType {              \
        return EventType::eventName;                                        \
    }                                                                       \
    auto eventName##Event::getStaticType() -> EventType {                   \
        return EventType::eventName;                                        \
    }                                                                       \
    auto eventName##Event::getEventCategoryFlags() const -> EventCategory { \
        return static_cast<EventCategory>(categoryFlags);                   \
    }

} // namespace ObsidianEdge
