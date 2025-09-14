#include <engine/core/pch.h>

#include "engine/core/modules/event/event_gamepad.h"

namespace ObsidianEdge
{
// GamepadButtonEvent
GamepadButtonEvent::GamepadButtonEvent (Input::GamepadCode gamepadCode, int controller)
    : m_code (gamepadCode), m_controller (controller)
{
}

EVENT_DEFINE_HELPER (GamepadButton, EventCategoryInput | EventCategoryGamepad | EventCategoryGamepadButton)

Input::GamepadCode
GamepadButtonEvent::getGamepadCode () const
{
    return m_code;
}

int
GamepadButtonEvent::getControllerIndex () const
{
    return m_controller;
}

std::string
GamepadButtonEvent::toString () const
{
    return "Base Gamepad Button Event";
}

// GamepadButtonPressedEvent
GamepadButtonPressedEvent::GamepadButtonPressedEvent (Input::GamepadCode gamepadCode, int controller)
    : GamepadButtonEvent (gamepadCode, controller)
{
}

EVENT_DEFINE_HELPER (GamepadButtonPressed, EventCategoryInput | EventCategoryGamepad | EventCategoryGamepadButton)

std::string
GamepadButtonPressedEvent::toString () const
{
    return "Gamepad Button Pressed(controller: " + std::to_string (getControllerIndex ())
           + "): " + std::to_string (getGamepadCode ());
}

// GamepadButtonReleasedEvent
GamepadButtonReleasedEvent::GamepadButtonReleasedEvent (Input::GamepadCode gamepadCode, int controller)
    : GamepadButtonEvent (gamepadCode, controller)
{
}

EVENT_DEFINE_HELPER (GamepadButtonReleased, EventCategoryInput | EventCategoryGamepad | EventCategoryGamepadButton)

std::string
GamepadButtonReleasedEvent::toString () const
{
    return "Gamepad Button Released(controller: " + std::to_string (getControllerIndex ())
           + "): " + std::to_string (getGamepadCode ());
}

// GamepadLeftJoystickMovedEvent
GamepadLeftJoystickMovedEvent::GamepadLeftJoystickMovedEvent (Vector2 offset, int controller)
    : m_offset (offset), m_controller (controller)
{
}

EVENT_DEFINE_HELPER (GamepadLeftJoystickMoved, EventCategoryInput | EventCategoryGamepad)

Vector2
GamepadLeftJoystickMovedEvent::getOffset () const
{
    return m_offset;
}

float
GamepadLeftJoystickMovedEvent::getX () const
{
    return m_offset.x;
}

float
GamepadLeftJoystickMovedEvent::getY () const
{
    return m_offset.y;
}

int
GamepadLeftJoystickMovedEvent::getControllerIndex () const
{
    return m_controller;
}

std::string
GamepadLeftJoystickMovedEvent::toString () const
{
    return "Gamepad Left Joystick Moved(controller: " + std::to_string (getControllerIndex ())
           + "): x: " + std::to_string (getX ()) + ", y: " + std::to_string (getY ());
}

// GamepadRightJoystickMovedEvent
GamepadRightJoystickMovedEvent::GamepadRightJoystickMovedEvent (Vector2 offset, int controller)
    : m_offset (offset), m_controller (controller)
{
}

EVENT_DEFINE_HELPER (GamepadRightJoystickMoved, EventCategoryInput | EventCategoryGamepad)

Vector2
GamepadRightJoystickMovedEvent::getOffset () const
{
    return m_offset;
}

float
GamepadRightJoystickMovedEvent::getX () const
{
    return m_offset.x;
}

float
GamepadRightJoystickMovedEvent::getY () const
{
    return m_offset.y;
}

int
GamepadRightJoystickMovedEvent::getControllerIndex () const
{
    return m_controller;
}

std::string
GamepadRightJoystickMovedEvent::toString () const
{
    return "Gamepad Right Joystick Moved(controller: " + std::to_string (getControllerIndex ())
           + "): x: " + std::to_string (getX ()) + ", y: " + std::to_string (getY ());
}

// GamepadLeftTriggerPulledEvent
GamepadLeftTriggerPulledEvent::GamepadLeftTriggerPulledEvent (float strength, int controller)
    : m_strength (strength), m_controller (controller)
{
}

EVENT_DEFINE_HELPER (GamepadLeftTriggerPulled, EventCategoryInput | EventCategoryGamepad)

float
GamepadLeftTriggerPulledEvent::getStrength () const
{
    return m_strength;
}

int
GamepadLeftTriggerPulledEvent::getControllerIndex () const
{
    return m_controller;
}

std::string
GamepadLeftTriggerPulledEvent::toString () const
{
    return "Gamepad Left Trigger Moved(controller: " + std::to_string (getControllerIndex ())
           + "): strength: " + std::to_string (getStrength ());
}

// GamepadRightTriggerPulledEvent
GamepadRightTriggerPulledEvent::GamepadRightTriggerPulledEvent (float strength, int controller)
    : m_strength (strength), m_controller (controller)
{
}

EVENT_DEFINE_HELPER (GamepadRightTriggerPulled, EventCategoryInput | EventCategoryGamepad)

float
GamepadRightTriggerPulledEvent::getStrength () const
{
    return m_strength;
}

int
GamepadRightTriggerPulledEvent::getControllerIndex () const
{
    return m_controller;
}

std::string
GamepadRightTriggerPulledEvent::toString () const
{
    return "Gamepad Right Trigger Moved(controller: " + std::to_string (getControllerIndex ())
           + "): strength: " + std::to_string (getStrength ());
}
}
