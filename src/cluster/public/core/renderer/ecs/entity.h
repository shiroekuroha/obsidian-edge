#pragma once

#include "core/event/event.h"
#include "core/renderer/modules/shader.h"

namespace ObsidianEdge {
enum class EntityType : std::int8_t {
    Entity = 0,

    Node,
    Node2D,
    Node3D,
};

enum class EntityCategory : std::int8_t {
    Generic = 0,

    RenderOff,
    Render2D,
    Render3D,
    Utility
};

class Entity {
public:
    Entity(Entity &parent);

    Entity();
    virtual ~Entity();

    Entity(const Entity &other);
    Entity(Entity &&other) noexcept;

    auto operator=(const Entity &other) -> Entity &;
    auto operator=(Entity &&other) noexcept -> Entity &;

    auto operator==(const Entity &other) const -> bool;

    virtual void setTransform(Matrix4 transform);
    [[nodiscard]] virtual auto getTransform() const -> Matrix4;

    virtual void onAttach() = 0;
    virtual void onDetach() = 0;
    virtual void onUpdate(float delta) = 0;
    virtual void onEvent(Event &event) = 0;

    void passUpdate(float delta);
    void passEvent(Event &event);

    static auto getStaticType() -> EntityType;
    [[nodiscard]] virtual auto getType() const -> EntityType = 0;

    static auto getStaticCategory() -> EntityCategory;
    [[nodiscard]] virtual auto getCategory() const -> EntityCategory = 0;

    virtual void draw(Shader &shader);

    void assignParent(Entity *parent);
    auto getParent() -> Entity &;
    [[nodiscard]] auto getParentNative() const -> Entity *;

    void addChild(Entity *entity);
    void removeChild(Entity &child);

    auto getChild(unsigned int index) -> Entity &;
    auto findChild(const std::function<bool(Entity &)> &func) -> Entity &;

    auto begin() -> std::vector<std::shared_ptr<Entity>>::iterator;
    auto end() -> std::vector<std::shared_ptr<Entity>>::iterator;

private:
    gsl::owner<Entity *> m_parent;
    std::vector<std::shared_ptr<Entity>> m_children = {};
};
} // namespace ObsidianEdge
