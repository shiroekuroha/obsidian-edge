#include "core.h"

#include "core/event/event.h"
#include "engine/handler_material.h"
#include "engine/handler_mesh.h"

namespace ObsidianEdge {
using NodeID = uint32_t;
using RenderObjData = struct RenderObjData {
    NodeID owner;

    MeshHandler mesh;
    MaterialHandler material;
};

class Scene; // ! Probably should do something else, but we ball...

class OE_API Node {
public:
    Node() = default;
    virtual ~Node() = default;

    Node(const Node &other) = delete;
    Node(Node &&other) noexcept = delete;

    auto operator=(const Node &other) -> Node & = delete;
    auto operator=(Node &&other) noexcept -> Node & = delete;

    [[nodiscard]] inline auto id() const -> NodeID { return m_id; }

    [[nodiscard]] inline auto getParent() const -> NodeID { return m_parent; }
    [[nodiscard]] inline auto getChildren() const -> const std::vector<NodeID> & { return m_children; }

    inline virtual auto isDrawable() -> bool { return false; }
    virtual auto getRenderData() -> RenderObjData;

    virtual void onReady(Scene &sceneContext);
    virtual void onUpdate(Scene &sceneContext, double delta);
    virtual void onEvent(Scene &sceneContext, Event &event);

protected:
    inline void setID(NodeID id) { m_id = id; }
    friend class Scene;

private:
    NodeID m_id = 0;

    NodeID m_parent = 0;
    std::vector<NodeID> m_children;
};
} // namespace ObsidianEdge
