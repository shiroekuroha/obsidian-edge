#pragma once

#include "engine/core/layer/layer.h"

namespace ObsidianEdge
{
class LayerStack
{
public:
    LayerStack ();
    virtual ~LayerStack ();

private:
    std::vector<Layer> m_layers;
    std::vector<Layer> m_overlays;
};
}
