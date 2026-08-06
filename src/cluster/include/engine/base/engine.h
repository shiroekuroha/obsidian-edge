#pragma once

#include "core.h"

#include "core/ecs/scene.h"

namespace ObsidianEdge {
class OE_API RenderEngine {
public:
    RenderEngine() = default;
    virtual ~RenderEngine() = default;

    RenderEngine(const RenderEngine &other) = default;
    RenderEngine(RenderEngine &&other) noexcept = default;

    auto operator=(const RenderEngine &other) -> RenderEngine & = default;
    auto operator=(RenderEngine &&other) noexcept -> RenderEngine & = default;

    virtual void uploadRenderData(const std::vector<RenderObjData> &renderObjData) = 0;

    virtual void init() = 0;
    virtual void yeet() = 0;

    virtual void update(double delta) = 0;

private:
};
} // namespace ObsidianEdge
