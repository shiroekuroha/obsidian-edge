#include <obsidian/core/data/pch.h>

#include "obsidian/core/render/primitives/shader.h"

namespace ObsidianEdge
{

static void
handleShaderError (unsigned int id, GLenum status)
{
    int result = 0;
    int length = 0;
    char *message = nullptr;

    glGetShaderiv (id, status, &result);

    if (!result)
        {
            glGetShaderiv (id, GL_INFO_LOG_LENGTH, &length);

            message = static_cast<char *> (alloca (length * sizeof (char)));
            glGetShaderInfoLog (id, length, &length, message);

            OE_CORE_ASSERT (false, message)
        }
}

static void
handleProgramError (unsigned int id, GLenum status)
{
    int result = 0;
    int length = 0;
    char *message = nullptr;

    glGetProgramiv (id, status, &result);

    if (!result)
        {
            glGetProgramiv (id, GL_INFO_LOG_LENGTH, &length);

            message = static_cast<char *> (alloca (length * sizeof (char)));
            glGetProgramInfoLog (id, length, &length, message);

            OE_CORE_ASSERT (false, message)
        }
}

static auto
compileShader (unsigned int type, std::string &source) -> unsigned int
{
    unsigned int id = glCreateShader (type);
    const char *src = source.c_str ();
    glShaderSource (id, 1, &src, nullptr);
    glCompileShader (id);

    handleShaderError (id, GL_COMPILE_STATUS);

    return id;
}

static auto
createShader (std::string &vertexSource, std::string &fragmentSource) -> unsigned int
{
    unsigned int program = glCreateProgram ();
    unsigned int vs = compileShader (GL_VERTEX_SHADER, vertexSource);
    unsigned int fs = compileShader (GL_FRAGMENT_SHADER, fragmentSource);

    glAttachShader (program, vs);
    glAttachShader (program, fs);
    glLinkProgram (program);
    glValidateProgram (program);

    handleProgramError (program, GL_VALIDATE_STATUS);

    glUseProgram (program);

    glDeleteShader (vs);
    glDeleteShader (fs);

    handleShaderError (vs, GL_DELETE_STATUS);
    handleShaderError (fs, GL_DELETE_STATUS);

    return program;
}

Shader::Shader (const char *vPath, const char *fPath) { create (vPath, fPath); }

void
Shader::create (const char *vPath, const char *fPath)
{
    if (m_id)
        destroy ();

    loadSource (vPath, fPath);

    m_id = ::ObsidianEdge::createShader (m_vertexSource, m_fragmentSource);
}

void
Shader::destroy ()
{
    glDeleteProgram (m_id);
    handleProgramError (m_id, GL_DELETE_STATUS);

    m_vertexSource.clear ();
    m_fragmentSource.clear ();
}

void
Shader::loadSource (const char *vPath, const char *fPath)
{
    std::fstream vp (vPath, std::ios::in);
    std::fstream fp (fPath, std::ios::in);

    OE_CORE_ASSERT (vp, "Error reading vertex shader file!")
    OE_CORE_ASSERT (fp, "Error reading fragment shader file!")

    std::string vb ((std::istreambuf_iterator<char> (vp)), (std::istreambuf_iterator<char> ()));
    std::string fb ((std::istreambuf_iterator<char> (fp)), (std::istreambuf_iterator<char> ()));

    m_vertexSource = vb;
    m_fragmentSource = fb;
}
}
