#pragma once

#include "core.h"

#include "engine/handler.h"
#include "stb/stb_image.h"

namespace ObsidianEdge {
using TextureID = uint32_t;
using TextureData = struct TextureData {
    Point3 dimensions = {1, 1, 1};
    std::vector<Vector4> data;
};

inline auto textureLoader(const char *path) -> TextureData {
    stbi_set_flip_vertically_on_load(true);

    static const float unsignedCharMax = 255.0f;
    int width = 0, height = 0, channels = 0;
    unsigned char *data = nullptr;
    unsigned int size = width * height * 4;
    std::vector<Vector4> finalData;

    data = stbi_load(path, &width, &height, &channels, 4);

    if (data) {
        OE_CORE_INFO("Image loaded: {0} x {1}, with channels: {2}\n", width, height, channels);
        // Good!
    } else {
        OE_CORE_ERROR("Image failed to load: {0}\n", stbi_failure_reason());
        throw std::runtime_error("Cannot load image");
    }

    for (unsigned int i = 0; i < size; i += 4) {
        finalData.emplace_back(static_cast<float>(data[i]) / unsignedCharMax, static_cast<float>(data[i + 1]) / unsignedCharMax,
                               static_cast<float>(data[i + 2]) / unsignedCharMax,
                               static_cast<float>(data[i + 3]) / unsignedCharMax);
    }

    stbi_image_free(data);

    return {Point3(width, height, 1), finalData};
}

using TextureHandler = Handler<TextureID, TextureData, textureLoader>;
} // namespace ObsidianEdge
