#pragma once

#include "core/renderer/ecs/entity.h"

namespace ObsidianEdge {
class RenderEngine;

class Root final : public Entity {
public:
    // ------------------------------------ Base Begin ------------------------------------

    Root(RenderEngine *renderEngine, const char *name = "Root");
    ~Root() final;

    Root(const Root &other) = delete;
    Root(Root &&other) noexcept = delete;

    auto operator=(const Root &other) -> Root & = delete;
    auto operator=(Root &&other) noexcept -> Root & = delete;

    [[nodiscard]] auto duplicate() const -> std::shared_ptr<Entity> final;

    void onAttach() final;
    void onDetach() final;
    void onUpdate(float delta) final;
    void onEvent(Event &event) final;

    OE_SETUP_ENTITY_TYPE_DEC

    // ------------------------------------- Base End -------------------------------------

    [[nodiscard]] auto isDrawable() const -> bool override;

    [[nodiscard]] auto getRenderEngine() const -> RenderEngine &;

private:
    gsl::not_null<RenderEngine *> m_engine;
};
} // namespace ObsidianEdge
