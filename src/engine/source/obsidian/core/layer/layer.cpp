#include <obsidian/core/data/pch.h>

#include "obsidian/core/layer/layer.h"

namespace ObsidianEdge
{
Layer::Layer (const char *name) : m_name (name) {}

void
Layer::onAttach ()
{
}

void
Layer::onDetach ()
{
}

void
Layer::onUpdate (float delta)
{
}

void
Layer::onEvent (SharedPointer<Event> event)
{
}
}
