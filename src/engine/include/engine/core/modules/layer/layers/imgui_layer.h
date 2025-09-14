#pragma once

#include "engine/core/application/application.h"
#include "engine/core/modules/layer/layer.h"
#include "engine/core/modules/render/imgui_renderer.h"

namespace ObsidianEdge
{
class ImGuiLayer : public Layer
{
public:
    ImGuiLayer ();
    virtual ~ImGuiLayer ();

    void onAttach () override;
    void onDetach () override;
    void onUpdate () override;
    void onEvent (Event &event) override;

private:
    float m_time = 0;
};

ImGuiKey KeyToImGuiKey (int keycode, int scancode);
}
