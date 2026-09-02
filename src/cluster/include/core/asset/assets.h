#pragma once

#include "core.h"

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

enum class BlendMode : uint8_t { Opaque = 0, AlphaBlend, Additive, Multiplicative, Screen, PremultipliedAlpha };
enum class CullMode : uint8_t { NoCulling, Back, Front, Both };

#ifdef OE_ARCHITECTURE_X64
using Index = uint64_t;
#else
using Index = uint32_t;
#endif
using Vertex = struct Vertex {
    Vector3 position;
    Vector3 normal;
    Vector2 texCoord;
    Vector4 tangent;
};

#ifdef OE_ARCHITECTURE_X64
using AssetId = uint64_t;
#else
using AssetId = uint32_t;
#endif

using Asset = struct Asset {};

using TextureData = struct TextureData : public Asset {
    TextureData(const std::vector<Vector4>& data)
        : data(data) {}

    std::vector<Vector4> data;
};
using Texture1D = struct Texture1D : public TextureData {
    Texture1D(unsigned int length, const std::vector<Vector4>& data)
        : length(length)
        , TextureData(data) {}

    unsigned int length{};
};
using Texture2D = struct Texture2D : public TextureData {
    Texture2D(Point2 dimensions, const std::vector<Vector4>& data)
        : dimensions(dimensions)
        , TextureData(data) {}

    Point2 dimensions{1};
};
using Texture3D = struct Texture3D : public TextureData {
    Texture3D(Point3 dimensions, const std::vector<Vector4>& data)
        : dimensions(dimensions)
        , TextureData(data) {}

    Point3 dimensions{1};
};
using SamplerData = struct SamplerData : public Asset {
    MagnificationFilter magFilter{};
    MinificationFilter minFilter{};
    WrapMode uWrapMode = WrapMode::ClampToEdge;
    WrapMode vWrapMode = WrapMode::ClampToEdge;
    bool genMipmap = true;
};

using TextureId = AssetId;
using SamplerId = AssetId;

using Texture = struct Texture {
    TextureId texture;
    SamplerId sampler;
};

using Material = struct Material : public Asset {
    Vector4 tint{1.0F};

    float metallic = 0.0f;
    float roughness = 0.5f;
    float ao = 1.0f;
    float opacity = 1.0f;

    Texture albedo;
    Texture normal;
    Texture metallicMap;
    Texture roughnessMap;
    Texture aoMap;
    Texture emissiveMap;

    BlendMode blendMode = BlendMode::Opaque;
    CullMode cullMode = CullMode::Back;

    bool depthWrite = true;
    bool depthTest = true;

    Vector2 uvScale{1.0f, 1.0f};
    Vector2 uvOffset{0.0f, 0.0f};
};
using Mesh = struct Mesh : public Asset {
    std::vector<Vertex> vertices;
    std::vector<Index> indices;
};

class AssetContainer {
public:
    template <typename T>
    AssetContainer(T& asset)
        : m_asset(std::make_unique<T>(asset)) {
        static_assert(std::is_base_of_v<Asset, T>, "Only accept Asset derived.");
    }

    void write(const std::function<void(Asset&)>& writeFunction) {
        std::unique_lock lock(m_mutex);

        writeFunction(*m_asset);
    }

    void read(const std::function<void(const Asset&)>& readFunction) const {
        std::shared_lock lock(m_mutex);

        readFunction(*m_asset);
    }

private:
    std::unique_ptr<Asset> m_asset;
    mutable std::shared_mutex m_mutex;
};
} // namespace ObsidianEdge