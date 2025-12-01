#include <pch.h>

#include "core/log/log.h"
#include "root.h"

namespace ObsidianEdge {
Root::Root(RenderEngine *renderEngine, const char *name) : m_engine(renderEngine), Entity(name) {}

Root::~Root() = default;

auto Root::duplicate() const -> std::shared_ptr<Entity> {
    OE_CORE_ERROR("This class is a unique class, do not try to duplicate it!");
    return nullptr;
}

void Root::onAttach() {}

void Root::onDetach() {}

void Root::onUpdate(float delta) {}

void Root::onEvent(Event &event) {}

OE_SETUP_ENTITY_TYPE_DEF(Root, Root)

auto Root::isDrawable() const -> bool { return false; }

auto Root::getRenderEngine() const -> RenderEngine & { return *m_engine; }
} // namespace ObsidianEdge
