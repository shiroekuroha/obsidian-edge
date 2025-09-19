#pragma once

#define GLAD_GL_IMPLEMENTATION
#define GLFW_INCLUDE_NONE

// ! This order matters!
// clang-format off
#include "glad/gl.h"
#include "GLFW/glfw3.h"
// clang-format on

#include "engine/core/application/application.h"
#include "engine/core/modules/layer/layer.h"
#include "engine/core/modules/log/logger.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

typedef struct Vertex
{
    glm::vec4 position;
    glm::vec4 color;
} Vertex;

namespace ObsidianEdge
{
class DuoLayer : public Layer
{
public:
    DuoLayer (const char *name = "Layer");
    virtual ~DuoLayer ();

    void onAttach () override;
    void onDetach () override;
    void onUpdate () override;
    void onEvent (Event &event) override;

    void begin () override;
    void end () override;
    void onRender () override;

private:
    std::string m_vertexShader;
    std::string m_fragmentShader;

    std::vector<Vertex> m_data = { { { 0.0f, 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } },
                                   // Top
                                   { { -0.2f, 0.8f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
                                   { { 0.2f, 0.8f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
                                   { { 0.0f, 0.8f, 0.0f, 1.0f }, { 0.0f, 1.0f, 1.0f, 1.0f } },
                                   { { 0.0f, 1.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
                                   // Bottom
                                   { { -0.2f, -0.8f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
                                   { { 0.2f, -0.8f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
                                   { { 0.0f, -0.8f, 0.0f, 1.0f }, { 0.0f, 1.0f, 1.0f, 1.0f } },
                                   { { 0.0f, -1.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
                                   // Left
                                   { { -0.8f, -0.2f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
                                   { { -0.8f, 0.2f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
                                   { { -0.8f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 1.0f, 1.0f } },
                                   { { -1.0f, 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
                                   // Right
                                   { { 0.8f, -0.2f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
                                   { { 0.8f, 0.2f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
                                   { { 0.8f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 1.0f, 1.0f } },
                                   { { 1.0f, 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } } };

    std::vector<unsigned char> m_indicies = { 0, 1, 3, 0, 3, 2, 3, 1, 4, 3, 4, 2,
                                              // Bottom
                                              0, 5, 7, 0, 7, 6, 7, 5, 8, 7, 8, 6,
                                              // Left
                                              0, 9, 11, 0, 11, 10, 11, 9, 12, 11, 12, 10,
                                              // Right
                                              0, 13, 15, 0, 15, 14, 15, 13, 16, 15, 16, 14 };

    unsigned int m_program;
    unsigned int m_indexBuffer;
    unsigned int m_vertexArray;
    unsigned int m_vertexBuffer;
};
}
