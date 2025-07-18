#include "engine/core/tree/base.h"

namespace ObsidianEdge
{
Base::Base () : p_name ("Base") {};

Base::Base (const char *name) : p_name (name) {};

Base &
Base::getParent () const
{
    return *m_parent;
}

const std::vector<std::shared_ptr<Base>> &
Base::getChildren () const
{
    return m_children;
}
}