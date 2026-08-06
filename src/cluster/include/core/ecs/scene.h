#pragma once

#include "core.h"

#include "node.h"

namespace ObsidianEdge {
class OE_API Scene {
public:
    Scene() = default;
    ~Scene() = default;

    Scene(const Scene& other) = default;
    Scene(Scene&& other) noexcept = default;

    auto operator=(const Scene& other) -> Scene& = default;
    auto operator=(Scene&& other) noexcept -> Scene& = default;

    auto getNode(NodeID id) -> Node&;
    auto getNode(NodeID id) const -> const Node&;

    auto getRoot() -> Node&;
    auto getRoot() const -> const Node&;

    void setRoot(NodeID root);

    void traverseNode(Node& node, const std::function<bool(Node&)>& fn);

    template <class T, typename... Args> auto createNode(Args&&... args) -> NodeID {
        static_assert(std::is_base_of_v<Node, T>, "T must inherit Node");

        NodeID id = m_nextUniqueID++;

        m_storage.emplace(id, std::make_unique<T>(std::forward<Args>(args)...));
        m_storage[id]->setID(id);

        return id;
    }

    void onInit();
    void onUpdate(double delta);
    void onEvent(Event& event);

    auto gatherRenderingData();

private:
    NodeID root = 0;

    NodeID m_nextUniqueID = 1;
    std::unordered_map<NodeID, std::unique_ptr<Node>> m_storage;
};
} // namespace ObsidianEdge
