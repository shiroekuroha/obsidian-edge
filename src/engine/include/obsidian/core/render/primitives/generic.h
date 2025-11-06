#ifndef OE_RENDER_GENERIC_H
#define OE_RENDER_GENERIC_H

#include "obsidian/core/render/primitives/texture.h"

namespace ObsidianEdge
{
using Vertex = struct Vertex
{
    Vector4 position;
    Vector4 tintColor;
    Vector2 texCoord;
};

using Index = unsigned char;

using Object2D = struct Object2D
{
    Vector<Vertex> vertices;
    Vector<Index> indicies;
    Vector<Texture> textures;

    Matrix4 transform = Matrix4 (1.0f);
};

using Object3D = struct Object3D
{
    Vector<Vertex> vertices;
    Vector<Index> indicies;
    Vector<Texture> textures;

    Matrix4 transform = Matrix4 (1.0f);
};
}

#endif
