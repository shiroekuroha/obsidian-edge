#pragma once

#include "core.h"

#include "core/log/log.h"

#define OE_VECTOR_BOILER_PLATE_DEFINE(t, n)                                                   \
    static_assert(std::is_arithmetic_v<t>, "Cannot create vector with non-arithmetic type."); \
    static_assert(n > 0, "Cannot create vector with 0 length");                               \
    constexpr VectorBase(){};                                                                 \
    ~VectorBase() = default;                                                                  \
    constexpr VectorBase(const VectorBase& other) = default;                                  \
    constexpr VectorBase(VectorBase&& other) noexcept = default;                              \
    constexpr auto operator=(const VectorBase& other)->VectorBase& = default;                 \
    constexpr auto operator=(VectorBase&& other) noexcept -> VectorBase& = default;           \
    constexpr VectorBase(const VectorBase<t, n - 1>& minor) {                                 \
        for (unsigned int i = 0; i < n - 1; i++) {                                            \
            this->data[i] = minor.data[i];                                                    \
        }                                                                                     \
    }                                                                                         \
    constexpr VectorBase(t scalar) {                                                          \
        for (unsigned int i = 0; i < n; i++)                                                  \
            this->data[i] = scalar;                                                           \
    }                                                                                         \
    static constexpr auto zero() -> VectorBase {                                              \
        return VectorBase(static_cast<t>(0));                                                 \
    }                                                                                         \
    constexpr auto operator==(const VectorBase& other) const->bool {                          \
        if (this == &other) {                                                                 \
            return true;                                                                      \
        }                                                                                     \
        for (unsigned int i = 0; i < n; i++) {                                                \
            if (this->data[i] != other[i]) {                                                  \
                return false;                                                                 \
            }                                                                                 \
        }                                                                                     \
        return true;                                                                          \
    }                                                                                         \
    constexpr auto operator!=(const VectorBase& other) const->bool {                          \
        if (this == &other) {                                                                 \
            return false;                                                                     \
        }                                                                                     \
        return !(*this == other);                                                             \
    }                                                                                         \
    constexpr auto operator*=(t scalar)->VectorBase& {                                        \
        for (unsigned int i = 0; i < n; i++) {                                                \
            this->data[i] *= scalar;                                                          \
        }                                                                                     \
        return *this;                                                                         \
    }                                                                                         \
    constexpr auto operator/=(t scalar)->VectorBase& {                                        \
        if (scalar == t(0)) {                                                                 \
            OE_CORE_ERROR("Division by zero is not allowed.");                                \
            throw std::runtime_error("Division by zero is not allowed.");                     \
        }                                                                                     \
        for (unsigned int i = 0; i < n; i++) {                                                \
            this->data[i] /= scalar;                                                          \
        }                                                                                     \
        return *this;                                                                         \
    }                                                                                         \
    constexpr auto operator*(t scalar)->VectorBase {                                          \
        VectorBase ret = (*this);                                                             \
        ret *= scalar;                                                                        \
        return ret;                                                                           \
    }                                                                                         \
    constexpr auto operator/(t scalar) const->VectorBase {                                    \
        if (scalar == t(0)) {                                                                 \
            OE_CORE_ERROR("Division by zero is not allowed.");                                \
            throw std::runtime_error("Division by zero is not allowed.");                     \
        }                                                                                     \
        VectorBase ret = (*this);                                                             \
        ret /= scalar;                                                                        \
        return ret;                                                                           \
    }                                                                                         \
    constexpr auto operator+=(const VectorBase& other)->VectorBase& {                         \
        for (unsigned int i = 0; i < n; i++) {                                                \
            this->data[i] += other[i];                                                        \
        }                                                                                     \
        return *this;                                                                         \
    }                                                                                         \
    constexpr auto operator-=(const VectorBase& other)->VectorBase& {                         \
        for (unsigned int i = 0; i < n; i++) {                                                \
            this->data[i] -= other[i];                                                        \
        }                                                                                     \
        return *this;                                                                         \
    }                                                                                         \
    constexpr auto operator+(const VectorBase& other) const->VectorBase {                     \
        VectorBase ret = *this;                                                               \
        ret += other;                                                                         \
        return ret;                                                                           \
    }                                                                                         \
    constexpr auto operator-(const VectorBase& other) const->VectorBase {                     \
        VectorBase ret = *this;                                                               \
        ret -= other;                                                                         \
        return ret;                                                                           \
    }                                                                                         \
    constexpr auto operator-() const->VectorBase {                                            \
        VectorBase ret = *this;                                                               \
        for (unsigned int i = 0; i < n; i++) {                                                \
            ret[i] = -ret[i];                                                                 \
        }                                                                                     \
        return ret;                                                                           \
    }                                                                                         \
    constexpr auto at(unsigned int index) const -> const t& {                                 \
        if (index >= n) {                                                                     \
            OE_CORE_ERROR("Accessing vector's element out of bound.");                        \
            throw std::out_of_range("Accessing vector's element out of bound.");              \
        }                                                                                     \
        return data[index];                                                                   \
    }                                                                                         \
    [[nodiscard]] constexpr auto at(unsigned int index) -> t& {                               \
        if (index >= n) {                                                                     \
            OE_CORE_ERROR("Accessing vector's element out of bound.");                        \
            throw std::out_of_range("Accessing vector's element out of bound.");              \
        }                                                                                     \
        return data[index];                                                                   \
    }                                                                                         \
    constexpr auto operator[](unsigned int index) const->const t& {                           \
        if (index >= n) {                                                                     \
            OE_CORE_ERROR("Accessing vector's element out of bound.");                        \
            throw std::out_of_range("Accessing vector's element out of bound.");              \
        }                                                                                     \
        return data[index];                                                                   \
    }                                                                                         \
    [[nodiscard]] constexpr auto operator[](unsigned int index)->t& {                         \
        if (index >= n) {                                                                     \
            OE_CORE_ERROR("Accessing vector's element out of bound.");                        \
            throw std::out_of_range("Accessing vector's element out of bound.");              \
        }                                                                                     \
        return data[index];                                                                   \
    }

namespace ObsidianEdge {
// NOLINTBEGIN(cppcoreguidelines-pro-bounds-constant-array-index)
// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)
static constexpr auto isHexDigit(char dig) -> bool {
    return (dig >= '0' && dig <= '9') || (dig >= 'a' && dig <= 'f') || (dig >= 'A' && dig <= 'F');
}

static constexpr auto hexValue(char dig) -> unsigned int {
    const unsigned int HEX_LETTER_OFFSET = 10;

    if (dig >= '0' && dig <= '9') {
        return (dig - '0');
    }

    if (dig >= 'A' && dig <= 'F') {
        return (dig - 'A' + HEX_LETTER_OFFSET);
    }

    if (dig >= 'a' && dig <= 'f') {
        return (dig - 'a' + HEX_LETTER_OFFSET);
    }

    return 0;
}

static constexpr auto hexToDec(char digit1, char digit2) -> unsigned int {
    return (hexValue(digit1) << 4) | hexValue(digit2);
}

template <typename T, unsigned int N> struct OE_API VectorBase {
    OE_VECTOR_BOILER_PLATE_DEFINE(T, N)

    T data[N]{}; // NOLINT(cppcoreguidelines-avoid-c-arrays)
};

template <typename T> struct OE_API VectorBase<T, 2> {
    VectorBase(T x, T y) // NOLINT(bugprone-easily-swappable-parameters,
                         // readability-identifier-length)
        : x(x)
        , y(y) {}

    OE_VECTOR_BOILER_PLATE_DEFINE(T, 2)

    union {
        T data[2]{}; // NOLINT(cppcoreguidelines-avoid-c-arrays) ! Intentionally
                     // unsafe.
        struct {
            T x, y;
        };
        struct {
            T u, v;
        };
        struct {
            T col, row;
        };
    };
};

template <> struct OE_API VectorBase<float, 3> {
    static constexpr unsigned int HEX_STR_LEN = 7;

    constexpr VectorBase(float x, float y, float z) // NOLINT(bugprone-easily-swappable-parameters,
                                                    // readability-identifier-length)
        : x(x)
        , y(y)
        , z(z) {}

    OE_VECTOR_BOILER_PLATE_DEFINE(float, 3)

    constexpr VectorBase(const char* hexStr)
        : VectorBase(1.0F) {
        const float RGBA_CHANNEL_MAX = 255.0F;

        if (hexStr[0] == '#') {
            unsigned int seg = 0;

            if (strlen(hexStr) != HEX_STR_LEN) {
                throw std::invalid_argument("Invalid hex string length, expected string length of 7.");
            }

            for (unsigned int i = 1; i < HEX_STR_LEN; i++) {
                if (!isHexDigit(hexStr[i])) {
                    OE_CORE_ERROR("Invalid hex string: unexpected digit "
                                  "#RRGGBBAA(/^#[a-fA-F0-9]{6}$/).");
                    throw std::invalid_argument("Invalid hex string: unexpected digit "
                                                "#RRGGBBAA(/^#[a-fA-F0-9]{6}$/).");
                }
            }

            for (unsigned int i = 1; i < HEX_STR_LEN; i += 2) {
                data[seg++] = static_cast<float>(hexToDec(hexStr[i], hexStr[i + 1])) / RGBA_CHANNEL_MAX;
            }
        } else {
            OE_CORE_ERROR("Invalid hex string: the hex string must begin with an "
                          "octothorpe (#).");
            throw std::invalid_argument("Invalid hex string: the hex string must "
                                        "begin with an octothorpe (#).");
        }
    }

    union {
        float data[3]{}; // NOLINT(cppcoreguidelines-avoid-c-arrays) ! Intentionally
                         // unsafe.
        struct {
            float x, y, z;
        };
        struct {
            float r, g, b;
        };
    };
};

template <typename T> struct OE_API VectorBase<T, 3> {
    constexpr VectorBase(T x, T y, T z) // NOLINT(bugprone-easily-swappable-parameters,
                                        // readability-identifier-length)
        : x(x)
        , y(y)
        , z(z) {}

    OE_VECTOR_BOILER_PLATE_DEFINE(T, 3)

    union {
        T data[3]{}; // NOLINT(cppcoreguidelines-avoid-c-arrays) ! Intentionally
                     // unsafe.
        struct {
            T x, y, z;
        };
        struct {
            T r, g, b;
        };
    };
};

template <> struct OE_API VectorBase<float, 4> {
    static constexpr unsigned int HEX_STR_LEN = 7;
    static constexpr unsigned int HEX_STR_LEN_EX = 9;

    constexpr VectorBase(float x, float y, float z, float w) // NOLINT(bugprone-easily-swappable-parameters,
                                                             // readability-identifier-length)
        : x(x)
        , y(y)
        , z(z)
        , w(w) {}

    OE_VECTOR_BOILER_PLATE_DEFINE(float, 4)

    constexpr VectorBase(const char* hexStr)
        : VectorBase(1.0F) {
        const float RGBA_CHANNEL_MAX = 255.0F;

        if (hexStr[0] == '#') {
            unsigned int seg = 0;
            unsigned int hexStrLen = strlen(hexStr);

            for (unsigned int i = 1; i < hexStrLen; i++) {
                if (!isHexDigit(hexStr[i])) {
                    OE_CORE_ERROR("Invalid hex string: unexpected digit "
                                  "#RRGGBBAA(/^#[a-fA-F0-9]{6}([a-fA-F0-9]{2})?$/).");
                    throw std::invalid_argument("Invalid hex string: unexpected digit "
                                                "#RRGGBBAA(/^#[a-fA-F0-9]{6}([a-fA-F0-9]{2})?$/).");
                }
            }

            switch (hexStrLen) {
            case HEX_STR_LEN:
                for (unsigned int i = 1; i < HEX_STR_LEN; i += 2) {
                    data[seg++] = static_cast<float>(hexToDec(hexStr[i], hexStr[i + 1])) / RGBA_CHANNEL_MAX;
                }
                break;

            case HEX_STR_LEN_EX:
                for (unsigned int i = 1; i < HEX_STR_LEN_EX; i += 2) {
                    data[seg++] = static_cast<float>(hexToDec(hexStr[i], hexStr[i + 1])) / RGBA_CHANNEL_MAX;
                }
                break;
            default:
                OE_CORE_ERROR("Invalid hex string: the hex string must have a length of 7 or 9.");
                throw std::invalid_argument("Invalid hex string: the hex string must have a length of 7 or 9.");
            }
        } else {
            OE_CORE_ERROR("Invalid hex string: the hex string must begin with an "
                          "octothorpe (#).");
            throw std::invalid_argument("Invalid hex string: the hex string must "
                                        "begin with an octothorpe (#).");
        }
    }

    union {
        float data[4]{}; // NOLINT(cppcoreguidelines-avoid-c-arrays) ! Intentionally
                         // unsafe.
        struct {
            float x, y, z, w;
        };
        struct {
            float r, g, b, a;
        };
    };
};

template <typename T> struct OE_API VectorBase<T, 4> {
    constexpr VectorBase(T x, T y, T z, T w) // NOLINT(bugprone-easily-swappable-parameters,
                                             // readability-identifier-length)
        : x(x)
        , y(y)
        , z(z)
        , w(w) {}

    OE_VECTOR_BOILER_PLATE_DEFINE(T, 4)

    union {
        T data[4]{}; // NOLINT(cppcoreguidelines-avoid-c-arrays) ! Intentionally
                     // unsafe.

        struct {
            T x, y, z, w;
        };
        struct {
            T r, g, b, a;
        };
    };
};

template <typename T, unsigned int N> auto dot(const VectorBase<T, N>& src, const VectorBase<T, N>& des) -> T {
    T ret = 0;

    for (unsigned int i = 0; i < N; i++) {
        ret += src[i] * des[i];
    }

    return ret;
}

template <typename T> auto cross(const VectorBase<T, 3>& src, const VectorBase<T, 3>& des) -> VectorBase<T, 3> {
    return Vector(-(src.y * des.z - src.z * des.y), -(src.z * des.x - src.x * des.z), -(src.x * des.y - src.y * des.x));
}

template <typename T> auto lengthSquared(const VectorBase<T, 2>& vec) -> T {
    return (vec.x * vec.x + vec.y * vec.y);
}

template <typename T> auto lengthSquared(const VectorBase<T, 3>& vec) -> T {
    return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

template <typename T> auto lengthSquared(const VectorBase<T, 4>& vec) -> T {
    return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
}

template <typename T> auto length(const VectorBase<T, 2>& vec) -> T {
    return std::sqrt(lengthSquared(vec));
}

template <typename T> auto length(const VectorBase<T, 3>& vec) -> T {
    return std::sqrt(lengthSquared(vec));
}

template <typename T> auto length(const VectorBase<T, 4>& vec) -> T {
    return std::sqrt(lengthSquared(vec));
}

template <typename T, unsigned int N> auto distanceSquared(const VectorBase<T, N>& src, const VectorBase<T, N>& des) -> T {
    return lengthSquared(src - des);
}

template <typename T, unsigned int N> auto distance(const VectorBase<T, N>& src, const VectorBase<T, N>& des) -> T {
    return length(src - des);
}

template <typename T, unsigned int N> auto normalize(const VectorBase<T, N>& vec) -> VectorBase<T, N> {
    if (length(vec) == T(0)) {
        OE_CORE_WARN("Cannot normalize a zero-length vector. Returning 0.");

        return T(0);
    }

    VectorBase<T, N> ret = vec / length(vec);

    return ret;
}

template <typename T, unsigned int N> auto angle(const VectorBase<T, N>& src, const VectorBase<T, N>& des) -> T {
    static_assert(N >= 2 && N <= 3, "Normalize doesn't support vector of size other than 2 or 3.");

    auto lengths = length(src) * length(des);

    if (lengths == T(0)) {
        OE_CORE_WARN("Cannot find angle of a zero-length vector. Returning 0.");

        return T(0);
    }

    auto value = dot(src, des) / lengths;
    value = std::clamp(value, T(-1), T(1));

    return std::acos(value);
}

template <typename T, unsigned int N>
auto project(const VectorBase<T, N>& src, const VectorBase<T, N>& des) -> VectorBase<T, N> {
    T denom = lengthSquared(des);

    if (denom == T(0)) {
        OE_CORE_WARN("Cannot project a zero-length vector. Returning the zero vector.");

        return VectorBase<T, N>::zero();
    }

    auto scale = dot(src, des) / denom;

    return des * scale;
}

template <typename T, unsigned int N> auto toString(const VectorBase<T, N>& vec, bool alt = false) -> std::string {
    std::stringstream sstream;

    // * NOTE: No alternative version yet.

    sstream << "Custom length vector: ";

    for (unsigned int i = 0; i < vec.data.size(); i++) {
        if (i != 0) {
            sstream << ", ";
        }
        sstream << "[" << std::to_string(i) << "]: " << vec.data[i];
    }

    return sstream.str();
}

template <typename T> auto toString(const VectorBase<T, 2>& vec, bool alt = false) -> std::string {
    std::stringstream sstream;

    if (alt) {
        sstream << "u: " << vec.x << ", v: " << vec.y;
    } else {
        sstream << "x: " << vec.x << ", y: " << vec.y;
    }

    return sstream.str();
}

template <typename T> auto toString(const VectorBase<T, 3>& vec, bool alt = false) -> std::string {
    std::stringstream sstream;

    if (alt) {
        sstream << "r: " << vec.x << ", g: " << vec.y << ", b: " << vec.z;
    } else {
        sstream << "x: " << vec.x << ", y: " << vec.y << ", z: " << vec.z;
    }

    return sstream.str();
}

template <typename T> auto toString(const VectorBase<T, 4>& vec, bool alt = false) -> std::string {
    std::stringstream sstream;

    if (alt) {
        sstream << "r: " << vec.x << ", g: " << vec.y << ", b: " << vec.z << ", a: " << vec.w;
    } else {
        sstream << "x: " << vec.x << ", y: " << vec.y << ", z: " << vec.z << ", w: " << vec.w;
    }

    return sstream.str();
}

using Point2 = VectorBase<unsigned int, 2>;
using Vector2 = VectorBase<float, 2>;
using Vector2p = VectorBase<double, 2>;
using Vector2i = VectorBase<int, 2>;

using Point3 = VectorBase<unsigned int, 3>;
using Vector3 = VectorBase<float, 3>;
using Vector3p = VectorBase<double, 3>;
using Vector3i = VectorBase<int, 3>;

using Point4 = VectorBase<unsigned int, 4>;
using Vector4 = VectorBase<float, 4>;
using Vector4p = VectorBase<double, 4>;
using Vector4i = VectorBase<int, 4>;
// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)
// NOLINTEND(cppcoreguidelines-pro-bounds-constant-array-index)
} // namespace ObsidianEdge
