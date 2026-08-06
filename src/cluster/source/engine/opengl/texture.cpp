#include <pch.h>

#include "engine/opengl/texture.h"

namespace ObsidianEdge {
void OpenGLTexture::init() {
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mapWrapMode(uWrapMode));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mapWrapMode(vWrapMode));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mapMinFilter(minFilter));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mapMagFilter(magFilter));

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, handler.getData().dimensions.x, handler.getData().dimensions.y, 0, GL_RGBA,
                 GL_FLOAT, handler.getData().data.data());

    if (genMipmap)
        glGenerateMipmap(GL_TEXTURE_2D);

    use();
}

void OpenGLTexture::yeet() {
    if (id)
        glDeleteTextures(1, &id);
}

void OpenGLTexture::use() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, id);
}

auto OpenGLTexture::mapMagFilter(MagnificationFilter magFilter) -> int {
    switch (magFilter) {
    case MagnificationFilter::Nearest:
        return GL_NEAREST;
    case MagnificationFilter::Linear:
        return GL_LINEAR;
    }
}

auto OpenGLTexture::mapMinFilter(MinificationFilter minFilter) -> int {
    switch (minFilter) {
    case MinificationFilter::Nearest:
        return GL_NEAREST;
    case MinificationFilter::Linear:
        return GL_LINEAR;
    case MinificationFilter::NearestMipmapNearest:
        return GL_NEAREST_MIPMAP_NEAREST;
    case MinificationFilter::LinearMipmapLinear:
        return GL_LINEAR_MIPMAP_LINEAR;
    case MinificationFilter::NearestMipmapLinear:
        return GL_NEAREST_MIPMAP_LINEAR;
    case MinificationFilter::LinearMipmapNearest:
        return GL_LINEAR_MIPMAP_NEAREST;
    }
}

auto OpenGLTexture::mapWrapMode(WrapMode wrapMode) -> int {
    switch (wrapMode) {
    case WrapMode::Repeat:
        return GL_REPEAT;
    case WrapMode::MirroredRepeat:
        return GL_MIRRORED_REPEAT;
    case WrapMode::ClampToEdge:
        return GL_CLAMP_TO_EDGE;
    case WrapMode::ClampToBorder:
        return GL_CLAMP_TO_BORDER;
    }
}
} // namespace ObsidianEdge
