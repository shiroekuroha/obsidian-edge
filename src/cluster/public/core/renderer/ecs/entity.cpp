#include <pch.h>

#include "core/log/log.h"
#include "entity.h"
#include "root.h"

namespace ObsidianEdge {
Entity::Entity(const char *name) : m_name(name) {}

Entity::~Entity() = default;

Entity::Entity(const Entity &other) : m_name(other.m_name), m_parent(other.m_parent) { *this = other; }

Entity::Entity(Entity &&other) noexcept : m_parent(other.m_parent) { *this = std::move(other); }

auto Entity::operator=(const Entity &other) -> Entity & {
    m_name = other.m_name;
    m_parent = other.m_parent;

    return *this;
}

auto Entity::operator=(Entity &&other) noexcept -> Entity & {
    m_name = other.m_name;
    m_parent = other.m_parent;

    return *this;
}

auto Entity::duplicate() const -> std::shared_ptr<Entity> {
    OE_CORE_ERROR("This class is an abstract class, do not try to duplicate it!");
    return nullptr;
}

void Entity::onAttach() {}

void Entity::onDetach() {}

void Entity::onUpdate(float delta) {}

void Entity::onEvent(Event &event) {}

OE_SETUP_ENTITY_TYPE_DEF(Entity, Entity)

auto Entity::operator==(const Entity &other) const -> bool { return this == &other; }

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

void Entity::setName(const char *name) { m_name = name; }

auto Entity::getName() const -> std::string { return m_name; }

void Entity::setParent(Entity *parent) { m_parent = parent; }

auto Entity::getParent() const -> Entity & { return *m_parent; }

void Entity::addChild(const std::shared_ptr<Entity> &entity) {
    m_children.push_back(entity);
    entity->setParent(this);
    entity->onAttach();
}

void Entity::removeChild(Entity &entity) {
    auto it = std::find_if(m_children.begin(), m_children.end(),
                           [&entity](const std::shared_ptr<Entity> &current) -> bool { return *current == entity; });

    m_children.erase(it);
    entity.setParent(nullptr);
    entity.onDetach();
}

void Entity::removeChild(const std::function<bool(Entity &)> &func) {
    Entity *entity = getChild(func);

    if (entity != nullptr) {
        removeChild(*entity);
    }
}

void Entity::clearChildren() {
    while (!m_children.empty()) {
        std::shared_ptr<Entity> entity = m_children.back();
        m_children.pop_back();
        entity->setParent(nullptr);
        entity->onDetach();
        entity.reset();
    }
}

auto Entity::getChild(unsigned int index) const -> Entity & { return *m_children[index]; }

auto Entity::getChild(const std::function<bool(Entity &)> &func) const -> Entity * {
    auto it = std::find_if(m_children.begin(), m_children.end(),
                           [&func](const std::shared_ptr<Entity> &entity) -> bool { return func(*entity); });

    if (it != m_children.end())
        return it->get();

    return nullptr;
}

void Entity::forEachChild(const std::function<void(Entity &)> &func) {
    std::for_each(m_children.begin(), m_children.end(),
                  [this, func](std::shared_ptr<Entity> &entity) -> void { func(*entity.get()); });
}

auto Entity::isPartOfEngine() const -> bool {
    Entity *entity = m_parent;

    while (entity != nullptr && entity->getType() != EntityType::Root) {
        entity = entity->m_parent;
    }

    if (entity != nullptr) {
        return true;
    }

    return false;
}

auto Entity::getRenderEngine() const -> RenderEngine & {
    Entity *entity = m_parent;

    while (entity != nullptr && entity->getType() != EntityType::Root) {
        entity = entity->m_parent;
    }

    if (entity != nullptr) {
        return dynamic_cast<Root &>(*entity).getRenderEngine();
    }

    OE_CORE_ERROR("This component is not child of any Root component!")
    throw std::runtime_error("This component is not child of any Root component!");
}

auto Entity::isDrawable() const -> bool { return false; }
} // namespace ObsidianEdge
