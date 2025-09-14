#pragma once

#include "engine/core/modules/data/vector/vector2.h"
#include "engine/core/modules/data/vector/vector2i.h"
#include "engine/core/modules/event/codes/codes_gamepad.h"
#include "engine/core/modules/event/event.h"

namespace ObsidianEdge
{
class GamepadButtonEvent : public Event
{
public:
    GamepadButtonEvent (Input::GamepadCode gamepadCode, int controller);
    virtual ~GamepadButtonEvent () = default;

    EVENT_DECLARE_HELPER (GamepadButton)

    Input::GamepadCode getGamepadCode () const;
    int getControllerIndex () const;

private:
    Input::GamepadCode m_code;
    int m_controller;
};

class GamepadButtonPressedEvent : public GamepadButtonEvent
{
public:
    GamepadButtonPressedEvent (Input::GamepadCode gamepadCode, int controller);
    virtual ~GamepadButtonPressedEvent () = default;

    EVENT_DECLARE_HELPER (GamepadButtonPressed)
};

class GamepadButtonReleasedEvent : public GamepadButtonEvent
{
public:
    GamepadButtonReleasedEvent (Input::GamepadCode gamepadCode, int controller);
    virtual ~GamepadButtonReleasedEvent () = default;

    EVENT_DECLARE_HELPER (GamepadButtonReleased)
};

class GamepadLeftJoystickMovedEvent : public Event
{
public:
    GamepadLeftJoystickMovedEvent (Vector2 offset, int controller);
    virtual ~GamepadLeftJoystickMovedEvent () = default;

    EVENT_DECLARE_HELPER (GamepadLeftJoystickMoved)

    Vector2 getOffset () const;
    float getX () const;
    float getY () const;
    int getControllerIndex () const;

private:
    Vector2 m_offset;
    int m_controller;
};

class GamepadRightJoystickMovedEvent : public Event
{
public:
    GamepadRightJoystickMovedEvent (Vector2 offset, int controller);
    virtual ~GamepadRightJoystickMovedEvent () = default;

    EVENT_DECLARE_HELPER (GamepadRightJoystickMoved)

    Vector2 getOffset () const;
    float getX () const;
    float getY () const;
    int getControllerIndex () const;

private:
    Vector2 m_offset;
    int m_controller;
};

class GamepadLeftTriggerPulledEvent : public Event
{
public:
    GamepadLeftTriggerPulledEvent (float strength, int controller);
    virtual ~GamepadLeftTriggerPulledEvent () = default;

    EVENT_DECLARE_HELPER (GamepadLeftTriggerPulled)

    float getStrength () const;
    int getControllerIndex () const;

private:
    float m_strength;
    int m_controller;
};

class GamepadRightTriggerPulledEvent : public Event
{
public:
    GamepadRightTriggerPulledEvent (float strength, int controller);
    virtual ~GamepadRightTriggerPulledEvent () = default;

    EVENT_DECLARE_HELPER (GamepadRightTriggerPulled)

    float getStrength () const;
    int getControllerIndex () const;

private:
    float m_strength;
    int m_controller;
};
}
