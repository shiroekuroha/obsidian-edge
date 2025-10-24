#ifndef OE_TEXTURE_H
#define OE_TEXTURE_H

#include "obsidian/core/core.h"

// ! This order matters!
// clang-format off
#include <glad/gl.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "obsidian/core/log/log.h"
#include "stb/stb_image.h"

namespace ObsidianEdge
{
class Texture
{
public:
    Texture (const char *path);

    Texture () = delete;
    virtual ~Texture () = default;

    Texture (const Texture &other) = default;
    Texture (Texture &&other) noexcept = default;

    auto operator= (const Texture &other) -> Texture & = default;
    auto operator= (Texture &&other) noexcept -> Texture & = default;

    void bind (unsigned int slot = 0);
    void unbind ();

public:
    static auto createTexture (const char *path) -> unsigned int;
    static void destroyTexture (const char *path);

    static void clear ();

private:
    unsigned int m_id = 0;
    String m_path = {};

private:
    static Vector<Pair<String, unsigned int>> buffer;
};
}

#endif
