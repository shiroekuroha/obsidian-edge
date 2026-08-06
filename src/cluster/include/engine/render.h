#pragma once

#include "core.h"

#include "core/ecs/scene.h"

// ! This order matters!
// clang-format off
#include <glad/gl.h>
#include <GLFW/glfw3.h>
// clang-format on

namespace ObsidianEdge {
void OE_API renderLoop(GLFWwindow *window, const std::atomic<bool> &isRunning,
                       std::atomic<std::vector<RenderObjData> *> &sharedRenderObjData, std::atomic<bool> &swapReady);
} // namespace ObsidianEdge
