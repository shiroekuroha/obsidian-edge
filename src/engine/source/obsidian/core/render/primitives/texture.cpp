#include <obsidian/core/data/pch.h>

#include "obsidian/core/render/primitives/texture.h"

namespace ObsidianEdge
{
Vector<Pair<String, unsigned int>> Texture::buffer = {};

Texture::Texture (const char *path) : m_id (createTexture (path)) {}

void
Texture::bind (unsigned int slot)
{
    glActiveTexture (GL_TEXTURE0 + slot);
    glBindTexture (GL_TEXTURE_2D, m_id);
}

void
Texture::unbind ()
{
    glActiveTexture (GL_TEXTURE0);
    glBindTexture (GL_TEXTURE_2D, 0);
}

auto
Texture::createTexture (const char *path) -> unsigned int
{
    for (Pair<String, unsigned int> &pair : buffer)
        if (pair.first == path && pair.second != 0)
            return pair.second;

    stbi_set_flip_vertically_on_load (true);

    unsigned int id = 0;
    int bpp = 0;
    unsigned char *localBuffer = nullptr;
    Vector2i size = { 0, 0 };

    localBuffer = stbi_load (path, &size.x, &size.y, &bpp, 4);

    OE_CORE_ASSERT (localBuffer, stbi_failure_reason ());

    glGenTextures (1, &id);
    glBindTexture (GL_TEXTURE_2D, id);
    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA8, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);

    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture (GL_TEXTURE_2D, 0);

    if (localBuffer)
        stbi_image_free (localBuffer);

    for (Pair<String, unsigned int> &pair : buffer)
        if (pair.first == path && pair.second == 0)
            {
                // Reinit existed texture.
                pair.second = id;

                return id;
            }

    // Instancing texture.
    buffer.emplace_back (Pair (path, id));

    return id;
}

void
Texture::destroyTexture (const char *path)
{
    for (Pair<String, unsigned int> &pair : buffer)
        if (pair.first == path)
            glDeleteTextures (1, &pair.second);
}

void
Texture::clear ()
{
    for (Pair<String, unsigned int> &pair : buffer)
        if (pair.second != 0)
            glDeleteTextures (1, &pair.second);

    buffer.clear ();
}
}
