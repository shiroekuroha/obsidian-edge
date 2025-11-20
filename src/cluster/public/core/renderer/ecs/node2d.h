#pragma once

#include "core/renderer/modules/generic.h"
#include "core/renderer/modules/shader.h"
#include "core/renderer/modules/texture.h"
#include "entity.h"
#include "glm/ext/matrix_transform.hpp"

namespace ObsidianEdge {
class Node2D : public Entity {
public:
    Node2D(Vector2 loc, Vector2 size, Vector4 color);

    Node2D();
    ~Node2D() override;

    Node2D(const Node2D &other);
    Node2D(Node2D &&other) noexcept;

    auto operator=(const Node2D &other) -> Node2D &;
    auto operator=(Node2D &&other) noexcept -> Node2D &;

    void setTransform(Matrix4 transform) override;
    [[nodiscard]] auto getTransform() const -> Matrix4 override;

    [[nodiscard]] virtual auto getVertices() const -> std::vector<Vertex>;
    [[nodiscard]] virtual auto getIndices() const -> std::vector<Index>;

    void onAttach() override;
    void onDetach() override;
    void onUpdate(float delta) override;
    void onEvent(Event &event) override;

    static auto getStaticType() -> EntityType;
    [[nodiscard]] auto getType() const -> EntityType override;

    static auto getStaticCategory() -> EntityCategory;
    [[nodiscard]] auto getCategory() const -> EntityCategory override;

    void draw(Shader &shader) override;

private:
    Matrix4 m_transform = {1.0f};

    unsigned int m_vao = 0;
    unsigned int m_vbo = 0;
    unsigned int m_ibo = 0;

    Vector2 m_loc, m_size;
    Vector4 m_color;
    Texture texture = {"textures/default.png"};
};
} // namespace ObsidianEdge
