#pragma once

#include "stb/stb_image.h"

namespace ObsidianEdge {
class Texture {
public:
    Texture(const char *path);

    Texture();
    virtual ~Texture() = default;

    Texture(const Texture &other) = default;
    Texture(Texture &&other) noexcept = default;

    auto operator=(const Texture &other) -> Texture & = default;
    auto operator=(Texture &&other) noexcept -> Texture & = default;

    void bind(unsigned int slot = 0);
    void unbind();

public:
    static auto loadDefaultTexture() -> unsigned int;
    static auto instancingTexture(const char *path, unsigned int id) -> unsigned int;

    static auto createTexture(const char *path) -> unsigned int;
    static void destroyTexture(const char *path);

    static void clear();

private:
    unsigned int m_id = 0;
    std::string m_path = {};

private:
    static bool defaultInit;
    static std::vector<std::pair<std::string, unsigned int>> buffer;
};
} // namespace ObsidianEdge
