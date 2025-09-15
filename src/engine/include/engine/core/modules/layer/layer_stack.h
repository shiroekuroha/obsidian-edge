#pragma once

#include "engine/core/modules/layer/layer.h"

namespace ObsidianEdge
{
class OE_API LayerStack
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
    unsigned int m_stackBreakIndex;
};
}
