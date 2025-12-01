#pragma once

#include "core/renderer/modules/texture.h"

namespace ObsidianEdge {
static constexpr unsigned int s_trigNumV = 3;
static constexpr unsigned int s_trigNumI = 3;
static constexpr unsigned int s_rectNumV = 4;
static constexpr unsigned int s_rectNumI = 6;

using Vertex = struct Vertex {
    Vector4 position;
    Vector4 tintColor;
    Vector2 texCoord;
};

using Index = unsigned char;

using QuadData = struct QuadData {
    std::array<Vertex, s_rectNumV> vertices;
    std::array<Index, s_rectNumI> indices;
    Texture texture;
    Matrix4 transform;
};
} // namespace ObsidianEdge
