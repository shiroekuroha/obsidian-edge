#include <pch.h>

#include "texture.h"

// ! This order matters!
// clang-format off
#include "glad/gl.h"
#include "GLFW/glfw3.h"
// clang-format on

#include "core/log/log.h"

namespace ObsidianEdge {
bool Texture::defaultInit = false;
std::vector<std::pair<std::string, unsigned int>> Texture::buffer = {};

Texture::Texture() : m_id(loadDefaultTexture()) {}

Texture::Texture(const char *path) : m_id(createTexture(path)) {}

void Texture::bind(unsigned int slot) {
    if (!defaultInit) {
        loadDefaultTexture();
    }

    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::unbind() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

auto Texture::loadDefaultTexture() -> unsigned int {
    static const unsigned int defaultColor = 255;

    unsigned int id = 0;
    std::array<unsigned char, 4> whitePixel = {defaultColor, defaultColor, defaultColor, defaultColor}; // RGBA

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, whitePixel.data());

    // Set filtering and wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindTexture(GL_TEXTURE_2D, 0);

    instancingTexture("", id);

    return id;
}

auto Texture::createTexture(const char *path) -> unsigned int {
    for (std::pair<std::string, unsigned int> &pair : buffer)
        if (pair.first == path && pair.second != 0)
            return pair.second;

    stbi_set_flip_vertically_on_load(true);

    unsigned int id = 0;
    int bpp = 0;
    unsigned char *localBuffer = nullptr;
    Vector2i size = {0, 0};

    localBuffer = stbi_load(path, &size.x, &size.y, &bpp, 4);

    OE_CORE_ASSERT(localBuffer, std::string(stbi_failure_reason()) + ", path: {0}", path);

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, 0);

    if (localBuffer)
        stbi_image_free(localBuffer);

    return instancingTexture(path, id);
}

void Texture::destroyTexture(const char *path) {
    for (std::pair<std::string, unsigned int> &pair : buffer)
        if (pair.first == path)
            glDeleteTextures(1, &pair.second);
}

auto Texture::instancingTexture(const char *path, unsigned int id) -> unsigned int {
    for (std::pair<std::string, unsigned int> &pair : buffer)
        if (pair.first == path && pair.second == 0) {
            // Reinit existed texture.
            pair.second = id;
            return id;
        }

    // Instancing texture.
    buffer.emplace_back(path, id);
    return id;
}

void Texture::clear() {
    for (std::pair<std::string, unsigned int> &pair : buffer)
        if (pair.second != 0)
            glDeleteTextures(1, &pair.second);

    buffer.clear();
}

} // namespace ObsidianEdge
