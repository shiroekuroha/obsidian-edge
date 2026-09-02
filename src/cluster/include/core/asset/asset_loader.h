#pragma once

#include "core.h"

#include "core/asset/assets.h"
#include "stb/stb_image.h"

namespace ObsidianEdge {
static inline auto loadImage(const char* path) -> Texture2D {
    stbi_set_flip_vertically_on_load(1);

    static const float UNSIGNED_CHAR_MAX = 255.0F;

    int width = 0;
    int height = 0;
    int channels = 0;
    unsigned char* data = nullptr;
    unsigned int size = width * height * 4;
    std::vector<Vector4> finalData;

    data = stbi_load(path, &width, &height, &channels, 4);

    if (data != nullptr) {
        OE_CORE_INFO("Image loaded: {0} x {1}, with channels: {2}\n", width, height, channels);
        // Good!
    } else {
        OE_CORE_ERROR("Image failed to load: {0}\n", stbi_failure_reason());
        throw std::runtime_error("Cannot load image");
    }

    for (unsigned int i = 0; i < size; i += 4) {
        finalData.emplace_back(static_cast<float>(data[i]) / UNSIGNED_CHAR_MAX,
                               static_cast<float>(data[i + 1]) / UNSIGNED_CHAR_MAX,
                               static_cast<float>(data[i + 2]) / UNSIGNED_CHAR_MAX,
                               static_cast<float>(data[i + 3]) / UNSIGNED_CHAR_MAX);
    }

    stbi_image_free(data);

    return {{static_cast<unsigned int>(width), static_cast<unsigned int>(height)}, finalData};
}
} // namespace ObsidianEdge