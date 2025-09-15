#pragma once

#include "engine/core/core.h"
#include "engine/core/modules/event/event.h"

namespace ObsidianEdge
{
class OE_API Layer
{
public:
    Layer (const char *name = "Layer");
    virtual ~Layer ();

    virtual void onAttach ();
    virtual void onDetach ();
    virtual void onUpdate ();
    virtual void onEvent (Event &event);

    virtual void begin ();
    virtual void end ();
    virtual void onRender ();

    inline const std::string &
    getName () const
    {
        return m_name;
    }

protected:
    std::string m_name;
};
}
