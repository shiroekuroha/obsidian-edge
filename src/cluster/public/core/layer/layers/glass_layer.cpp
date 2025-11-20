#include <pch.h>

#include "glass_layer.h"

namespace ObsidianEdge {
GlassLayer::GlassLayer() = default;

GlassLayer::~GlassLayer() = default;

GlassLayer::GlassLayer(const GlassLayer &other) { *this = other; }

GlassLayer::GlassLayer(GlassLayer &&other) noexcept { *this = std::move(other); }

auto GlassLayer::operator=(const GlassLayer &other) -> GlassLayer & { return *this; }

auto GlassLayer::operator=(GlassLayer &&other) noexcept -> GlassLayer & { return *this; }

void GlassLayer::onAttach() {}

void GlassLayer::onDetach() {}

void GlassLayer::onUpdate(float delta) { renderer.onUpdate(delta); }

void GlassLayer::onEvent(Event &event) { renderer.onEvent(event); }
} // namespace ObsidianEdge
