#ifndef OE_RECTANGLE_H
#define OE_RECTANGLE_H

#include "obsidian/core/core.h"

// ! This order matters!
// clang-format off
#include <glad/gl.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "obsidian/core/render/primitives/generic.h"
#include "obsidian/core/render/primitives/texture.h"

namespace ObsidianEdge
{
/**
 * @brief Generate vertex data and texture, if an texture not given it will render color instead.
 */
class Rectangle
{
public:
    Rectangle (Vector2 position, Vector2 size, Vector4 tintColor = Vector4 (1.0f),
               Texture texture = Texture ("textures/default.png"));

    Rectangle ();
    virtual ~Rectangle () = default;

    Rectangle (const Rectangle &other) = default;
    Rectangle (Rectangle &&other) noexcept = delete;

    auto operator= (const Rectangle &other) -> Rectangle & = default;
    auto operator= (Rectangle &&other) noexcept -> Rectangle & = delete;

    void bind (unsigned int program, int slot = 0);
    void unbind (unsigned int program);

    [[nodiscard]] auto getPosition () const -> Vector2;
    [[nodiscard]] auto getSize () const -> Vector2;

    [[nodiscard]] auto getVertices () const -> Vector<Vertex>;
    [[nodiscard]] auto getIndicies (unsigned int offset = 0) const -> Vector<Index>;

    [[nodiscard]] auto getTexture () const -> Texture;

private:
    Vector2 m_position = { 0, 0 };
    Vector2 m_size = { 1, 1 };
    Vector4 m_tintColor;
    Texture m_texture;
};
}

#endif
