#include <pch.h>

#include "node2d.h"

#include "core/log/log.h"
#include "core/renderer/render_engine.h"
#include "glm/ext/matrix_transform.hpp"

namespace ObsidianEdge {
Node2D::Node2D(const char *name) : Entity(name) {}

Node2D::~Node2D() = default;

Node2D::Node2D(const Node2D &other) { *this = other; }

Node2D::Node2D(Node2D &&other) noexcept { *this = std::move(other); }

auto Node2D::operator=(const Node2D &other) -> Node2D & {
    m_position = other.m_position;
    m_rotation = other.m_rotation;
    m_scale = other.m_scale;

    return *this;
}

auto Node2D::operator=(Node2D &&other) noexcept -> Node2D & {
    m_position = other.m_position;
    m_rotation = other.m_rotation;
    m_scale = other.m_scale;

    return *this;
}

auto Node2D::duplicate() const -> std::shared_ptr<Entity> {
    OE_CORE_ERROR("This class is an abstract class, do not try to duplicate it!");
    return nullptr;
}

void Node2D::onAttach() {}

void Node2D::onDetach() {}

void Node2D::onUpdate(float delta) {}

void Node2D::onEvent(Event &event) {}

OE_SETUP_ENTITY_TYPE_DEF(Node2D, Node2D)

Node2D::Node2D(Vector3 position, float rotation, Vector3 scale)
    : m_position(position), m_rotation(rotation), m_scale(scale), Entity("Node2D") {}

auto Node2D::isDrawable() const -> bool { return false; }

auto Node2D::getLocalMatrix() const -> Matrix4 {
    Matrix4 mat = {1.0f};

    // clang-format off

    mat = glm::translate    (mat, m_position);
    mat = glm::rotate       (mat, m_rotation, glm::vec3(0, 0, 1));
    mat = glm::scale        (mat, m_scale);

    // clang-format on

    return mat;
}

auto Node2D::getWorldMatrix() const -> Matrix4 {
    // TODO: Optimize this piece of garbage

    if (!isPartOfEngine()) {
        return {1.0f};
    }

    Entity *entity = &getParent();

    while (entity->getType() != EntityType::Root && !entity->isDrawable()) {
        entity = &entity->getParent();
    }

    if (entity->getType() == EntityType::Root) {
        return getLocalMatrix();
    }

    return dynamic_cast<Node2D &>(*entity).getWorldMatrix() * getLocalMatrix();
}

auto Node2D::isPositionInShape(Vector2 position) const -> bool { return false; }

auto Node2D::isHovered(bool passThrough, bool ignoreChildren) -> bool {
    if (!isPartOfEngine()) {
        return false;
    }

    std::vector<Entity *> ignoreList;

    /**
     * @brief childBlocking == false, ignore children hovering (passthrough)
     */
    if (passThrough) {
        getRenderEngine().traversePostOrder(getRenderEngine().getRoot(), [&ignoreList](Entity &entity) -> void {
            // This is a separator
            ignoreList.push_back(&entity);
        });
        ignoreList.erase(std::remove(ignoreList.begin(), ignoreList.end(), this), ignoreList.end());

        return getRenderEngine().isHovered(*this, ignoreList);
    }

    if (ignoreChildren) {
        getRenderEngine().traversePostOrder(*this, [&ignoreList](Entity &entity) -> void {
            // This is a separator
            ignoreList.push_back(&entity);
        });
        ignoreList.erase(std::remove(ignoreList.begin(), ignoreList.end(), this), ignoreList.end());

        return getRenderEngine().isHovered(*this, ignoreList);
    }

    return getRenderEngine().isHovered(*this, ignoreList);
}

auto Node2D::getPosition() const -> Vector3 { return m_position; }

auto Node2D::getRotation() const -> float { return m_rotation; }

auto Node2D::getScale() const -> Vector3 { return m_scale; }

void Node2D::setPosition(Vector3 position) {
    m_position = position;

    if (isPartOfEngine()) {
        getRenderEngine().reload();
    }
}

void Node2D::setRotation(float rotation) {
    m_rotation = rotation;

    if (isPartOfEngine()) {
        getRenderEngine().reload();
    }
}

void Node2D::setScale(Vector3 scale) {
    m_scale = scale;

    if (isPartOfEngine()) {
        getRenderEngine().reload();
    }
}
} // namespace ObsidianEdge
