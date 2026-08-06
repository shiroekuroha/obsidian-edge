#pragma once
namespace ObsidianEdge::Input {
/**
 * @brief Mouse Code for Engine, copied from GLFW
 */
using MouseCode = uint8_t;

enum : MouseCode {
    Mouse1 = 0,
    Mouse2 = 1,
    Mouse3 = 2,
    Mouse4 = 3,
    Mouse5 = 4,
    Mouse6 = 5,
    Mouse7 = 6,
    Mouse8 = 7,

    MouseLeft = Mouse1,
    MouseRight = Mouse2,
    MouseMiddle = Mouse3,
    MouseLast = Mouse8,
};
} // namespace ObsidianEdge::Input
