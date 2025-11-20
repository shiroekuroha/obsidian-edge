#include "app/application.h"
#include "core/layer/layers/glass_layer.h"

#include "external.h"

class Hammer : public ObsidianEdge::Application {
public:
    Hammer() = default;
    ~Hammer() override = default;

    Hammer(const Hammer &other) = delete;
    Hammer(Hammer &&other) noexcept = delete;

    auto operator=(const Hammer &other) -> Hammer & = delete;
    auto operator=(Hammer &&other) noexcept -> Hammer & = delete;

    void run() override {
        ObsidianEdge::Application::pushLayer(new ObsidianEdge::GlassLayer);
        ObsidianEdge::Application::run();
    }

private:
};

// NOLINTBEGIN(cppcoreguidelines-owning-memory)

auto ObsidianEdge::createApplication() -> ObsidianEdge::Application * { return new Hammer(); }

// NOLINTEND(cppcoreguidelines-owning-memory)
