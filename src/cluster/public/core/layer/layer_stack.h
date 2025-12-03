#pragma once

#include "core.h"
#include "core/layer/layer.h"

namespace ObsidianEdge {
class LayerStack {
public:
    LayerStack() = default;
    virtual ~LayerStack();

    LayerStack(const LayerStack &other) = default;
    LayerStack(LayerStack &&other) noexcept = default;

    auto operator=(const LayerStack &other) -> LayerStack & = default;
    auto operator=(LayerStack &&other) noexcept -> LayerStack & = default;

    void pushLayer(Layer *layer);
    void popLayer(Layer *layer);

    void pushOverlay(Layer *overlay);
    void popOverlay(Layer *overlay);

    void clear();

    auto begin() -> std::vector<Layer *>::iterator;
    auto end() -> std::vector<Layer *>::iterator;

    inline operator std::vector<Layer *> &() { return m_layers; }

private:
    std::vector<Layer *> m_layers;
    unsigned int m_stackBreakIndex = 0;
};
} // namespace ObsidianEdge
