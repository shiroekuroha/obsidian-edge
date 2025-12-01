#pragma once

#include "core/renderer/ecs/node2d.h"

namespace ObsidianEdge {
class Image : public Node2D {
public:
    // ------------------------------------ Base Begin ------------------------------------

    Image(const char *name = "Node2D Image");
    ~Image() override;

    Image(const Image &other);
    Image(Image &&other) noexcept;

    auto operator=(const Image &other) -> Image &;
    auto operator=(Image &&other) noexcept -> Image &;

    [[nodiscard]] auto duplicate() const -> std::shared_ptr<Entity> override;

    void onAttach() override;
    void onDetach() override;
    void onUpdate(float delta) override;
    void onEvent(Event &event) override;

    OE_SETUP_ENTITY_TYPE_DEC

    // ------------------------------------- Base End -------------------------------------

    Image(Vector3 postion, float rotation, Vector3 scale, Vector2 size, Vector4 tintColor, Texture texture);

    [[nodiscard]] auto isDrawable() const -> bool final;

    [[nodiscard]] auto isPositionInShape(Vector2 position) const -> bool final;
    [[nodiscard]] auto getRenderingData() const -> QuadData final;

    [[nodiscard]] auto getSize() const -> Vector2;
    [[nodiscard]] auto getTintColor() const -> Vector4;
    [[nodiscard]] auto getTexture() const -> Texture;

    void setSize(Vector2 size);
    void setTintColor(Vector4 tintColor);
    void setTexture(Texture texture);

private:
    Vector2 m_size{0.0f};
    Vector4 m_tintColor{1.0f};
    Texture m_texture;
};
} // namespace ObsidianEdge
