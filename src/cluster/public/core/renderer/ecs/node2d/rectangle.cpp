#include <pch.h>

#include "rectangle.h"

#include "core/log/log.h"
#include "core/renderer/render_engine.h"

namespace ObsidianEdge {
Rectangle::Rectangle(const char *name) : Node2D(name) { setName("Rectangle"); }

Rectangle::~Rectangle() = default;

Rectangle::Rectangle(const Rectangle &other) { *this = other; };

Rectangle::Rectangle(Rectangle &&other) noexcept { *this = std::move(other); }

auto Rectangle::operator=(const Rectangle &other) -> Rectangle & {
    setName(other.getName().c_str());

    setPosition(other.getPosition());
    setRotation(other.getRotation());
    setScale(other.getScale());

    m_size = other.m_size;
    m_color = other.m_color;

    return *this;
}

auto Rectangle::operator=(Rectangle &&other) noexcept -> Rectangle & {
    setName(other.getName().c_str());

    setPosition(other.getPosition());
    setRotation(other.getRotation());
    setScale(other.getScale());

    m_size = other.m_size;
    m_color = other.m_color;

    return *this;
}

auto Rectangle::duplicate() const -> std::shared_ptr<Entity> { return Entity::duplicateTyped<Rectangle>(*this); }

void Rectangle::onAttach() {
    if (isPartOfEngine()) {
        getRenderEngine().reload();
    }
}

void Rectangle::onDetach() {
    if (isPartOfEngine()) {
        getRenderEngine().reload();
    }
}

void Rectangle::onUpdate(float delta) {}

void Rectangle::onEvent(Event &event) {}

OE_SETUP_ENTITY_TYPE_DEF(Rectangle, Rectangle)

Rectangle::Rectangle(Vector3 postion, float rotation, Vector3 scale, Vector2 size, Vector4 color)
    : Node2D(postion, rotation, scale), m_size(size), m_color(color) {}

auto Rectangle::isDrawable() const -> bool { return true; }

auto Rectangle::isPositionInShape(Vector2 position) const -> bool {
    if (!isPartOfEngine()) {
        return false;
    }

    // Convert position to vec4 (homogeneous coordinates for mat4)
    Vector4 worldPos(position, 0.0f, 1.0f); // z = 0 for 2D

    // Compute inverse of the 4x4 transform matrix
    Matrix4 invTransform = glm::inverse(getWorldMatrix());

    // Transform world position into rectangle's local space
    Vector4 localPos4 = invTransform * worldPos;
    Vector2 localPos(localPos4.x, localPos4.y);

    // Check if the local position is within rectangle bounds
    return (localPos.x >= 0.0f && localPos.x <= getSize().x && localPos.y >= 0.0f && localPos.y <= getSize().y);
}

auto Rectangle::getRenderingData() const -> QuadData {
    return {{{{{0, 0, 0, 1.0f}, m_color, {0.0f, 0.0f}},
              {{m_size.x, 0, 0, 1.0f}, m_color, {1.0f, 0.0f}},
              {{0, m_size.y, 0, 1.0f}, m_color, {0.0f, 1.0f}},
              {{m_size.x, m_size.y, 0, 1.0f}, m_color, {1.0f, 1.0f}}}},
            {0, 1, 2, 3, 2, 1},
            Texture(),
            getWorldMatrix()};
}

auto Rectangle::getSize() const -> Vector2 { return m_size; }

auto Rectangle::getColor() const -> Vector4 { return m_color; }

void Rectangle::setSize(Vector2 size) {
    m_size = size;

    if (isPartOfEngine()) {
        getRenderEngine().reload();
    }
}

void Rectangle::setColor(Vector4 color) {
    m_color = color;

    if (isPartOfEngine()) {
        getRenderEngine().reload();
    }
}
} // namespace ObsidianEdge
