#include <pch.h>

#include "renderer.h"

namespace ObsidianEdge {
RenderObject::RenderObject() = default;
RenderObject::~RenderObject() = default;

RenderObject::RenderObject(const RenderObject &other) { *this = other; };
RenderObject::RenderObject(RenderObject &&other) noexcept { *this = std::move(other); }

auto RenderObject::operator=(const RenderObject &other) -> RenderObject & = default;
auto RenderObject::operator=(RenderObject &&other) noexcept -> RenderObject & = default;

Renderer::Renderer() = default;
Renderer::~Renderer() = default;

Renderer::Renderer(const Renderer &other) { *this = other; };
Renderer::Renderer(Renderer &&other) noexcept { *this = std::move(other); }

auto Renderer::operator=(const Renderer &other) -> Renderer & = default;
auto Renderer::operator=(Renderer &&other) noexcept -> Renderer & = default;
} // namespace ObsidianEdge
