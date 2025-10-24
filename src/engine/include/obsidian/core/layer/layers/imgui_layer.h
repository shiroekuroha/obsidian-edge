#ifndef OE_IMGUI_LAYER_H
#define OE_IMGUI_LAYER_H

#include "imgui.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "obsidian/core/application.h"
#include "obsidian/core/layer/layer.h"

namespace ObsidianEdge
{
class ImGuiLayer : public Layer
{
public:
    ImGuiLayer () = default;
    ~ImGuiLayer () override = default;

    ImGuiLayer (const ImGuiLayer &other) = default;
    ImGuiLayer (ImGuiLayer &&other) noexcept = default;

    auto operator= (const ImGuiLayer &other) -> ImGuiLayer & = default;
    auto operator= (ImGuiLayer &&other) noexcept -> ImGuiLayer & = default;

    void onAttach () override;
    void onDetach () override;
    void onUpdate (float delta) override;
    void onEvent (SharedPointer<Event> event) override;

private:
    float m_time = 0;
};

auto glfwKeyToImGuiKey (int keycode, int scancode) -> ImGuiKey;
}

#endif
