#include "engine/obsidian_edge.h"

#include "engine/core/imgui/imgui_layer.h"

class Hammer : public ObsidianEdge::Application
{
public:
    Hammer () { OE_INFO ("Application Starting...") }

    ~Hammer () { OE_INFO ("Application Ending...") }

    void
    run () override
    {
        OE_INFO ("Application Running...")
        pushLayer (new ObsidianEdge::ImGuiLayer);
        Application::run ();
    }

private:
};

ObsidianEdge::Application *
ObsidianEdge::createApplication ()
{
    return new Hammer ();
}
