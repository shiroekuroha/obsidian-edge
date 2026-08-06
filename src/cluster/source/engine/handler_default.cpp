#include <pch.h>

#include "engine/handler_default.h"

namespace ObsidianEdge {
void initKeepers() {
    TextureHandler defaultTexture1({
        {
            {2, 2, 1},
            {"#d40ac6", "#ffffff", "#ffffff", "#d40ac6"},
        },
    });

    TextureHandler defaultTexture2({
        {
            {1, 1, 1},
            {
                "#ffffff",
            },
        },
    });

    MaterialHandler defaultMaterial1({
        {1.0f, 1.0f, 1.0f, 1.0f},
        0.0f,
        0.5f,
        1.0f,
        1.0f,

        TextureID(0),
        1,
        1,
        1,
        1,
        1,

        BlendMode::Additive,
        CullMode::Back,

        true,
        true,

        {1.0f, 1.0f},
        {0.0f, 0.0f},
    });

    MaterialHandler defaultMaterial2({
        {1.0f, 1.0f, 1.0f, 1.0f},
        0.0f,
        0.5f,
        1.0f,
        1.0f,

        1,
        1,
        1,
        1,
        1,
        1,

        BlendMode::Additive,
        CullMode::Back,

        true,
        true,

        {1.0f, 1.0f},
        {0.0f, 0.0f},
    });
}
} // namespace ObsidianEdge
