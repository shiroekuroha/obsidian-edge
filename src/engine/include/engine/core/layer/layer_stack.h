#pragma once

#include "engine/core/layer/layer.h"

namespace ObsidianEdge
{
class LayerStack
{
public:
    LayerStack ();
    virtual ~LayerStack ();

    void pushLayer (Layer *layer);
    void popLayer (Layer *layer);

    void pushOverlay (Layer *overlay);
    void popOverlay (Layer *overlay);

    void clear ();

    std::vector<Layer *>::iterator begin ();
    std::vector<Layer *>::iterator end ();

private:
    std::vector<Layer *> m_layers;
    std::vector<Layer *>::iterator m_stackBreak;
};
}
