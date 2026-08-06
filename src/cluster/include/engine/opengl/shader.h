#pragma once

#include "core.h"

#include "engine/base/shader.h"

// ! This order matters!
// clang-format off
#include <glad/gl.h>
#include <GLFW/glfw3.h>
// clang-format on

namespace ObsidianEdge {
using OpenGLShaderID = uint32_t;

class OE_API OpenGLShader : public Shader {
public:
    OpenGLShader();
    OpenGLShader(const char* vPath, const char* fPath);
    virtual ~OpenGLShader() = default;

    OpenGLShader(const OpenGLShader&) = default;
    OpenGLShader(OpenGLShader&&) noexcept = default;

    auto operator=(const OpenGLShader&) -> OpenGLShader& = default;
    auto operator=(OpenGLShader&&) noexcept -> OpenGLShader& = default;

    [[nodiscard]] inline auto id() const -> unsigned int {
        return m_id;
    }

    void init(const char* vPath = nullptr, const char* fPath = nullptr);
    void init() override;
    void yeet() override;

    void use() override;

    void setUniform1f(const char* name, float value);
    void setUniform2f(const char* name, const Vector2& value);
    void setUniform3f(const char* name, const Vector3& value);
    void setUniform4f(const char* name, const Vector4& value);

    void setUniform1i(const char* name, int value);
    void setUniform2i(const char* name, const Vector2i& value);
    void setUniform3i(const char* name, const Vector3i& value);
    void setUniform4i(const char* name, const Vector4i& value);

    void setUniform1ui(const char* name, unsigned int value);
    void setUniform2ui(const char* name, const Point2& value);
    void setUniform3ui(const char* name, const Point3& value);
    void setUniform4ui(const char* name, const Point4& value);

    void setUniformMatrix2(const char* name, bool transpose, const Matrix2& value);
    void setUniformMatrix3(const char* name, bool transpose, const Matrix3& value);
    void setUniformMatrix4(const char* name, bool transpose, const Matrix4& value);

    void setUniformMatrix2x3(const char* name, bool transpose, const MatrixBase<float, 2, 3>& value);
    void setUniformMatrix3x2(const char* name, bool transpose, const MatrixBase<float, 3, 2>& value);
    void setUniformMatrix2x4(const char* name, bool transpose, const MatrixBase<float, 2, 4>& value);
    void setUniformMatrix4x2(const char* name, bool transpose, const MatrixBase<float, 4, 2>& value);
    void setUniformMatrix3x4(const char* name, bool transpose, const MatrixBase<float, 3, 4>& value);
    void setUniformMatrix4x3(const char* name, bool transpose, const MatrixBase<float, 4, 3>& value);

protected:
    static void loadSource(const char* vPath, const char* fPath, std::string& vSource, std::string& fSource);

private:
    OpenGLShaderID m_id = 0;
};
} // namespace ObsidianEdge
