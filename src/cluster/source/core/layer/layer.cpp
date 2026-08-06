#include <pch.h>

#include "core/layer/layer.h"

namespace ObsidianEdge {
Layer::Layer(const char* name)
    : m_name(name) {}

void Layer::onAttach() {}

void Layer::onDetach() {}

void Layer::onUpdate(double delta) {}

void Layer::onEvent(Event& event) {}
} // namespace ObsidianEdge
