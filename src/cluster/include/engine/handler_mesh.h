#pragma once

#include "core.h"

#include "engine/handler.h"

namespace ObsidianEdge {
using Index = uint32_t;
using Vertex = struct Vertex {
    Vector4 position;
    Vector2 texCoord;
};

using MeshID = uint32_t;
using MeshData = struct MeshData {
    std::vector<Vertex> vertices;
    std::vector<Index> indices;
};

inline auto meshLoader(const char *path) -> MeshData { throw std::runtime_error("Unimplemented feature."); }

using MeshHandler = Handler<MeshID, MeshData, meshLoader>;
} // namespace ObsidianEdge
