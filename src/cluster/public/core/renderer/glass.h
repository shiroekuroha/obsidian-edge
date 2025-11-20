#pragma once

#include "core/renderer/ecs/entity.h"
#include "core/renderer/modules/shader.h"

namespace ObsidianEdge {
class Glass {
public:
    Glass();
    ~Glass();

    Glass(const Glass &other);
    Glass(Glass &&other) noexcept;

    auto operator=(const Glass &other) -> Glass &;
    auto operator=(Glass &&other) noexcept -> Glass &;

    void onUpdate(float delta);
    void onEvent(Event &event);

    void traverseTree(const std::function<void(Entity &)> &func);

    void makeRoot(Entity *entity);
    auto getRoot() -> Entity &;

private:
    Shader shader;
    std::shared_ptr<Entity> root = nullptr;

    Matrix4 view = Matrix4(1.0f);
    Matrix4 proj = Matrix4(1.0f);
};
} // namespace ObsidianEdge
