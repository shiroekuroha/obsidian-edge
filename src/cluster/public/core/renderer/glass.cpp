#include <pch.h>

#include "glass.h"

// ! This order matters!
// clang-format off
#include <glad/gl.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "app/application.h"
#include "core/renderer/ecs/node2d.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_projection.hpp"
#include "glm/ext/matrix_transform.hpp"

namespace ObsidianEdge {

Glass::Glass() : root(std::make_shared<Node2D>(Node2D({0.0f, 0.0f}, {200.0f, 200.0f}, {1.0f, 0.0f, 0.0f, 1.0f}))) {
    shader.create("shaders/vertex.glsl", "shaders/fragment.glsl");

    view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));
    proj = glm::orthoLH(
        // Left, Right
        0.0f, (float)Application::get().window().getWidth(),
        // Up, Down
        0.0f, (float)Application::get().window().getHeight(),
        // Near, Far
        -1.0f, 1.0f);

    root->onAttach();
    root->addChild(new Node2D({200.0f, 0.0f}, {200.0f, 200.0f}, {1.0f, 0.0f, 1.0f, 1.0f}));
    root->addChild(new Node2D({0.0f, 200.0f}, {200.0f, 200.0f}, {0.0f, 1.0f, 0.0f, 1.0f}));
    root->addChild(new Node2D({200.0f, 200.0f}, {200.0f, 200.0f}, {0.0f, 0.0f, 1.0f, 1.0f}));

    root->setTransform(glm::translate(root->getTransform(), Vector3(20.0f, 20.0f, 0.0f)));
}

Glass::~Glass() = default;

Glass::Glass(const Glass &other) { *this = other; }

Glass::Glass(Glass &&other) noexcept { *this = std::move(other); }

auto Glass::operator=(const Glass &other) -> Glass & { return *this; }

auto Glass::operator=(Glass &&other) noexcept -> Glass & { return *this; }

void Glass::onUpdate(float delta) {
    root->passUpdate(delta);

    glClearColor(0.25f, 0.25f, 0.25f, 0.25f);
    glClear(GL_COLOR_BUFFER_BIT);

    traverseTree([this](Entity &entity) -> void {
        if (entity.getType() == EntityType::Node2D) {
            Matrix4 mvp = proj * view * entity.getTransform();

            shader.setUniformMatrix4fv("g_MVP", 1, GL_FALSE, &mvp[0][0]);
            entity.draw(this->shader);
        }
    });
}

void Glass::onEvent(Event &event) { root->passEvent(event); }

void Glass::traverseTree(const std::function<void(Entity &)> &func) {
    std::vector<Entity *> targets = {root.get()};

    while (targets.size()) {
        std::vector<Entity *> next_targets = {};

        for (Entity *target : targets) {
            func(*target);
        }

        for (Entity *target : targets) {
            std::for_each(target->begin(), target->end(), [&next_targets](const std::shared_ptr<Entity> &entity) -> void {
                next_targets.push_back(entity.get());
            });
        }

        targets = next_targets;
    }
}

void Glass::makeRoot(Entity *entity) {
    if (root != nullptr)
        root->onDetach();

    root.reset(entity);
    root->onAttach();
}

auto Glass::getRoot() -> Entity & { return *root; }
} // namespace ObsidianEdge
