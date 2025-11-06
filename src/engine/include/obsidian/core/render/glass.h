#ifndef OE_GLASS_H
#define OE_GLASS_H

#include "obsidian/core/core.h"

// ! This order matters!
// clang-format off
#include <glad/gl.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "obsidian/core/application.h"
#include "obsidian/core/layer/layer.h"
#include "obsidian/core/render/primitives/generic.h"
#include "obsidian/core/render/primitives/rectangle.h"
#include "obsidian/core/render/primitives/shader.h"

#include "glm/gtc/matrix_transform.hpp"

namespace ObsidianEdge
{
class Glass : public Layer
{
public:
    void onAttach () override;
    void onDetach () override;
    void onUpdate (float delta) override;

    void createBuffer (const Vector<Rectangle> &rects = {});
    void destroyBuffer (unsigned int bufferIndex);

    void drawSegment (unsigned int bufferIndex, unsigned int segmentIndex);
    void drawBuffer (unsigned int bufferIndex);

private:
    Shader shader;
    Vector<unsigned int> vao = {};

    struct Buffer
    {
        Pair<unsigned int, Vector<Vertex>> vbo = {};
        Pair<unsigned int, Vector<Index>> ibo = {};
        Vector<Texture> textures = {};
        Matrix4 transform = { 1.0f };
    };

    Vector<Buffer> buffer = {};

    Matrix4 view = Matrix4 (1.0f);
    Matrix4 proj = Matrix4 (1.0f);
};
}

#endif
