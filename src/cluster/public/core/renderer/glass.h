#pragma once

#include "core/renderer/ecs/root.h"
#include "core/renderer/modules/generic.h"
#include "core/renderer/modules/shader.h"
#include "core/renderer/render_engine.h"

#define DEFAULT_BG {0.25f, 0.25f, 0.25f, 1.0f}

namespace ObsidianEdge {
struct RenderObject {
    QuadData data;

    unsigned int vao = 0;
    unsigned int vbo = 0;
    unsigned int ibo = 0;
};

class Glass : public RenderEngine {
public:
    Glass();
    ~Glass() override;

    Glass(const Glass &other) = delete;
    Glass(Glass &&other) noexcept = delete;

    auto operator=(const Glass &other) -> Glass & = delete;
    auto operator=(Glass &&other) noexcept -> Glass & = delete;

    void onUpdate(float delta) override;
    void onEvent(Event &event) override;

    void init();
    void yeet();

    void createBuffers();
    void destroyBuffers();

    void draw();
    void reload() override;
    [[nodiscard]] auto isHovered(Entity &entity, std::vector<Entity *> ignoreList = {}) -> bool override;

private:
    Shader shader;

    Matrix4 view = Matrix4(1.0f);
    Matrix4 proj = Matrix4(1.0f);

    Vector4 bg = DEFAULT_BG;

    unsigned int m_vao = 0;
    std::vector<RenderObject> m_renderObjects = {};
    Vector2 m_lastMousePosition{0.0f};
};
} // namespace ObsidianEdge
