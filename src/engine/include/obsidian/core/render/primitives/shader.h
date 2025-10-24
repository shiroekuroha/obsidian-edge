#ifndef OE_SHADER_H
#define OE_SHADER_H

// ! This order matters!
// clang-format off
#include "glad/gl.h"
#include "GLFW/glfw3.h"
// clang-format on

#include "obsidian/core/core.h"
#include "obsidian/core/log/log.h"

namespace ObsidianEdge
{
class Shader
{
public:
    Shader (const char *vPath, const char *fPath);

    Shader () = default;
    ~Shader () = default;

    Shader (const Shader &other) = default;
    Shader (Shader &&other) noexcept = delete;

    auto operator= (const Shader &other) -> Shader & = default;
    auto operator= (Shader &&other) noexcept -> Shader & = delete;

    void create (const char *vPath, const char *fPath);
    void destroy ();

    [[nodiscard]] inline auto
    id () const -> unsigned int
    {
        return m_id;
    }

    inline void
    use () const
    {
        glUseProgram (m_id);
    }

protected:
    void loadSource (const char *vPath, const char *fPath);

private:
    std::string m_vertexSource;
    std::string m_fragmentSource;

    unsigned int m_id = 0;
};
}

#endif
