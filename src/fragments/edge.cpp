#include "external.h"

#include "application/application.h"

namespace ObsidianEdge {

class Edge : public Application {
public:
    Edge() = default;
    ~Edge() override = default;

    Edge(const Edge &other) = delete;
    Edge(Edge &&other) noexcept = delete;

    auto operator=(const Edge &other) -> Edge & = delete;
    auto operator=(Edge &&other) noexcept -> Edge & = delete;

    void run() override {
        try {
            Application::run();
        } catch (std::exception e) {
            OE_ERROR("Obsidian Cluster application run error \"{0}\"", e.what())
        }
    }

private:
};

} // namespace ObsidianEdge

// NOLINTBEGIN(cppcoreguidelines-owning-memory)

auto ObsidianEdge::createApplication() -> Application * { return new Edge(); }

// NOLINTEND(cppcoreguidelines-owning-memory)
