#pragma once

#include "core/layer/layer.h"
#include "core/renderer/glass.h"

namespace ObsidianEdge {
class GlassLayer : public Layer {
public:
    GlassLayer();
    ~GlassLayer() override;

    GlassLayer(const GlassLayer &other);
    GlassLayer(GlassLayer &&other) noexcept;

    auto operator=(const GlassLayer &other) -> GlassLayer &;
    auto operator=(GlassLayer &&other) noexcept -> GlassLayer &;

    void onAttach() override;
    void onDetach() override;
    void onUpdate(float delta) override;
    void onEvent(Event &event) override;

    [[nodiscard]] auto getGlass() -> Glass &;

private:
    Glass renderer;
};
} // namespace ObsidianEdge
