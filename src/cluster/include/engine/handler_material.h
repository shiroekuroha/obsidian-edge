#pragma once

#include "core.h"

#include "engine/handler_texture.h"

namespace ObsidianEdge {
enum class BlendMode : uint8_t { Opaque = 0, AlphaBlend, Additive, Multiplicative, Screen, PremultipliedAlpha };
enum class CullMode : uint8_t { None = 0, Back, Front, Both };

using MaterialID = uint32_t;
using MaterialData = struct MaterialData {
    Vector4 tint = {1.0f, 1.0f, 1.0f, 1.0f};
    float metallic = 0.0f;
    float roughness = 0.5f;
    float ao = 1.0f;
    float opacity = 1.0f;

    TextureHandler albedo = 1;
    TextureHandler normal = 1;
    TextureHandler metallicMap = 1;
    TextureHandler roughnessMap = 1;
    TextureHandler aoMap = 1;
    TextureHandler emissiveMap = 1;

    BlendMode blendMode = BlendMode::Opaque;
    CullMode cullMode = CullMode::Back;

    bool depthWrite = true;
    bool depthTest = true;

    Vector2 uvScale = {1.0f, 1.0f};
    Vector2 uvOffset = {0.0f, 0.0f};
};

inline auto materialLoader(const char *path) -> MaterialData { throw std::runtime_error("Unimplemented feature."); }

using MaterialHandler = Handler<MaterialID, MaterialData, materialLoader>;

} // namespace ObsidianEdge
