#pragma once

#include "core/renderer/ecs/node2d.h"

namespace ObsidianEdge {
class Rectangle : public Node2D {
public:
    // ------------------------------------ Base Begin ------------------------------------

    Rectangle(const char *name = "Node2D Rectangle");
    ~Rectangle() override;

    Rectangle(const Rectangle &other);
    Rectangle(Rectangle &&other) noexcept;

    auto operator=(const Rectangle &other) -> Rectangle &;
    auto operator=(Rectangle &&other) noexcept -> Rectangle &;

    [[nodiscard]] auto duplicate() const -> std::shared_ptr<Entity> override;

    void onAttach() override;
    void onDetach() override;
    void onUpdate(float delta) override;
    void onEvent(Event &event) override;

    OE_SETUP_ENTITY_TYPE_DEC

    // ------------------------------------- Base End -------------------------------------

    Rectangle(Vector3 postion, float rotation, Vector3 scale, Vector2 size, Vector4 color);

    [[nodiscard]] auto isDrawable() const -> bool final;

    [[nodiscard]] auto isPositionInShape(Vector2 position) const -> bool final;
    [[nodiscard]] auto getRenderingData() const -> QuadData final;

    [[nodiscard]] auto getSize() const -> Vector2;
    [[nodiscard]] auto getColor() const -> Vector4;

    void setSize(Vector2 size);
    void setColor(Vector4 color);

private:
    Vector2 m_size{100.0f};
    Vector4 m_color{1.0f};
};
} // namespace ObsidianEdge
