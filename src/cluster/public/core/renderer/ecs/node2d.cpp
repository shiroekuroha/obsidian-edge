#include <pch.h>

#include "node2d.h"

// ! This order matters!
// clang-format off
#include <glad/gl.h>
#include <GLFW/glfw3.h>
// clang-format on

namespace ObsidianEdge {
Node2D::Node2D(Vector2 loc, Vector2 size, Vector4 color) : m_loc(loc), m_size(size), m_color(color) {}

Node2D::Node2D() : m_loc(0.0f, 0.0f), m_size(1.0f, 1.0f), m_color(1.0f) {};

Node2D::~Node2D() = default;

Node2D::Node2D(const Node2D &other) : m_loc(other.m_loc), m_size(other.m_size), m_color(other.m_color) { *this = other; }

Node2D::Node2D(Node2D &&other) noexcept : m_loc(other.m_loc), m_size(other.m_size), m_color(other.m_color) {
    *this = std::move(other);
}

auto Node2D::operator=(const Node2D &other) -> Node2D & {
    m_transform = other.getTransform();

    m_vao = other.m_vao;
    m_vbo = other.m_vbo;
    m_ibo = other.m_ibo;

    m_loc = other.m_loc;
    m_size = other.m_size;
    m_color = other.m_color;

    return *this;
}

auto Node2D::operator=(Node2D &&other) noexcept -> Node2D & {
    m_transform = other.getTransform();

    m_vao = other.m_vao;
    m_vbo = other.m_vbo;
    m_ibo = other.m_ibo;

    m_loc = other.m_loc;
    m_size = other.m_size;
    m_color = other.m_color;

    return *this;
}

void Node2D::setTransform(Matrix4 transform) { m_transform = transform; }

auto Node2D::getTransform() const -> Matrix4 {
    if (getParentNative() != nullptr) {
        return m_transform * getParentNative()->getTransform();
    }

    return m_transform;
}

auto Node2D::getVertices() const -> std::vector<Vertex> {
    return {{{m_loc.x, m_loc.y, 0.0f, 1.0f}, m_color, {0.0f, 0.0f}},
            {{m_loc.x + m_size.x, m_loc.y, 0.0f, 1.0f}, m_color, {1.0f, 0.0f}},
            {{m_loc.x, m_loc.y + m_size.y, 0.0f, 1.0f}, m_color, {0.0f, 1.0f}},
            {{m_loc.x + m_size.x, m_loc.y + m_size.y, 0.0f, 1.0f}, m_color, {1.0f, 1.0f}}};
}

auto Node2D::getIndices() const -> std::vector<Index> { return {0, 1, 2, 3, 2, 1}; }

void Node2D::onAttach() {
    std::vector<Vertex> vertices = getVertices();
    std::vector<Index> indices = getIndices();

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, static_cast<long>(sizeof(Vertex) * vertices.size()), vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<long>(sizeof(Index) * indices.size()), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, 0, sizeof(Vertex), (void *)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, 0, sizeof(Vertex), (void *)offsetof(Vertex, tintColor));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, 0, sizeof(Vertex), (void *)offsetof(Vertex, texCoord));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Node2D::onDetach() {
    glDeleteBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDeleteVertexArrays(1, &m_vao);
    glBindVertexArray(0);
}

void Node2D::onUpdate(float delta) {}

void Node2D::onEvent(Event &event) {}

auto Node2D::getStaticType() -> EntityType { return EntityType::Node2D; }

auto Node2D::getType() const -> EntityType { return EntityType::Node2D; }

auto Node2D::getStaticCategory() -> EntityCategory { return EntityCategory::Render2D; }

auto Node2D::getCategory() const -> EntityCategory { return EntityCategory::Render2D; }

void Node2D::draw(Shader &shader) {
    texture.bind();
    shader.setUniform1i("g_Sampler", 0);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);
}
} // namespace ObsidianEdge
