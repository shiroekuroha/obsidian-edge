#pragma once

#include "core/renderer/ecs/entity.h"

namespace ObsidianEdge {
class Node : public Entity {
public:
    // ------------------------------------ Base Begin ------------------------------------

    Node(const char *name = "Node");
    ~Node() override;

    Node(const Node &other);
    Node(Node &&other) noexcept;

    auto operator=(const Node &other) -> Node &;
    auto operator=(Node &&other) noexcept -> Node &;

    [[nodiscard]] auto duplicate() const -> std::shared_ptr<Entity> override = 0;

    void onAttach() override;
    void onDetach() override;
    void onUpdate(float delta) override;
    void onEvent(Event &event) override;

    OE_SETUP_ENTITY_TYPE_DEC

    // ------------------------------------- Base End -------------------------------------

    [[nodiscard]] auto isDrawable() const -> bool final;

private:
};
} // namespace ObsidianEdge
