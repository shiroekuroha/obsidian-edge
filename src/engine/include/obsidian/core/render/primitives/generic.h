#ifndef OE_RENDER_GENERIC_H
#define OE_RENDER_GENERIC_H

namespace ObsidianEdge
{
using Vertex = struct Vertex
{
    Vector4 position;
    Vector4 tintColor;
    Vector2 texCoord;
};

using Index = unsigned char;
}

#endif
