#ifndef OE_GLASS_LAYER_H
#define OE_GLASS_LAYER_H

#include "obsidian/core/application.h"
#include "obsidian/core/layer/layer.h"

namespace ObsidianEdge
{
class GlassLayer : public Layer
{
public:
    GlassLayer ();
    ~GlassLayer () override;

    GlassLayer (const GlassLayer &other) = default;
    GlassLayer (GlassLayer &&other) noexcept = default;

    auto operator= (const GlassLayer &other) -> GlassLayer & = default;
    auto operator= (GlassLayer &&other) noexcept -> GlassLayer & = default;

private:
};
}

#endif
