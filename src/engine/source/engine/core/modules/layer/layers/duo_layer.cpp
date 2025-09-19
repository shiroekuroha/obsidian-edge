#include <engine/core/pch.h>

#include "engine/core/modules/layer/layers/duo_layer.h"

namespace ObsidianEdge
{
static unsigned int
compileShader (unsigned int type, std::string &source)
{
    unsigned int id = glCreateShader (type);
    const char *src = source.c_str ();
    glShaderSource (id, 1, &src, nullptr);
    glCompileShader (id);

    int result;
    int length = 0;
    char *message = nullptr;

    glGetShaderiv (id, GL_COMPILE_STATUS, &result);

    switch (result)
        {
        case GL_FALSE:
            glGetShaderiv (id, GL_INFO_LOG_LENGTH, &length);

            message = (char *)alloca (length * sizeof (char));
            glGetShaderInfoLog (id, length, &length, message);

            switch (type)
                {
                case GL_VERTEX_SHADER:
                    OE_CORE_TRACE ("Vertex Shader compile error message: {0}", message)
                    break;

                case GL_FRAGMENT_SHADER:
                    OE_CORE_TRACE ("Fragment Shader compile error message: {0}", message)
                    break;
                }

            OE_CORE_ASSERT ((false), "Failed to compile shader")

            break;

        case GL_TRUE:
            OE_CORE_TRACE ("Shader compiled successful!")
            break;
        }

    return id;
}

static unsigned int
createShader (std::string &vertexSource, std::string &fragmentSource)
{
    unsigned int program = glCreateProgram ();
    unsigned int vs = compileShader (GL_VERTEX_SHADER, vertexSource);
    unsigned int fs = compileShader (GL_FRAGMENT_SHADER, fragmentSource);

    glAttachShader (program, vs);
    glAttachShader (program, fs);
    glLinkProgram (program);
    glValidateProgram (program);

    glDeleteShader (vs);
    glDeleteShader (fs);

    return program;
}

DuoLayer::DuoLayer (const char *name) : Layer ("ImGui")
{
    m_vertexShader = "#version 330\n"
                     "\n"
                     "layout(location=0)in vec4 in_Position;\n"
                     "layout(location=1)in vec4 in_Color;\n"
                     "out vec4 ex_Color;\n"
                     "\n"
                     "void main()\n"
                     "{\n"
                     "    gl_Position = in_Position;\n"
                     "    ex_Color = in_Color;\n"
                     "}\n";

    m_fragmentShader = "#version 330\n"
                       "\n"
                       "in vec4 ex_Color;\n"
                       "out vec4 out_Color;\n "
                       "\n"
                       "void main()\n"
                       "{\n"
                       "    out_Color = ex_Color;\n"
                       "}\n";
}

DuoLayer::~DuoLayer () {}

void
DuoLayer::onAttach ()
{
    m_program = createShader (m_vertexShader, m_fragmentShader);

    glGenVertexArrays (1, &m_vertexArray);
    glBindVertexArray (m_vertexArray);

    glGenBuffers (1, &m_vertexBuffer);
    glBindBuffer (GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData (GL_ARRAY_BUFFER, sizeof (Vertex) * m_data.size (), m_data.data (), GL_STATIC_DRAW);

    glEnableVertexAttribArray (0);
    glVertexAttribPointer (0, 4, GL_FLOAT, GL_FALSE, sizeof (Vertex), (void *)offsetof (Vertex, position));

    glEnableVertexAttribArray (1);
    glVertexAttribPointer (1, 4, GL_FLOAT, GL_FALSE, sizeof (Vertex), (void *)offsetof (Vertex, color));

    glGenBuffers (1, &m_indexBuffer);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER, sizeof (unsigned char) * m_indicies.size (), m_indicies.data (), GL_STATIC_DRAW);
}

void
DuoLayer::onDetach ()
{
}

void
DuoLayer::onUpdate ()
{
}

void
DuoLayer::onEvent (Event &event)
{
}

void
DuoLayer::begin ()
{
}

void
DuoLayer::end ()
{
}

void
DuoLayer::onRender ()
{
    glUseProgram (m_program);

    glBindVertexArray (m_vertexArray);
    // glDrawArrays (GL_TRIANGLE_STRIP, 0, m_data.size ());
    glDrawElements (GL_TRIANGLES, m_indicies.size (), GL_UNSIGNED_BYTE, (GLvoid *)0);
}
}
