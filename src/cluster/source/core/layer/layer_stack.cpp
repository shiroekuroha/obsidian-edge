
#include "core/layer/layer_stack.h"
#include <pch.h>

namespace ObsidianEdge {
LayerStack::~LayerStack() { clear(); }

void LayerStack::pushLayer(Layer *layer) {
    m_layers.emplace(m_layers.begin() + m_stackBreakIndex, layer);
    m_stackBreakIndex++;
}

void LayerStack::popLayer(Layer *layer) {
    auto it = std::find(m_layers.begin(), m_layers.end(), layer);

    if (it != m_layers.end()) {
        m_layers.erase(it);
        m_stackBreakIndex--;
    }
}

void LayerStack::pushOverlay(Layer *overlay) { m_layers.emplace_back(overlay); }

void LayerStack::popOverlay(Layer *overlay) {
    auto it = std::find(m_layers.begin(), m_layers.end(), overlay);

    if (it != m_layers.end()) {
        m_layers.erase(it);
    }
}

void LayerStack::clear() {
    for (Layer *layer : m_layers)
        delete layer;

    m_layers.clear();
}

auto LayerStack::begin() -> std::vector<Layer *>::iterator { return m_layers.begin(); }

auto LayerStack::end() -> std::vector<Layer *>::iterator { return m_layers.end(); }
} // namespace ObsidianEdge
