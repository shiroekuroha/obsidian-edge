#include <engine/core/pch.h>

#include "engine/core/modules/render/imgui_renderer.h"

namespace ObsidianEdge
{
void
ImGuiRenderer::init ()
{
    switch (Render::getRenderAPI ())
        {
        case ObsidianEdge::RenderAPI::OPENGL:
            ImGuiOpenGlRenderer::init ();
            break;

        case ObsidianEdge::RenderAPI::VULKAN:
            OE_FATAL ("Vulkan Rendering API is not ready!")
            break;

        default:
            OE_FATAL ("UNKNOWN RENDERING API!")
            break;
        }
}
}
