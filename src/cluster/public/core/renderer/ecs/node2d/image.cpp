#include <pch.h>

#include <utility>

#include "image.h"

#include "core/log/log.h"
#include "core/renderer/render_engine.h"

namespace ObsidianEdge {
Image::Image(const char *name) : Node2D(name) { setName("Image"); }

Image::~Image() = default;

Image::Image(const Image &other) { *this = other; };

Image::Image(Image &&other) noexcept { *this = std::move(other); }

auto Image::operator=(const Image &other) -> Image & {
    setName(other.getName().c_str());

    setPosition(other.getPosition());
    setRotation(other.getRotation());
    setScale(other.getScale());

    m_size = other.m_size;
    m_tintColor = other.m_tintColor;
    m_texture = other.m_texture;

    return *this;
}

auto Image::operator=(Image &&other) noexcept -> Image & {
    setName(other.getName().c_str());

    setPosition(other.getPosition());
    setRotation(other.getRotation());
    setScale(other.getScale());

    m_size = other.m_size;
    m_tintColor = other.m_tintColor;
    m_texture = other.m_texture;

    return *this;
}

auto Image::duplicate() const -> std::shared_ptr<Entity> { return Entity::duplicateTyped<Image>(*this); }

void Image::onAttach() {
    if (isPartOfEngine()) {
        getRenderEngine().reload();
    }
}

void Image::onDetach() {
    if (isPartOfEngine()) {
        getRenderEngine().reload();
    }
}

void Image::onUpdate(float delta) {}

void Image::onEvent(Event &event) {}

OE_SETUP_ENTITY_TYPE_DEF(Image, Image)

Image::Image(Vector3 postion, float rotation, Vector3 scale, Vector2 size, Vector4 tintColor, Texture texture)
    : Node2D(postion, rotation, scale), m_size(size), m_tintColor(tintColor), m_texture(std::move(texture)) {}

auto Image::isDrawable() const -> bool { return true; }

auto Image::isPositionInShape(Vector2 position) const -> bool {
    if (!isPartOfEngine()) {
        return false;
    }

    Matrix4 inv = glm::inverse(getWorldMatrix());
    Vector4 p4 = inv * Vector4(position, 0.0f, 1.0f);
    Vector2 p = Vector2(p4.x, getRenderEngine().getViewportSize().y - p4.y);

    Vector2 min = Vector2(getPosition().x, getPosition().y);
    Vector2 max = Vector2(getPosition().x, getPosition().y) + getSize();

    return (p.x >= min.x && p.x <= max.x && p.y >= min.y && p.y <= max.y);
}

auto Image::getRenderingData() const -> QuadData {
    return {{{{{0, 0, 0, 1.0f}, m_tintColor, {0.0f, 0.0f}},
              {{m_size.x, 0, 0, 1.0f}, m_tintColor, {1.0f, 0.0f}},
              {{0, m_size.y, 0, 1.0f}, m_tintColor, {0.0f, 1.0f}},
              {{m_size.x, m_size.y, 0, 1.0f}, m_tintColor, {1.0f, 1.0f}}}},
            {0, 1, 2, 3, 2, 1},
            getTexture(),
            getWorldMatrix()};
}

auto Image::getSize() const -> Vector2 { return m_size; }

auto Image::getTintColor() const -> Vector4 { return m_tintColor; }

auto Image::getTexture() const -> Texture { return m_texture; }

void Image::setSize(Vector2 size) {
    m_size = size;

    if (isPartOfEngine()) {
        getRenderEngine().reload();
    }
}

void Image::setTintColor(Vector4 tintColor) {
    m_tintColor = tintColor;

    if (isPartOfEngine()) {
        getRenderEngine().reload();
    }
}

void Image::setTexture(Texture texture) {
    m_texture = std::move(texture);

    if (isPartOfEngine()) {
        getRenderEngine().reload();
    }
}
} // namespace ObsidianEdge
