#pragma once

#include "imgui.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "engine/core/application/application.h"
#include "engine/core/modules/layer/layer.h"

namespace ObsidianEdge
{
class ImGuiLayer : public Layer
{
public:
    ImGuiLayer ();
    virtual ~ImGuiLayer ();

    void onAttach () override;
    void onDetach () override;
    void onEvent (Event &event) override;

    virtual void begin () override;
    virtual void end () override;
    virtual void onRender () override;

private:
    float m_time = 0;
};

ImGuiKey glfwKeyToImGuiKey (int keycode, int scancode);
}
