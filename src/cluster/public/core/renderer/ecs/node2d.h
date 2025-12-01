#pragma once

#include "core/renderer/modules/generic.h"
#include "entity.h"

namespace ObsidianEdge {
class Node2D : public Entity {
public:
    // ------------------------------------ Base Begin ------------------------------------

    Node2D(const char *name = "Node2D");
    ~Node2D() override;

    Node2D(const Node2D &other);
    Node2D(Node2D &&other) noexcept;

    auto operator=(const Node2D &other) -> Node2D &;
    auto operator=(Node2D &&other) noexcept -> Node2D &;

    [[nodiscard]] auto duplicate() const -> std::shared_ptr<Entity> override = 0;

    void onAttach() override;
    void onDetach() override;
    void onUpdate(float delta) override;
    void onEvent(Event &event) override;

    OE_SETUP_ENTITY_TYPE_DEC

    // ------------------------------------- Base End -------------------------------------

    Node2D(Vector3 position, float rotation, Vector3 scale);

    [[nodiscard]] auto isDrawable() const -> bool override = 0;

    [[nodiscard]] virtual auto isPositionInShape(Vector2 position) const -> bool = 0;
    [[nodiscard]] auto isHovered(bool passThrough = false, bool ignoreChildren = false) -> bool;
    [[nodiscard]] virtual auto getRenderingData() const -> QuadData = 0;

    [[nodiscard]] auto getPosition() const -> Vector3;
    [[nodiscard]] auto getRotation() const -> float;
    [[nodiscard]] auto getScale() const -> Vector3;

    void setPosition(Vector3 position);
    void setRotation(float rotation);
    void setScale(Vector3 scale);

    [[nodiscard]] auto getLocalMatrix() const -> Matrix4;
    [[nodiscard]] auto getWorldMatrix() const -> Matrix4;

private:
    // clang-format off

    Vector3 m_position  {0.0f};
    float   m_rotation  {0.0f};
    Vector3 m_scale     {1.0f};

    // clang-format on
};
} // namespace ObsidianEdge
