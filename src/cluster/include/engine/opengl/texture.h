#include "core.h"

#include "engine/base/texture.h"

// ! This order matters!
// clang-format off
#include <glad/gl.h>
#include <GLFW/glfw3.h>
// clang-format on

namespace ObsidianEdge {
class OpenGLTexture : public Texture {
public:
    OpenGLTexture() = default;
    virtual ~OpenGLTexture() = default;

    OpenGLTexture(const OpenGLTexture &other) = default;
    OpenGLTexture(OpenGLTexture &&other) noexcept = default;

    auto operator=(const OpenGLTexture &other) -> OpenGLTexture & = default;
    auto operator=(OpenGLTexture &&other) noexcept -> OpenGLTexture & = default;

    void init() override;
    void yeet() override;
    void use() override;

    MagnificationFilter magFilter{};
    MinificationFilter minFilter{};
    WrapMode uWrapMode = WrapMode::ClampToEdge;
    WrapMode vWrapMode = WrapMode::ClampToEdge;
    bool genMipmap = true;

protected:
    static auto mapMagFilter(MagnificationFilter magFilter) -> int;
    static auto mapMinFilter(MinificationFilter minFilter) -> int;
    static auto mapWrapMode(WrapMode wrapMode) -> int;

private:
    unsigned int id = 0;
};
} // namespace ObsidianEdge
