#include <engine/core/pch.h>

#include "engine/core/layer/layer.h"

namespace ObsidianEdge
{
Layer::Layer (const char *name) : m_name (name) {}

Layer::~Layer () {}

void
Layer::onAttach ()
{
}

void
Layer::onDetach ()
{
}

void
Layer::onUpdate ()
{
}

void
Layer::onEvent (Event &event)
{
}
}
