#include <pch.h>

#include "core/log/log.h"
#include "node.h"

namespace ObsidianEdge {
Node::Node(const char *name) : Entity(name) {}

Node::~Node() = default;

Node::Node(const Node &other) { *this = other; };

Node::Node(Node &&other) noexcept { *this = std::move(other); }

auto Node::operator=(const Node &other) -> Node & { return *this; }

auto Node::operator=(Node &&other) noexcept -> Node & { return *this; }

auto Node::duplicate() const -> std::shared_ptr<Entity> {
    OE_CORE_ERROR("This class is an abstract class, do not try to duplicate it!");
    return nullptr;
}

void Node::onAttach() {}

void Node::onDetach() {}

void Node::onUpdate(float delta) {}

void Node::onEvent(Event &event) {}

OE_SETUP_ENTITY_TYPE_DEF(Node, Node)

auto Node::isDrawable() const -> bool { return false; }
} // namespace ObsidianEdge
