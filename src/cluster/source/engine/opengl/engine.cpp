#include <pch.h>

#include "engine/opengl/engine.h"
#include "engine/opengl/shader.h"

namespace ObsidianEdge {
void OpenGLEngine::uploadRenderData(const std::vector<RenderObjData>& renderObjData) {
    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    for (const RenderObjData& obj : renderObjData) {
        auto it = m_renderData.find(obj.owner);

        if (it != m_renderData.end()) {
            glDeleteVertexArrays(1, &it->second.vao);
            glDeleteBuffers(1, &it->second.ebo);
            glDeleteBuffers(1, &it->second.vbo);
            it->second.texture.yeet();
        }

        unsigned int vao = 0;
        unsigned int vbo = 0;
        unsigned int ebo = 0;

        auto& data = obj.mesh.getData();
        auto& mat = obj.material.getData();

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * data.vertices.size(), data.vertices.data(), GL_STATIC_DRAW);

        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Index) * data.indices.size(), data.indices.data(), GL_STATIC_DRAW);

        OpenGLTexture texture;

        texture.setTextureHandler(obj.material.getData().albedo);

        texture.uWrapMode = WrapMode::ClampToEdge;
        texture.vWrapMode = WrapMode::ClampToEdge;
        texture.genMipmap = true;

        texture.init();

        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);

        m_renderData[obj.owner] = {vao, vbo, ebo, texture, obj.mesh, obj.material};
    }
}

void OpenGLEngine::init() {
    shader = std::make_shared<OpenGLShader>();
    shader->init();
}

void OpenGLEngine::yeet() {}

void OpenGLEngine::update(double delta) {
    glClearColor(0.2F, 0.2F, 0.2F, 1.0F);
    glClear(GL_COLOR_BUFFER_BIT);

    for (auto& [nodeId, renderData] : m_renderData) {
        shader->use();

        dynamic_cast<OpenGLShader&>(*shader).setUniform1i("g_Sampler", 0);
        dynamic_cast<OpenGLShader&>(*shader).setUniform4f("g_TintColor", Vector4(1.0f, 1.0f, 0.0f, 1.0f));

        renderData.texture.use();

        glBindVertexArray(renderData.vao);

        glDrawElements(GL_TRIANGLES, (renderData.mesh.getData().indices.size()), GL_UNSIGNED_INT, nullptr);
    }
}
} // namespace ObsidianEdge
