#pragma once
namespace ObsidianEdge::Input
{
using MouseCode = unsigned int;

enum : MouseCode
{
    MOUSE_1 = 0,
    MOUSE_2 = 1,
    MOUSE_3 = 2,
    MOUSE_4 = 3,
    MOUSE_5 = 4,
    MOUSE_6 = 5,
    MOUSE_7 = 6,
    MOUSE_8 = 7,

    MOUSE_LEFT = MOUSE_1,
    MOUSE_RIGHT = MOUSE_2,
    MOUSE_MIDDLE = MOUSE_3,
    MOUSE_LAST = MOUSE_8,
};
} // namespace ObsidianEdge::Input

