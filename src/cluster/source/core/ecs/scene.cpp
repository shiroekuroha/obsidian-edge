#include <pch.h>

#include "core/ecs/scene.h"

namespace ObsidianEdge {
auto Scene::getNode(NodeID id) -> Node & { return *m_storage.at(id).get(); }

auto Scene::getNode(NodeID id) const -> const Node & { return *m_storage.at(id).get(); }

auto Scene::getRoot() -> Node & { return getNode(root); }

auto Scene::getRoot() const -> const Node & { return getNode(root); }

void Scene::setRoot(NodeID id) { root = id; }

void Scene::traverseNode(Node &node, const std::function<bool(Node &)> &fn) {
    // Stop traverse branch on false

    if (fn(node)) {
        for (NodeID child : node.getChildren())
            traverseNode(getNode(child), fn);
    }
}

void Scene::onInit() {
    traverseNode(getNode(root), [this](Node &node) -> bool {
        node.onReady(*this);
        return true;
    });
}

void Scene::onUpdate(double delta) {
    traverseNode(getNode(root), [this, delta](Node &node) -> bool {
        node.onUpdate(*this, delta);
        return true;
    });
}

void Scene::onEvent(Event &event) {
    traverseNode(getNode(root), [this, &event](Node &node) -> bool {
        node.onEvent(*this, event);

        if (event.isHandled())
            return false;

        return true;
    });
}
} // namespace ObsidianEdge
