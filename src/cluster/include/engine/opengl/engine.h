#pragma once

#include "core.h"

#include "engine/base/engine.h"
#include "engine/base/shader.h"

#include "engine/opengl/shader.h"
#include "engine/opengl/texture.h"

// ! This order matters!
// clang-format off
#include <glad/gl.h>
#include <GLFW/glfw3.h>
// clang-format on

namespace ObsidianEdge {
using OpenGLEngineRenderData = struct OpenGLEngineRenderData {
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;

    OpenGLTexture texture;

    MeshHandler mesh;
    MaterialHandler material;
};

class OE_API OpenGLEngine : public RenderEngine {
public:
    OpenGLEngine() = default;
    virtual ~OpenGLEngine() = default;

    OpenGLEngine(const OpenGLEngine &other) = default;
    OpenGLEngine(OpenGLEngine &&other) noexcept = default;

    auto operator=(const OpenGLEngine &other) -> OpenGLEngine & = default;
    auto operator=(OpenGLEngine &&other) noexcept -> OpenGLEngine & = default;

    void uploadRenderData(const std::vector<RenderObjData> &renderObjData) override;

    void init() override;
    void yeet() override;

    void update(double delta) override;

private:
    std::shared_ptr<Shader> shader;
    std::unordered_map<NodeID, OpenGLEngineRenderData> m_renderData;
};
} // namespace ObsidianEdge
