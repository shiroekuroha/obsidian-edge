#ifndef OE_LAYER_STACK_H
#define OE_LAYER_STACK_H

#include "obsidian/core/core.h"

#include "obsidian/core/layer/layer.h"

namespace ObsidianEdge
{
class OE_API LayerStack
{
public:
    LayerStack () = default;
    virtual ~LayerStack ();

    LayerStack (const LayerStack &other) = default;
    LayerStack (LayerStack &&other) noexcept = default;

    auto operator= (const LayerStack &other) -> LayerStack & = default;
    auto operator= (LayerStack &&other) noexcept -> LayerStack & = default;

    void pushLayer (Layer *layer);
    void popLayer (Layer *layer);

    void pushOverlay (Layer *overlay);
    void popOverlay (Layer *overlay);

    void clear ();

    auto begin () -> Vector<Layer *>::iterator;
    auto end () -> Vector<Layer *>::iterator;

    inline
    operator Vector<Layer *> & ()
    {
        return m_layers;
    }

private:
    Vector<Layer *> m_layers;
    unsigned int m_stackBreakIndex = 0;
};
}

#endif
