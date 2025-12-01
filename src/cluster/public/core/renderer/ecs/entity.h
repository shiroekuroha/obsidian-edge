#pragma once

#include "core/event/event.h"

namespace ObsidianEdge {
class RenderEngine;
class Root;

// NOLINTBEGIN(cppcoreguidelines-macro-usage)

#define OE_SETUP_ENTITY_TYPE_DEC                                                                                               \
    [[nodiscard]] auto getStaticType() const -> EntityType;                                                                    \
    [[nodiscard]] virtual auto getType() const -> EntityType override;

#define OE_SETUP_ENTITY_TYPE_DEF(className, type)                                                                              \
    [[nodiscard]] auto className::getStaticType() const -> EntityType { return EntityType::type; }                             \
    [[nodiscard]] auto className::getType() const -> EntityType { return EntityType::type; }

// NOLINTEND(cppcoreguidelines-macro-usage)

enum class EntityType : std::int8_t {
    Entity = 0,
    Root,

    // clang-format off
    Node,
        GameController,

    Node2D,
        Rectangle,
        Image,
    // clang-format on
};

class Entity {
public:
    // ------------------------------------ Base Begin ------------------------------------

    Entity(const char *name = "Entity");
    virtual ~Entity();

    Entity(const Entity &other);
    Entity(Entity &&other) noexcept;

    auto operator=(const Entity &other) -> Entity &;
    auto operator=(Entity &&other) noexcept -> Entity &;

    [[nodiscard]] virtual auto duplicate() const -> std::shared_ptr<Entity> = 0;

    virtual void onAttach();
    virtual void onDetach();
    virtual void onUpdate(float delta);
    virtual void onEvent(Event &event);

    [[nodiscard]] auto getStaticType() const -> EntityType;
    [[nodiscard]] virtual auto getType() const -> EntityType = 0;

    // ------------------------------------- Base End -------------------------------------

    auto operator==(const Entity &other) const -> bool;

    template <typename T> static auto duplicateTyped(const T &object) -> std::shared_ptr<T> {
        return std::make_shared<T>(T(object));
    }

    void passUpdate(float delta);
    void passEvent(Event &event);

    void setName(const char *name);
    [[nodiscard]] auto getName() const -> std::string;

    void setParent(Entity *parent);
    [[nodiscard]] auto getParent() const -> Entity &;

    void addChild(const std::shared_ptr<Entity> &entity);

    void removeChild(Entity &child);
    void removeChild(const std::function<bool(Entity &)> &func);

    void clearChildren();

    [[nodiscard]] auto getChild(unsigned int index) const -> Entity &;
    [[nodiscard]] auto getChild(const std::function<bool(Entity &)> &func) const -> Entity *;

    void forEachChild(const std::function<void(Entity &)> &func);

    [[nodiscard]] auto isPartOfEngine() const -> bool;
    [[nodiscard]] auto getRenderEngine() const -> RenderEngine &;

    [[nodiscard]] virtual auto isDrawable() const -> bool = 0;

private:
    std::string m_name;

    gsl::owner<Entity *> m_parent = nullptr;
    std::vector<std::shared_ptr<Entity>> m_children = {};
};
} // namespace ObsidianEdge
