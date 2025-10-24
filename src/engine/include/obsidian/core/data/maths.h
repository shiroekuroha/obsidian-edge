#ifndef OE_MATHS_H
#define OE_MATHS_H

#include "glm/matrix.hpp"

namespace ObsidianEdge
{
using Vector2 = glm::vec2;
using Vector2i = glm::ivec2;
using Vector3 = glm::vec3;
using Vector3i = glm::ivec3;
using Vector4 = glm::vec4;
using Vector4i = glm::ivec4;

using Matrix2 = glm::mat2x2;
using Matrix2x3 = glm::mat2x3;
using Matrix2x4 = glm::mat2x4;
using Matrix2 = glm::mat2;

using Matrix3x2 = glm::mat3x2;
using Matrix3 = glm::mat3x3;
using Matrix3x4 = glm::mat3x4;
using Matrix3 = glm::mat3;

using Matrix4x2 = glm::mat4x2;
using Matrix4x3 = glm::mat4x3;
using Matrix4x4 = glm::mat4x4;
using Matrix4 = glm::mat4;
}

#endif
