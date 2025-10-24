#include "obsidian/core/render/glass.h"
#include "obsidian/external.h"

#include "obsidian/core/layer/layers/imgui_layer.h"

class Hammer : public ObsidianEdge::Application
{
public:
    Hammer () = default;
    ~Hammer () override = default;

    Hammer (const Hammer &other) = delete;
    Hammer (Hammer &&other) noexcept = delete;

    auto operator= (const Hammer &other) -> Hammer & = delete;
    auto operator= (Hammer &&other) noexcept -> Hammer & = delete;

    void
    run () override
    {
        ObsidianEdge::Application::pushLayer (new ObsidianEdge::Glass);
        ObsidianEdge::Application::run ();
    }

private:
};

// NOLINTBEGIN(cppcoreguidelines-owning-memory)

auto
ObsidianEdge::createApplication () -> ObsidianEdge::Application *
{
    return new Hammer ();
}

// NOLINTEND(cppcoreguidelines-owning-memory)
