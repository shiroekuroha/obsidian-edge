#pragma once

#include "core/event/event.h"

namespace ObsidianEdge {
/**
 * @brief Logic / Rendering system layer for passing data and events
 */
class OE_API Layer {
public:
    /**
     * @brief Construct a new Layer object
     *
     * @param name Name for debug, might remove after production
     */
    Layer(const char *name = "Layer");
    virtual ~Layer() = default;

    /**
     * @brief Copy Construct a new Layer object
     *
     * @param other
     */
    Layer(const Layer &other) = default;

    /**
     * @brief Move Construct a new Layer object
     *
     * @param other
     */
    Layer(Layer &&other) noexcept = default;

    /**
     * @brief Copy Assignment for Layer object
     *
     * @param other
     * @return Layer&
     */
    auto operator=(const Layer &other) -> Layer & = default;

    /**
     * @brief Move Assignment for Layer object
     *
     * @param other
     * @return Layer&
     */
    auto operator=(Layer &&other) noexcept -> Layer & = default;

    /**
     * @brief Called after attached to a Layer manager
     */
    virtual void onAttach();

    /**
     * @brief Called after detached from a Layer manager
     */
    virtual void onDetach();

    /**
     * @brief Called every frame from Layer manager, which triggered by Application
     *
     * @param delta Seconds passed after the last rendered/completed frame
     */
    virtual void onUpdate(double delta);

    /**
     * @brief Called on events parsed from Layer manager
     *
     * @param event Event object parsed from Layer manager
     */
    virtual void onEvent(Event &event);

    /**
     * @brief Get the Name of the Layer
     *
     * @return std::string name of Layer
     */
    [[nodiscard]] inline auto getName() const -> std::string { return m_name; }

private:
    std::string m_name;
};
} // namespace ObsidianEdge
