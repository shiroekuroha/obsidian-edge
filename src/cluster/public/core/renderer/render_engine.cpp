#include <pch.h>

#include "render_engine.h"

#include "app/application.h"

namespace ObsidianEdge {
RenderEngine::RenderEngine() : root(this) {}

RenderEngine::~RenderEngine() = default;

auto RenderEngine::getViewportSize() const -> Vector2 {
    return {Application::get().getWindow().getWidth(), Application::get().getWindow().getHeight()};
}

auto RenderEngine::getRoot() -> Root & { return root; }

void RenderEngine::onUpdate(float delta) {}

void RenderEngine::onEvent(Event &event) {}

void RenderEngine::traversePreOrder(Entity &entity, const std::function<void(Entity &entity)> &func) {
    func(entity);

    entity.forEachChild([this, func](Entity &entity) -> void { traversePreOrder(entity, func); });
}

void RenderEngine::traversePostOrder(Entity &entity, const std::function<void(Entity &entity)> &func) {
    entity.forEachChild([this, func](Entity &entity) -> void { traversePostOrder(entity, func); });

    func(entity);
}
} // namespace ObsidianEdge
