#pragma once

#include "core.h"
#include "engine/handler_texture.h"

namespace ObsidianEdge {
enum class MagnificationFilter : uint8_t {
    Nearest = 0,
    Linear,
};
enum class MinificationFilter : uint8_t {
    Nearest = 0,
    Linear,
    NearestMipmapNearest,
    LinearMipmapLinear,
    NearestMipmapLinear,
    LinearMipmapNearest,
};
enum class WrapMode : uint8_t { Repeat, MirroredRepeat, ClampToEdge, ClampToBorder };

class OE_API Texture {
public:
    Texture() = default;
    virtual ~Texture() = default;

    Texture(const Texture &other) = default;
    Texture(Texture &&other) noexcept = default;

    auto operator=(const Texture &other) -> Texture & = default;
    auto operator=(Texture &&other) noexcept -> Texture & = default;

    [[nodiscard]] inline auto getTextureData() const -> const TextureData & { return handler.getData(); }
    inline void setTextureHandler(TextureHandler _handler) { handler = _handler; }

    virtual void init() = 0;
    virtual void yeet() = 0;
    virtual void use() = 0;

    MagnificationFilter magFilter{};
    MinificationFilter minFilter{};
    WrapMode uWrapMode = WrapMode::ClampToEdge;
    WrapMode vWrapMode = WrapMode::ClampToEdge;
    bool genMipmap = true;

protected:
    TextureHandler handler;
};
} // namespace ObsidianEdge
