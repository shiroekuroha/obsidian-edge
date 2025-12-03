#pragma once

#include "imgui.h"

#include "core/layer/layer.h"

namespace ObsidianEdge {
class ImGuiLayer : public Layer {
public:
    ImGuiLayer() = default;
    ~ImGuiLayer() override = default;

    ImGuiLayer(const ImGuiLayer &other) = default;
    ImGuiLayer(ImGuiLayer &&other) noexcept = default;

    auto operator=(const ImGuiLayer &other) -> ImGuiLayer & = default;
    auto operator=(ImGuiLayer &&other) noexcept -> ImGuiLayer & = default;

    void onAttach() override;
    void onDetach() override;
    void onUpdate(float delta) override;
    void onEvent(Event &event) override;

private:
    float m_time = 0;
};

auto glfwKeyToImGuiKey(int keycode, int scancode) -> ImGuiKey;
} // namespace ObsidianEdge
