#pragma once

#include "core.h"

namespace ObsidianEdge {
class OE_API Shader {
public:
    Shader() = default;
    virtual ~Shader() = default;

    Shader(const Shader &other) = default;
    Shader(Shader &&other) noexcept = default;

    auto operator=(const Shader &other) -> Shader & = default;
    auto operator=(Shader &&other) noexcept -> Shader & = default;

    virtual void init() = 0;
    virtual void yeet() = 0;

    virtual void use() = 0;

private:
};
} // namespace ObsidianEdge
