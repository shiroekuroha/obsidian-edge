#include <engine/core/pch.h>

#include "engine/core/layer/layer_stack.h"

namespace ObsidianEdge
{
LayerStack::LayerStack () { m_stackBreak = m_layers.begin (); }

LayerStack::~LayerStack () { clear (); }

void
LayerStack::pushLayer (Layer *layer)
{
    m_stackBreak = m_layers.emplace (m_stackBreak, layer);
}

void
LayerStack::popLayer (Layer *layer)
{
    auto it = std::find (m_layers.begin (), m_layers.end (), layer);

    if (it != m_layers.end ())
        {
            m_layers.erase (it);
            m_stackBreak--;
        }
}

void
LayerStack::pushOverlay (Layer *overlay)
{
    m_layers.emplace_back (overlay);
}

void
LayerStack::popOverlay (Layer *overlay)
{
    auto it = std::find (m_layers.begin (), m_layers.end (), overlay);

    if (it != m_layers.end ())
        {
            m_layers.erase (it);
        }
}

void
LayerStack::clear ()
{
    for (Layer *layer : m_layers)
        delete layer;

    m_layers.clear ();
}

std::vector<Layer *>::iterator
LayerStack::begin ()
{
    return m_layers.begin ();
}

std::vector<Layer *>::iterator
LayerStack::end ()
{
    return m_layers.end ();
}
}
