#include <engine/core/pch.h>

#include "engine/core/modules/render/platform/imgui_opengl_renderer.h"

namespace ObsidianEdge
{
#if defined(IMGUI_IMPL_OPENGL_ES2)
static const char *glsl_version = "#version 100";
#elif defined(IMGUI_IMPL_OPENGL_ES3)
static const char *glsl_version = "#version 300 es";
#else
static const char *glsl_version = "#version 130";
#endif

const char *
ImGuiOpenGlRenderer::getGlslVersion ()
{
    return glsl_version;
}

void
ImGuiOpenGlRenderer::init ()
{
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100 (WebGL 1.0)
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint (GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(IMGUI_IMPL_OPENGL_ES3)
    // GL ES 3.0 + GLSL 300 es (WebGL 2.0)
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint (GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#else
    // GL 3.0 + GLSL 130
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // 3.0+ only
#endif
}
}
