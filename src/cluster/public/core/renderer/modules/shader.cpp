#include <pch.h>

#include "shader.h"

// ! This order matters!
// clang-format off
#include <glad/gl.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "core/log/log.h"

namespace ObsidianEdge {

static void handleShaderError(unsigned int id, GLenum status) {
    int result = 0;
    int length = 0;
    char *message = nullptr;

    glGetShaderiv(id, status, &result);

    if (!result) {
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        message = static_cast<char *>(alloca(length * sizeof(char)));
        glGetShaderInfoLog(id, length, &length, message);

        OE_CORE_ASSERT(false, message)
    }
}

static void handleProgramError(unsigned int id, GLenum status) {
    int result = 0;
    int length = 0;
    char *message = nullptr;

    glGetProgramiv(id, status, &result);

    if (!result) {
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);

        message = static_cast<char *>(alloca(length * sizeof(char)));
        glGetProgramInfoLog(id, length, &length, message);

        OE_CORE_ASSERT(false, message)
    }
}

static auto compileShader(unsigned int type, std::string &source) -> unsigned int {
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    handleShaderError(id, GL_COMPILE_STATUS);

    return id;
}

static auto createShader(std::string &vertexSource, std::string &fragmentSource) -> unsigned int {
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexSource);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    handleProgramError(program, GL_VALIDATE_STATUS);

    glUseProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    handleShaderError(vs, GL_DELETE_STATUS);
    handleShaderError(fs, GL_DELETE_STATUS);

    return program;
}

Shader::Shader(const char *vPath, const char *fPath) { create(vPath, fPath); }

void Shader::create(const char *vPath, const char *fPath) {
    if (m_id)
        destroy();

    loadSource(vPath, fPath);

    m_id = ::ObsidianEdge::createShader(m_vertexSource, m_fragmentSource);
}

void Shader::destroy() {
    glDeleteProgram(m_id);
    handleProgramError(m_id, GL_DELETE_STATUS);

    m_vertexSource.clear();
    m_fragmentSource.clear();
}

void Shader::loadSource(const char *vPath, const char *fPath) {
    std::fstream vp(vPath, std::ios::in);
    std::fstream fp(fPath, std::ios::in);

    OE_CORE_ASSERT(vp, "Error reading vertex shader file!")
    OE_CORE_ASSERT(fp, "Error reading fragment shader file!")

    std::string vb((std::istreambuf_iterator<char>(vp)), (std::istreambuf_iterator<char>()));
    std::string fb((std::istreambuf_iterator<char>(fp)), (std::istreambuf_iterator<char>()));

    m_vertexSource = vb;
    m_fragmentSource = fb;
}

void Shader::use() const { glUseProgram(m_id); }

void Shader::setUniform1f(const char *name, float v0) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniform1f(location, v0);
}

void Shader::setUniform2f(const char *name, float v0, float v1) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniform2f(location, v0, v1);
}

void Shader::setUniform3f(const char *name, float v0, float v1, float v2) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniform3f(location, v0, v1, v2);
}

void Shader::setUniform4f(const char *name, float v0, float v1, float v2, float v3) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniform4f(location, v0, v1, v2, v3);
}

void Shader::setUniform1i(const char *name, int v0) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniform1i(location, v0);
}

void Shader::setUniform2i(const char *name, int v0, int v1) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniform2i(location, v0, v1);
}

void Shader::setUniform3i(const char *name, int v0, int v1, int v2) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniform3i(location, v0, v1, v2);
}

void Shader::setUniform4i(const char *name, int v0, int v1, int v2, int v3) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniform4i(location, v0, v1, v2, v3);
}

void Shader::setUniform1ui(const char *name, unsigned int v0) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniform1ui(location, v0);
}

void Shader::setUniform2ui(const char *name, unsigned int v0, unsigned int v1) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniform2ui(location, v0, v1);
}

void Shader::setUniform3ui(const char *name, unsigned int v0, unsigned int v1, unsigned int v2) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniform3ui(location, v0, v1, v2);
}

void Shader::setUniform4ui(const char *name, unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniform4ui(location, v0, v1, v2, v3);
}

void Shader::setUniform1fv(const char *name, int count, const float *value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniform1fv(location, count, value);
}

void Shader::setUniform2fv(const char *name, int count, const float *value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniform2fv(location, count, value);
}

void Shader::setUniform3fv(const char *name, int count, const float *value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniform3fv(location, count, value);
}

void Shader::setUniform4fv(const char *name, int count, const float *value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniform4fv(location, count, value);
}

void Shader::setUniform1iv(const char *name, int count, const int *value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniform1iv(location, count, value);
}

void Shader::setUniform2iv(const char *name, int count, const int *value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniform2iv(location, count, value);
}

void Shader::setUniform3iv(const char *name, int count, const int *value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniform3iv(location, count, value);
}

void Shader::setUniform4iv(const char *name, int count, const int *value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniform4iv(location, count, value);
}

void Shader::setUniform1uiv(const char *name, int count, const unsigned int *value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniform1uiv(location, count, value);
}

void Shader::setUniform2uiv(const char *name, int count, const unsigned int *value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniform2uiv(location, count, value);
}

void Shader::setUniform3uiv(const char *name, int count, const unsigned int *value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniform3uiv(location, count, value);
}

void Shader::setUniform4uiv(const char *name, int count, const unsigned int *value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniform4uiv(location, count, value);
}

void Shader::setUniformMatrix2fv(const char *name, int count, bool transpose, const float *value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniformMatrix2fv(location, count, transpose, value);
}

void Shader::setUniformMatrix3fv(const char *name, int count, bool transpose, const float *value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniformMatrix3fv(location, count, transpose, value);
}

void Shader::setUniformMatrix4fv(const char *name, int count, bool transpose, const float *value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniformMatrix4fv(location, count, transpose, value);
}

void Shader::setUniformMatrix2x3fv(const char *name, int count, bool transpose, const float *value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniformMatrix2x3fv(location, count, transpose, value);
}

void Shader::setUniformMatrix3x2fv(const char *name, int count, bool transpose, const float *value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniformMatrix3x2fv(location, count, transpose, value);
}

void Shader::setUniformMatrix2x4fv(const char *name, int count, bool transpose, const float *value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniformMatrix2x4fv(location, count, transpose, value);
}

void Shader::setUniformMatrix4x2fv(const char *name, int count, bool transpose, const float *value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniformMatrix4x2fv(location, count, transpose, value);
}

void Shader::setUniformMatrix3x4fv(const char *name, int count, bool transpose, const float *value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniformMatrix3x4fv(location, count, transpose, value);
}

void Shader::setUniformMatrix4x3fv(const char *name, int count, bool transpose, const float *value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniformMatrix4x3fv(location, count, transpose, value);
}

} // namespace ObsidianEdge
