#pragma once

namespace ObsidianEdge
{
enum class RenderAPI
{
    OPENGL = 0,
    VULKAN = 1,
    DIRECTX11, // Not supported yet
    DIRECTX12, // Not supported yet
    METAL,     // Not supported yet
};

class Render
{
public:
    static void setRenderAPI (RenderAPI api);
    static RenderAPI getRenderAPI ();

private:
    static RenderAPI s_api;
};
}
