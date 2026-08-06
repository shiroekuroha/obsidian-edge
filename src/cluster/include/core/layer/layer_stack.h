#pragma once

#include "core.h"
#include "core/layer/layer.h"

namespace ObsidianEdge {
/**
 * @brief Layer manager for Layer objects
 */
class OE_API LayerStack {
public:
    LayerStack() = default;
    virtual ~LayerStack();

    /**
     * @brief Copy Construct a new Layer Stack object
     *
     * @param other
     */
    LayerStack(const LayerStack &other) = default;

    /**
     * @brief Move Construct a new Layer Stack object
     *
     * @param other
     */
    LayerStack(LayerStack &&other) noexcept = default;

    /**
     * @brief Copy Assignment
     *
     * @param other
     * @return LayerStack& this
     */
    auto operator=(const LayerStack &other) -> LayerStack & = default;

    /**
     * @brief Move Assignment
     *
     * @param other
     * @return LayerStack&
     */
    auto operator=(LayerStack &&other) noexcept -> LayerStack & = default;

    /**
     * @brief Push layer into the Layer Stack
     *
     * @param layer
     */
    void pushLayer(Layer *layer);

    /**
     * @brief Pop layer out of the Layer Stack
     *
     * @param layer
     */
    void popLayer(Layer *layer);

    /**
     * @brief Push overlay into Layer Stack
     *
     * @param overlay
     */
    void pushOverlay(Layer *overlay);

    /**
     * @brief Pop overlay out of the Layer Stack
     *
     * @param overlay
     */
    void popOverlay(Layer *overlay);

    /**
     * @brief Drop all layers
     */
    void clear();

    /**
     * @brief Begin of Layer Stack, used for iteration on Layer Stack
     *
     * @return std::vector<Layer *>::iterator
     */
    auto begin() -> std::vector<Layer *>::iterator;

    /**
     * @brief End of Layer Stack, used for iteration on Layer Stack
     *
     * @return std::vector<Layer *>::iterator
     */
    auto end() -> std::vector<Layer *>::iterator;

    /**
     * @brief Return the Layer Stack, will be remove in future
     *
     * @return std::vector<Layer *> &
     */
    inline operator std::vector<Layer *> &() { return m_layers; }

private:
    std::vector<Layer *> m_layers;
    unsigned int m_stackBreakIndex = 0;
};
} // namespace ObsidianEdge
