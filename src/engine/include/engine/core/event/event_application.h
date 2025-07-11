#pragma once

#include "engine/core/event/event.h"

namespace ObsidianEdge {
class WindowGainedFocus : public Event {
   public:
    WindowGainedFocus() = default;

    EVENT_CLASS_TYPE(WindowGainedFocus)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)

    std::string toString() const override {
        std::stringstream ss;
        ss << "WindowGainedFocus!";

        return ss.str();
    }
};

class WindowLostFocus : public Event {
   public:
    WindowLostFocus() = default;

    EVENT_CLASS_TYPE(WindowLostFocus)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)

    std::string toString() const override {
        std::stringstream ss;
        ss << "WindowLostFocus!";

        return ss.str();
    }
};

class WindowMoved : public Event {
   public:
    WindowMoved(unsigned int newX, unsigned int newY)
        : m_newX(newX), m_newY(newY) {}

    unsigned int getNewX() const { return m_newX; }
    unsigned int getNewY() const { return m_newY; }

    EVENT_CLASS_TYPE(WindowMoved)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)

    std::string toString() const override {
        std::stringstream ss;
        ss << "WindowMoved: New Location(" << m_newX << ", "
           << m_newY << ")";

        return ss.str();
    }

   private:
    unsigned int m_newX, m_newY;
    int m_relX, m_relY;
};

class WindowResizedEvent : public Event {
   public:
    WindowResizedEvent(unsigned int width, unsigned int height)
        : m_width(width), m_height(height) {}

    unsigned int getWidth() const { return m_width; }
    unsigned int getHeight() const { return m_height; }

    EVENT_CLASS_TYPE(WindowResized)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)

    std::string toString() const override {
        std::stringstream ss;
        ss << "WindowResizedEvent: " << m_width << ", "
           << m_height;

        return ss.str();
    }

   private:
    unsigned int m_width, m_height;
};

class WindowClosedEvent : public Event {
   public:
    WindowClosedEvent() = default;

    EVENT_CLASS_TYPE(WindowClosed)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class AppTickEvent : public Event {
   public:
    AppTickEvent() = default;

    EVENT_CLASS_TYPE(AppTick)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class AppUpdateEvent : public Event {
   public:
    AppUpdateEvent() = default;

    EVENT_CLASS_TYPE(AppUpdate)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class AppRenderEvent : public Event {
   public:
    AppRenderEvent() = default;

    EVENT_CLASS_TYPE(AppRender)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};
}  // namespace ObsidianEdge
