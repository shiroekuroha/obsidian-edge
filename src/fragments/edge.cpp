#include "core/layer/layers/imgui_layer.h"
#include "core/renderer/ecs/node2d/image.h"
#include "core/renderer/ecs/node2d/rectangle.h"
#include "external.h"

#include "app/application.h"
#include "core/layer/layers/glass_layer.h"
#include "modules/card.h"
#include "modules/game_master.h"

namespace ObsidianEdge {

class Edge : public Application {
public:
    Edge() = default;
    ~Edge() override = default;

    Edge(const Edge &other) = delete;
    Edge(Edge &&other) noexcept = delete;

    auto operator=(const Edge &other) -> Edge & = delete;
    auto operator=(Edge &&other) noexcept -> Edge & = delete;

    void onUpdate(float delta) override {}

    void run() override {
        glassLayerPtr = new GlassLayer;

        pushLayer(glassLayerPtr);
        // pushOverlay(new ImGuiLayer);

        glassLayerPtr->getGlass().getRoot().addChild(std::shared_ptr<Entity>(new GameMaster()));
        Application::run();
    }

private:
    gsl::owner<ObsidianEdge::GlassLayer *> glassLayerPtr{};
};

} // namespace ObsidianEdge

// NOLINTBEGIN(cppcoreguidelines-owning-memory)

auto ObsidianEdge::createApplication() -> Application * { return new Edge(); }

// NOLINTEND(cppcoreguidelines-owning-memory)
