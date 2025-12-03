#pragma once

#include "core/event/event.h"

namespace ObsidianEdge {
class Layer {
public:
    Layer(const char *name = "Layer");
    virtual ~Layer() = default;

    Layer(const Layer &other) = default;
    Layer(Layer &&other) noexcept = default;

    auto operator=(const Layer &other) -> Layer & = default;
    auto operator=(Layer &&other) noexcept -> Layer & = default;

    virtual void onAttach();
    virtual void onDetach();
    virtual void onUpdate(float delta);
    virtual void onEvent(Event &event);

    [[nodiscard]] inline auto getName() const -> std::string { return m_name; }

private:
    std::string m_name;
};
} // namespace ObsidianEdge
