#include <pch.h>

#include "glass.h"

// ! This order matters!
// clang-format off
#include <glad/gl.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "core/event/event_app.h"
#include "core/event/event_mouse.h"
#include "core/log/log.h"
#include "core/renderer/ecs/node2d.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

namespace ObsidianEdge {

Glass::Glass() { init(); }

Glass::~Glass() { yeet(); }

void Glass::onUpdate(float delta) {
    getRoot().passUpdate(delta);

    draw();
}

void Glass::onEvent(Event &event) {
    EventDispatcher eventDispatcher(event);

    eventDispatcher.dispatch<MouseMovedEvent>([this](MouseMovedEvent &event) -> bool {
        m_lastMousePosition = event.getLocation();
        m_lastMousePosition.y = getViewportSize().y - event.getLocation().y;

        return false;
    });

    eventDispatcher.dispatch<WindowResizedEvent>([this](WindowResizedEvent &event) -> bool {
        reload();

        return false;
    });

    getRoot().passEvent(event);
}

void Glass::init() {
    static const float x = 200.0f;
    static const float y = 200.0f;

    shader.create("shaders/vertex.glsl", "shaders/fragment.glsl");

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));
    proj = glm::orthoLH(
        // Left, Right
        0.0f, (float)getViewportSize().x,
        // Up, Down
        0.0f, (float)getViewportSize().y,
        // Near, Far
        -1.0f, 1.0f);

    createBuffers();
}

void Glass::yeet() {
    shader.destroy();
    destroyBuffers();
}

void Glass::createBuffers() {
    if (!m_renderObjects.empty())
        destroyBuffers();

    traversePreOrder(getRoot(), [this](Entity &entity) -> void {
        if (entity.isDrawable()) {
            QuadData data = dynamic_cast<Node2D &>(entity).getRenderingData();

            unsigned int vao = 0;
            unsigned int vbo = 0;
            unsigned int ibo = 0;

            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);

            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, static_cast<long>(sizeof(Vertex) * data.vertices.size()), data.vertices.data(),
                         GL_STATIC_DRAW);

            glGenBuffers(1, &ibo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<long>(sizeof(Index) * data.indices.size()), data.indices.data(),
                         GL_STATIC_DRAW);

            // NOLINTBEGIN(cppcoreguidelines-pro-type-cstyle-cast)
            // NOLINTBEGIN(performance-no-int-to-ptr)

            glVertexAttribPointer(0, 4, GL_FLOAT, 0, sizeof(Vertex), (void *)offsetof(Vertex, position));
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 4, GL_FLOAT, 0, sizeof(Vertex), (void *)offsetof(Vertex, tintColor));
            glEnableVertexAttribArray(1);

            glVertexAttribPointer(2, 2, GL_FLOAT, 0, sizeof(Vertex), (void *)offsetof(Vertex, texCoord));
            glEnableVertexAttribArray(2);

            // NOLINTEND(performance-no-int-to-ptr)
            // NOLINTEND(cppcoreguidelines-pro-type-cstyle-cast)

            glBindVertexArray(0);

            m_renderObjects.push_back({data, vao, vbo, ibo});
        }
    });
}

void Glass::destroyBuffers() {
    for (RenderObject &obj : m_renderObjects) {
        glDeleteVertexArrays(1, &obj.vao);
        glDeleteBuffers(1, &obj.vbo);
        glDeleteBuffers(1, &obj.ibo);
    }

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    m_renderObjects.clear();
}

void Glass::draw() {
    glClearColor(bg.r, bg.g, bg.b, bg.a);
    glClear(GL_COLOR_BUFFER_BIT);

    for (RenderObject &obj : m_renderObjects) {
        Matrix4 mvp = proj * view * obj.data.transform;

        obj.data.texture.bind();
        shader.setUniform1i("g_Sampler", 0);
        shader.setUniformMatrix4fv("u_Model", 1, GL_FALSE, &obj.data.transform[0][0]);
        shader.setUniformMatrix4fv("u_View", 1, GL_FALSE, &view[0][0]);
        shader.setUniformMatrix4fv("u_Proj", 1, GL_FALSE, &proj[0][0]);

        glBindVertexArray(obj.vao);
        glBindBuffer(GL_ARRAY_BUFFER, obj.vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj.ibo);

        glDrawElements(GL_TRIANGLES, (int)obj.data.indices.size(), GL_UNSIGNED_BYTE, nullptr);
    }
}

void Glass::reload() {
    destroyBuffers();
    createBuffers();
}

auto Glass::isHovered(Entity &entity, std::vector<Entity *> ignoreList) -> bool {
    Node2D *selected = nullptr;

    traversePostOrder(getRoot(), [this, &selected, &ignoreList](Entity &entity) -> void {
        bool ignoreEntity = false;

        std::for_each(ignoreList.begin(), ignoreList.end(), [&ignoreEntity, &entity](Entity *target) -> void {
            if (target == &entity) {
                ignoreEntity = true;
            }
        });

        if (!ignoreEntity && entity.isDrawable()) {
            auto &node = dynamic_cast<Node2D &>(entity);

            if (selected == nullptr && node.isPositionInShape(m_lastMousePosition)) {
                selected = &node;
            }
        }
    });

    return entity == *selected;
};
} // namespace ObsidianEdge
