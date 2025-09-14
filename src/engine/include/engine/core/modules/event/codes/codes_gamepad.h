#pragma once

namespace ObsidianEdge
{
namespace Input
{
using GamepadCode = unsigned int;

enum : GamepadCode
{
    GAMEPAD_A = 0,
    GAMEPAD_B = 1,
    GAMEPAD_X = 2,
    GAMEPAD_Y = 3,
    GAMEPAD_LEFT_BUMPER = 4,
    GAMEPAD_RIGHT_BUMPER = 5,
    GAMEPAD_BACK = 6,
    GAMEPAD_START = 7,
    GAMEPAD_GUIDE = 8,
    GAMEPAD_LEFT_THUMB = 9,
    GAMEPAD_RIGHT_THUMB = 10,
    GAMEPAD_DPAD_UP = 11,
    GAMEPAD_DPAD_RIGHT = 12,
    GAMEPAD_DPAD_DOWN = 13,
    GAMEPAD_DPAD_LEFT = 14,

    GAMEPAD_CROSS = GAMEPAD_A,
    GAMEPAD_CIRCLE = GAMEPAD_B,
    GAMEPAD_SQUARE = GAMEPAD_X,
    GAMEPAD_TRIANGLE = GAMEPAD_Y,
};
} // namespace Input
} // namespace ObsidianEdge
