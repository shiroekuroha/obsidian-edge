#include <pch.h>

#include "entity.h"

namespace ObsidianEdge {
Entity::Entity(Entity &parent) : m_parent(&parent) {}

Entity::Entity() : m_parent(nullptr) {}

Entity::~Entity() = default;

Entity::Entity(const Entity &other) : m_parent(other.m_parent) { *this = other; }

Entity::Entity(Entity &&other) noexcept : m_parent(other.m_parent) { *this = std::move(other); }

auto Entity::operator=(const Entity &other) -> Entity & {
    m_parent = other.m_parent;
    return *this;
}

auto Entity::operator=(Entity &&other) noexcept -> Entity & {
    m_parent = other.m_parent;
    return *this;
}

auto Entity::operator==(const Entity &other) const -> bool { return this == &other; }

void Entity::setTransform(Matrix4 transform) {}

auto Entity::getTransform() const -> Matrix4 {
    if (m_parent != nullptr) {
        return m_parent->getTransform();
    }

    return 1.0f;
}

void Entity::onAttach() {}

void Entity::onDetach() {}

void Entity::onUpdate(float delta) {}

void Entity::onEvent(Event &event) {}

void Entity::passUpdate(float delta) {
    onUpdate(delta);

    std::for_each(m_children.begin(), m_children.end(),
                  [delta](const std::shared_ptr<Entity> &entity) -> void { entity->passUpdate(delta); });
}

void Entity::passEvent(Event &event) {
    onEvent(event);

    std::for_each(m_children.begin(), m_children.end(),
                  [&event](const std::shared_ptr<Entity> &entity) -> void { entity->passEvent(event); });
}

auto Entity::getStaticType() -> EntityType { return EntityType::Entity; }

auto Entity::getType() const -> EntityType { return EntityType::Entity; }

auto Entity::getStaticCategory() -> EntityCategory { return EntityCategory::Generic; }

auto Entity::getCategory() const -> EntityCategory { return EntityCategory::Generic; }

void Entity::draw(Shader &shader) {}

void Entity::assignParent(Entity *parent) { m_parent = parent; }

auto Entity::getParent() -> Entity & { return *m_parent; }

auto Entity::getParentNative() const -> Entity * { return m_parent; }

void Entity::addChild(Entity *entity) {
    m_children.push_back(std::shared_ptr<Entity>(entity));
    entity->assignParent(this);
    entity->onAttach();
}

void Entity::removeChild(Entity &entity) {
    auto it = std::find_if(m_children.begin(), m_children.end(),
                           [&entity](const std::shared_ptr<Entity> &current) -> bool { return *current == entity; });

    m_children.erase(it);
    entity.assignParent(nullptr);
    entity.onDetach();
}

auto Entity::getChild(unsigned int index) -> Entity & { return *m_children[index]; }

auto Entity::findChild(const std::function<bool(Entity &)> &func) -> Entity & {
    auto it = std::find_if(m_children.begin(), m_children.end(),
                           [&func](const std::shared_ptr<Entity> &entity) -> bool { return func(*entity); });

    return **it;
}

auto Entity::begin() -> std::vector<std::shared_ptr<Entity>>::iterator { return m_children.begin(); }

auto Entity::end() -> std::vector<std::shared_ptr<Entity>>::iterator { return m_children.end(); }
} // namespace ObsidianEdge
