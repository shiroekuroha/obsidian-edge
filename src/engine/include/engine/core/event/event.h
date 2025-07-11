#pragma once

namespace ObsidianEdge {
enum class EventType {
    None = 0,

    // Windows Events
    WindowGainedFocus,
    WindowLostFocus,
    WindowMoved,
    WindowResized,
    WindowClosed,

    // App Events
    AppTick,
    AppUpdate,
    AppRender,

    // Key Events
    KeyPressed,
    KeyReleased,
    KeyTyped,

    // Mouse Events
    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseScrolled,
};

enum EventCategory {
    None = 0,

    EventCategoryApplication = 0b0000001,
    EventCategoryInput = 0b0000010,
    EventCategoryKeyboard = 0b0000100,
    EventCategoryMouse = 0b0001000,
    EventCategoryMouseButton = 0b0010000,
    EventCategoryGamepad = 0b0100000,
    EventCategoryGamepadButton = 0b1000000
};

class Event {
   public:
    Event() = default;
    virtual ~Event() = default;

    virtual EventType getEventType() const = 0;
    virtual int getEventCategoryFlags() const = 0;
    virtual const char *getEventName() const = 0;
    virtual std::string toString() const {
        return getEventName();
    }

    bool isInCategory(EventCategory category) {
        return getEventCategoryFlags() & category;
    }

    bool handled = false;
};

class EventDispatcher {
   public:
    EventDispatcher(Event &event) : m_event(event) {}

    template <typename T, typename F>
    bool dispatch(const F &func) {
        if (m_event.getEventType() == T::getStaticType()) {
            m_event.handled |= func(static_cast<T &>(m_event));

            return true;
        }

        return false;
    }

   private:
    Event &m_event;
};

#define EVENT_CLASS_TYPE(type)                                 \
    static EventType getStaticType() {                         \
        return EventType::type;                                \
    }                                                          \
    virtual EventType getEventType() const override {          \
        return getStaticType();                                \
    }                                                          \
    virtual const char *getEventName() const override {        \
        return #type;                                          \
    }

#define EVENT_CLASS_CATEGORY(category)                         \
    virtual int getEventCategoryFlags() const override {       \
        return category;                                       \
    }
}  // namespace ObsidianEdge
