#ifndef OE_LAYER_H
#define OE_LAYER_H

#include "obsidian/core/core.h"
#include "obsidian/core/event/event.h"

namespace ObsidianEdge
{
class OE_API Layer
{
public:
    Layer (const char *name = "Layer");
    virtual ~Layer () = default;

    Layer (const Layer &other) = default;
    Layer (Layer &&other) noexcept = default;

    auto operator= (const Layer &other) -> Layer & = default;
    auto operator= (Layer &&other) noexcept -> Layer & = default;

    virtual void onAttach ();
    virtual void onDetach ();
    virtual void onUpdate (float delta);
    virtual void onEvent (SharedPointer<Event> event);

    [[nodiscard]] inline auto
    getName () const -> String
    {
        return m_name;
    }

private:
    String m_name;
};
}

#endif
