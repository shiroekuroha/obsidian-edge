#pragma once

#include "core/event/event.h"
#include "core/renderer/ecs/root.h"

namespace ObsidianEdge {
enum class RenderMode : std::int8_t { None = 0, Triangle, Rectangle };

class RenderEngine {
public:
    RenderEngine();
    virtual ~RenderEngine();

    RenderEngine(const RenderEngine &other) = delete;
    RenderEngine(RenderEngine &&other) noexcept = delete;

    auto operator=(const RenderEngine &other) -> RenderEngine & = delete;
    auto operator=(RenderEngine &&other) noexcept -> RenderEngine & = delete;

    virtual void onUpdate(float delta) = 0;
    virtual void onEvent(Event &event) = 0;

    [[nodiscard]] auto getViewportSize() const -> Vector2;
    [[nodiscard]] auto getRoot() -> Root &;

    virtual void reload() = 0;
    [[nodiscard]] virtual auto isHovered(Entity &entity, std::vector<Entity *> ignore = {}) -> bool = 0;

    void traversePreOrder(Entity &entity, const std::function<void(Entity &entity)> &func);
    void traversePostOrder(Entity &entity, const std::function<void(Entity &entity)> &func);

private:
    Root root;
};
} // namespace ObsidianEdge
