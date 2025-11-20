#pragma once

namespace ObsidianEdge {
class Shader {
public:
    Shader(const char *vPath, const char *fPath);

    Shader() = default;
    ~Shader() = default;

    Shader(const Shader &other) = default;
    Shader(Shader &&other) noexcept = delete;

    auto operator=(const Shader &other) -> Shader & = default;
    auto operator=(Shader &&other) noexcept -> Shader & = delete;

    void create(const char *vPath, const char *fPath);
    void destroy();

    [[nodiscard]] inline auto id() const -> unsigned int { return m_id; }

    void use() const;

    void setUniform1f(const char *name, float v0);
    void setUniform2f(const char *name, float v0, float v1);
    void setUniform3f(const char *name, float v0, float v1, float v2);
    void setUniform4f(const char *name, float v0, float v1, float v2, float v3);
    void setUniform1i(const char *name, int v0);
    void setUniform2i(const char *name, int v0, int v1);
    void setUniform3i(const char *name, int v0, int v1, int v2);
    void setUniform4i(const char *name, int v0, int v1, int v2, int v3);
    void setUniform1ui(const char *name, unsigned int v0);
    void setUniform2ui(const char *name, unsigned int v0, unsigned int v1);
    void setUniform3ui(const char *name, unsigned int v0, unsigned int v1, unsigned int v2);
    void setUniform4ui(const char *name, unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3);
    void setUniform1fv(const char *name, int count, const float *value);
    void setUniform2fv(const char *name, int count, const float *value);
    void setUniform3fv(const char *name, int count, const float *value);
    void setUniform4fv(const char *name, int count, const float *value);
    void setUniform1iv(const char *name, int count, const int *value);
    void setUniform2iv(const char *name, int count, const int *value);
    void setUniform3iv(const char *name, int count, const int *value);
    void setUniform4iv(const char *name, int count, const int *value);
    void setUniform1uiv(const char *name, int count, const unsigned int *value);
    void setUniform2uiv(const char *name, int count, const unsigned int *value);
    void setUniform3uiv(const char *name, int count, const unsigned int *value);
    void setUniform4uiv(const char *name, int count, const unsigned int *value);
    void setUniformMatrix2fv(const char *name, int count, bool transpose, const float *value);
    void setUniformMatrix3fv(const char *name, int count, bool transpose, const float *value);
    void setUniformMatrix4fv(const char *name, int count, bool transpose, const float *value);
    void setUniformMatrix2x3fv(const char *name, int count, bool transpose, const float *value);
    void setUniformMatrix3x2fv(const char *name, int count, bool transpose, const float *value);
    void setUniformMatrix2x4fv(const char *name, int count, bool transpose, const float *value);
    void setUniformMatrix4x2fv(const char *name, int count, bool transpose, const float *value);
    void setUniformMatrix3x4fv(const char *name, int count, bool transpose, const float *value);
    void setUniformMatrix4x3fv(const char *name, int count, bool transpose, const float *value);

protected:
    void loadSource(const char *vPath, const char *fPath);

private:
    std::string m_vertexSource;
    std::string m_fragmentSource;

    unsigned int m_id = 0;
};
} // namespace ObsidianEdge
