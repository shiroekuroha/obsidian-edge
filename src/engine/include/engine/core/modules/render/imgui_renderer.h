#pragma once

// ! This order matters!
// clang-format off
#include "glad/gl.h"
#include "GLFW/glfw3.h"
// clang-format on

#include "engine/core/core.h"
#include "engine/core/modules/log/logger.h"
#include "engine/core/modules/render/render.h"

#include "backends/imgui_impl_glfw.h"

// * OpenGL:
#include "backends/imgui_impl_opengl3.h"
#include "engine/core/modules/render/platform/imgui_opengl_renderer.h"

// TODO: Release these files for Vulkan build
// * Vulkan:
// #include "backends/imgui_impl_vulkan.h"
// #include "engine/core/modules/render/platform/imgui_vulkan_renderer.h"

namespace ObsidianEdge
{
class ImGuiRenderer
{
public:
    static void init ();
};
}
