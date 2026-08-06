#include <pch.h>

#include "engine/opengl/shader.h"

#include "core/log/log.h"
#include "engine/opengl/glsl/fragment.glsl.h"
#include "engine/opengl/glsl/vertex.glsl.h"

namespace ObsidianEdge {

static void handleShaderError(unsigned int id, GLenum status) {
    int result = 0;
    int length = 0;

    glGetShaderiv(id, status, &result);

    if (!result) {
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        OE_CORE_WARN("Shader compilation {0} have unexpected result.", status)

        if (length > 0) {
            std::vector<char> message(length + 1, '\0');

            glGetShaderInfoLog(id, length, nullptr, message.data());

            std::string error(message.data());
            OE_CORE_ASSERT(false, error.c_str());
        }
    }
}

static void handleProgramError(unsigned int id, GLenum status) {
    int result = 0;
    int length = 0;

    glGetProgramiv(id, status, &result);

    if (!result) {
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);

        OE_CORE_WARN("Program compilation {0} have unexpected result.", status)

        if (length > 0) {
            std::vector<char> message(length + 1, '\0');

            glGetProgramInfoLog(id, length, nullptr, message.data());

            std::string error(message.data());
            OE_CORE_ASSERT(false, error.c_str());
        }
    }
}

static auto compileShader(unsigned int type, const char* source) -> unsigned int {
    unsigned int id = glCreateShader(type);
    const char* src = source;
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    handleShaderError(id, GL_COMPILE_STATUS);

    return id;
}

static auto createProgram(const char* vertexSource, const char* fragmentSource) -> unsigned int {
    unsigned int program = glCreateProgram();

    unsigned int vShader = compileShader(GL_VERTEX_SHADER, vertexSource);
    unsigned int fShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

    glAttachShader(program, vShader);
    glAttachShader(program, fShader);

    glLinkProgram(program);
    handleProgramError(program, GL_LINK_STATUS);

    glValidateProgram(program);
    handleProgramError(program, GL_VALIDATE_STATUS);

    glUseProgram(program);

    glDeleteShader(vShader);
    glDeleteShader(fShader);

    handleShaderError(vShader, GL_DELETE_STATUS);
    handleShaderError(fShader, GL_DELETE_STATUS);

    return program;
}

OpenGLShader::OpenGLShader()
    : m_id(::ObsidianEdge::createProgram(s_default_vertex_shader, s_default_fragment_shader)) {}

void OpenGLShader::init(const char* vPath, const char* fPath) {
    if (m_id) {
        yeet();
    }

    std::string vSource;
    std::string fSource;

    if (vPath == nullptr || fPath == nullptr) {
        vSource = s_default_vertex_shader;
        fSource = s_default_fragment_shader;
    } else {
        loadSource(vPath, fPath, vSource, fSource);
    }

    m_id = ::ObsidianEdge::createProgram(vSource.c_str(), fSource.c_str());
}

void OpenGLShader::init() {
    init(nullptr, nullptr);
}

void OpenGLShader::yeet() {
    glDeleteProgram(m_id);
    handleProgramError(m_id, GL_DELETE_STATUS);
}

void OpenGLShader::loadSource(const char* vPath, const char* fPath, std ::string& vSource, std::string& fSource) {
    std::fstream vFile(vPath, std::ios::in);
    std::fstream fFile(fPath, std::ios::in);

    OE_CORE_ASSERT(vFile, "Error reading vertex shader file!")
    OE_CORE_ASSERT(fFile, "Error reading fragment shader file!")

    std::string vString((std::istreambuf_iterator<char>(vFile)), (std::istreambuf_iterator<char>()));
    std::string fString((std::istreambuf_iterator<char>(fFile)), (std::istreambuf_iterator<char>()));

    vSource = vString;
    fSource = fString;
}

void OpenGLShader::use() {
    glUseProgram(m_id);
}

void OpenGLShader::setUniform1f(const char* name, float value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniform1f(location, value);
}

void OpenGLShader::setUniform2f(const char* name, const Vector2& value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniform2fv(location, 2, value.data);
}

void OpenGLShader::setUniform3f(const char* name, const Vector3& value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniform3fv(location, 3, value.data);
}

void OpenGLShader::setUniform4f(const char* name, const Vector4& value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniform4f(location, value.x, value.y, value.z, value.w);
}

void OpenGLShader::setUniform1i(const char* name, int value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniform1i(location, value);
}

void OpenGLShader::setUniform2i(const char* name, const Vector2i& value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniform2iv(location, 2, value.data);
}

void OpenGLShader::setUniform3i(const char* name, const Vector3i& value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniform3iv(location, 3, value.data);
}

void OpenGLShader::setUniform4i(const char* name, const Vector4i& value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniform4iv(location, 4, value.data);
}

void OpenGLShader::setUniform1ui(const char* name, unsigned int value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniform1ui(location, value);
}

void OpenGLShader::setUniform2ui(const char* name, const Point2& value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniform2uiv(location, 2, value.data);
}

void OpenGLShader::setUniform3ui(const char* name, const Point3& value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniform3uiv(location, 3, value.data);
}

void OpenGLShader::setUniform4ui(const char* name, const Point4& value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniform4uiv(location, 4, value.data);
}

void OpenGLShader::setUniformMatrix2(const char* name, bool transpose, const Matrix2& value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniformMatrix2fv(location, 4, static_cast<GLboolean>(transpose), value.getTrueArray().data());
}

void OpenGLShader::setUniformMatrix3(const char* name, bool transpose, const Matrix3& value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniformMatrix3fv(location, 9, static_cast<GLboolean>(transpose), value.getTrueArray().data());
}

void OpenGLShader::setUniformMatrix4(const char* name, bool transpose, const Matrix4& value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniformMatrix4fv(location, 16, static_cast<GLboolean>(transpose), value.getTrueArray().data());
}

void OpenGLShader::setUniformMatrix2x3(const char* name, bool transpose, const MatrixBase<float, 2, 3>& value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniformMatrix2x3fv(location, 6, static_cast<GLboolean>(transpose), value.getTrueArray().data());
}

void OpenGLShader::setUniformMatrix3x2(const char* name, bool transpose, const MatrixBase<float, 3, 2>& value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniformMatrix3x2fv(location, 6, static_cast<GLboolean>(transpose), value.getTrueArray().data());
}

void OpenGLShader::setUniformMatrix2x4(const char* name, bool transpose, const MatrixBase<float, 2, 4>& value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniformMatrix2x4fv(location, 8, static_cast<GLboolean>(transpose), value.getTrueArray().data());
}

void OpenGLShader::setUniformMatrix4x2(const char* name, bool transpose, const MatrixBase<float, 4, 2>& value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniformMatrix4x2fv(location, 8, static_cast<GLboolean>(transpose), value.getTrueArray().data());
}

void OpenGLShader::setUniformMatrix3x4(const char* name, bool transpose, const MatrixBase<float, 3, 4>& value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniformMatrix3x4fv(location, 12, static_cast<GLboolean>(transpose), value.getTrueArray().data());
}

void OpenGLShader::setUniformMatrix4x3(const char* name, bool transpose, const MatrixBase<float, 4, 3>& value) {
    use();
    int location = glGetUniformLocation(m_id, name);
    glUniformMatrix4x3fv(location, 12, static_cast<GLboolean>(transpose), value.getTrueArray().data());
}
} // namespace ObsidianEdge
