#include <obsidian/core/data/pch.h>

#include "obsidian/core/render/primitives/rectangle.h"

namespace ObsidianEdge
{
Rectangle::Rectangle (Vector2 position, Vector2 size, Vector4 tintColor, Texture texture)
    : m_position (position), m_size (size), m_tintColor (tintColor), m_texture (texture)
{
}

Rectangle::Rectangle ()
    : m_position (0, 0), m_size (1, 1), m_tintColor (1.0f), m_texture ("placeholders/textures/default.png")
{
}

auto
Rectangle::getPosition () const -> Vector2
{
    return m_position;
}

auto
Rectangle::getSize () const -> Vector2
{
    return m_size;
}

auto
Rectangle::getVertices () const -> Vector<Vertex>
{
    return {
        { { m_position.x, m_position.y, 0.0f, 1.0f },
          { m_tintColor.r, m_tintColor.g, m_tintColor.b, m_tintColor.a },
          { 0.0f, 0.0f } },
        { { m_position.x + m_size.x, m_position.y, 0.0f, 1.0f },
          { m_tintColor.r, m_tintColor.g, m_tintColor.b, m_tintColor.a },
          { 1.0f, 0.0f } },
        { { m_position.x, m_position.y + m_size.y, 0.0f, 1.0f },
          { m_tintColor.r, m_tintColor.g, m_tintColor.b, m_tintColor.a },
          { 0.0f, 1.0f } },
        { { m_position.x + m_size.x, m_position.y + m_size.y, 0.0f, 1.0f },
          { m_tintColor.r, m_tintColor.g, m_tintColor.b, m_tintColor.a },
          { 1.0f, 1.0f } },
    };
}

auto
Rectangle::getIndicies (unsigned int offset) const -> Vector<Index>
{
    return { 0, 1, 2, 3, 2, 1 };
}

auto
Rectangle::getTexture () const -> Texture
{
    return m_texture;
}
}
