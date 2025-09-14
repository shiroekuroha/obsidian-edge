#include <engine/core/pch.h>

#include "engine/core/modules/render/render.h"

namespace ObsidianEdge
{
RenderAPI Render::s_api = RenderAPI::OPENGL;

void
Render::setRenderAPI (RenderAPI api)
{
    s_api = api;
}

RenderAPI
Render::getRenderAPI ()
{
    return s_api;
}
}
