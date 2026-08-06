#pragma once

#define OE_VECTOR_VEC_3_HEX_STR_LEN 7
#define OE_VECTOR_VEC_4_HEX_STR_LEN 9

#define OE_VECTOR_BOILER_PLATE_DEFINE(t, n)                                         \
    constexpr VectorBase() {}                                                       \
    constexpr VectorBase(const VectorBase& other) = default;                        \
    constexpr VectorBase(VectorBase&& other) noexcept = default;                    \
    constexpr auto operator=(const VectorBase& other)->VectorBase& = default;       \
    constexpr auto operator=(VectorBase&& other) noexcept -> VectorBase& = default; \
    constexpr VectorBase(t scalar) {                                                \
        for (unsigned int i = 0; i < n; i++)                                        \
            this->data[i] = scalar;                                                 \
    }                                                                               \
    static constexpr auto ZERO() -> VectorBase {                                    \
        return VectorBase(static_cast<t>(0));                                       \
    }                                                                               \
    constexpr auto operator==(const VectorBase& other) const->bool {                \
        for (unsigned int i = 0; i < n; i++) {                                      \
            if (this->data[i] != other[i])                                          \
                return false;                                                       \
        }                                                                           \
        return true;                                                                \
    }                                                                               \
    constexpr auto operator!=(const VectorBase& other) const->bool {                \
        return !((*this) == other);                                                 \
    }                                                                               \
    constexpr auto operator*=(t scalar)->VectorBase& {                              \
        for (unsigned int i = 0; i < n; i++)                                        \
            this->data[i] *= scalar;                                                \
        return *this;                                                               \
    }                                                                               \
    constexpr auto operator/=(t scalar)->VectorBase& {                              \
        for (unsigned int i = 0; i < n; i++)                                        \
            this->data[i] /= scalar;                                                \
        return *this;                                                               \
    }                                                                               \
    constexpr auto operator*(t scalar)->VectorBase {                                \
        VectorBase ret = (*this);                                                   \
        ret *= scalar;                                                              \
        return ret;                                                                 \
    }                                                                               \
    constexpr auto operator/(t scalar)->VectorBase {                                \
        VectorBase ret = (*this);                                                   \
        ret /= scalar;                                                              \
        return ret;                                                                 \
    }                                                                               \
    constexpr auto operator+=(const VectorBase& other)->VectorBase& {               \
        for (unsigned int i = 0; i < n; i++)                                        \
            this->data[i] += other[i];                                              \
        return *this;                                                               \
    }                                                                               \
    constexpr auto operator-=(const VectorBase& other)->VectorBase& {               \
        for (unsigned int i = 0; i < n; i++)                                        \
            this->data[i] -= other[i];                                              \
        return *this;                                                               \
    }                                                                               \
    constexpr auto operator+(const VectorBase& other) const->VectorBase {           \
        VectorBase ret = *this;                                                     \
        ret += other;                                                               \
        return ret;                                                                 \
    }                                                                               \
    constexpr auto operator-(const VectorBase& other) const->VectorBase {           \
        VectorBase ret = *this;                                                     \
        ret -= other;                                                               \
        return ret;                                                                 \
    }                                                                               \
    constexpr auto operator-() const->VectorBase {                                  \
        VectorBase ret = *this;                                                     \
        for (unsigned int i = 0; i < n; i++)                                        \
            ret[i] = -ret[i];                                                       \
        return ret;                                                                 \
    }                                                                               \
    constexpr auto operator[](const unsigned int index) const->const t& {           \
        return data[index];                                                         \
    }                                                                               \
    constexpr auto operator[](const unsigned int index)->t& {                       \
        return data[index];                                                         \
    }

namespace ObsidianEdge {
constexpr auto hexValue(char c) -> unsigned int {
    return (c >= '0' && c <= '9')   ? (c - '0')
           : (c >= 'A' && c <= 'F') ? (c - 'A' + 10)
           : (c >= 'a' && c <= 'f') ? (c - 'a' + 10)
                                    : 0;
}

constexpr auto hexToDec(char digit1, char digit2) -> unsigned int {
    return (hexValue(digit1) << 4) | hexValue(digit2);
}

template <typename T, unsigned int N> struct VectorBase {
    OE_VECTOR_BOILER_PLATE_DEFINE(T, N)

    T data[N];
};

template <typename T> struct VectorBase<T, 2> {
    VectorBase(T x_, T y_)
        : x(x_)
        , y(y_) {}

    OE_VECTOR_BOILER_PLATE_DEFINE(T, 2)

    union {
        T data[2];
        struct {
            T /*x=*/x, /*y=*/y;
        };
        struct {
            T /*u=*/u, /*v=*/v;
        };
    };
};

template <> struct VectorBase<float, 3> {
    constexpr VectorBase(float x_, float y_, float z_)
        : x(x_)
        , y(y_)
        , z(z_) {}

    OE_VECTOR_BOILER_PLATE_DEFINE(float, 3)

    VectorBase(const char* hexStr) {
        if (hexStr[0] == '#') {
            unsigned int j = 0;

            if (strlen(hexStr) != OE_VECTOR_VEC_3_HEX_STR_LEN)
                throw std::invalid_argument("Invalid hex string length, expected string length of 7.");

            for (unsigned int i = 1; i < OE_VECTOR_VEC_3_HEX_STR_LEN; i++) {
                if ((hexStr[i] < 'a' || hexStr[i] > 'z') && (hexStr[i] < 'A' || hexStr[i] > 'Z') &&
                    (hexStr[i] < '0' || hexStr[i] > '9')) {
                    throw std::out_of_range("Invalid hex string digit, 0-9 or a-z or A-Z.");
                }
            }

            for (unsigned int i = 1; i < OE_VECTOR_VEC_3_HEX_STR_LEN; i += 2) {
                data[j++] = static_cast<float>(hexToDec(hexStr[i], hexStr[i + 1])) / 255.0F;
            }
        } else {
            throw std::invalid_argument("Invalid hex string for color, #dddddd where d is 0-9 or a-f.");
        }
    }

    union {
        float data[3]{};
        struct {
            float /*x=*/x, /*y=*/y, /*z=*/z;
        };
        struct {
            float /*r=*/r, /*g=*/g, /*b=*/b;
        };
    };
};

template <typename T> struct VectorBase<T, 3> {
    constexpr VectorBase(T x_, T y_, T z_)
        : x(x_)
        , y(y_)
        , z(z_) {}

    OE_VECTOR_BOILER_PLATE_DEFINE(T, 3)

    union {
        T data[3];
        struct {
            T /*x=*/x, /*y=*/y, /*z=*/z;
        };
        struct {
            T /*r=*/r, /*g=*/g, /*b=*/b;
        };
    };
};

template <> struct VectorBase<float, 4> {
    constexpr VectorBase(float x_, float y_, float z_, float w_)
        : x(x_)
        , y(y_)
        , z(z_)
        , w(w_) {}

    OE_VECTOR_BOILER_PLATE_DEFINE(float, 4)

    VectorBase(const char* hexStr) {
        if (hexStr[0] == '#') {
            unsigned int j = 0;
            unsigned int hexStrLen = strlen(hexStr);

            for (unsigned int i = 1; i < hexStrLen; i++) {
                if (!((hexStr[i] >= 'a' && hexStr[i] <= 'z') || (hexStr[i] >= 'A' && hexStr[i] <= 'Z') ||
                      (hexStr[i] >= '0' && hexStr[i] <= '9'))) {
                    throw std::out_of_range("Invalid hex string digit, 0-9 or a-z or A-Z.");
                }
            }

            switch (hexStrLen) {
            case OE_VECTOR_VEC_3_HEX_STR_LEN:
                for (unsigned int i = 1; i < OE_VECTOR_VEC_3_HEX_STR_LEN; i += 2) {
                    data[j++] = static_cast<float>(hexToDec(hexStr[i], hexStr[i + 1])) / 255.0f;
                }
                data[j] = 1.0f;
                break;

            case OE_VECTOR_VEC_4_HEX_STR_LEN:
                for (unsigned int i = 1; i < OE_VECTOR_VEC_4_HEX_STR_LEN; i += 2) {
                    data[j++] = static_cast<float>(hexToDec(hexStr[i], hexStr[i + 1])) / 255.0f;
                }
                break;
            default:
                throw std::invalid_argument("Invalid hex string length, expected string length of 7 or 9.");
                break;
            }
        } else {
            throw std::invalid_argument("Invalid hex string for color, #dddddddd where d is 0-9 or a-f.");
        }
    }

    union {
        float data[4]{};
        struct {
            float /*x=*/x, /*y=*/y, /*z=*/z, /*w=*/w;
        };
        struct {
            float /*r=*/r, /*g=*/g, /*b=*/b, /*a=*/a;
        };
    };
};

template <typename T> struct VectorBase<T, 4> {
    constexpr VectorBase(T x_, T y_, T z_, T w_)
        : x(x_)
        , y(y_)
        , z(z_)
        , w(w_) {}

    OE_VECTOR_BOILER_PLATE_DEFINE(T, 4)

    union {
        T data[4];
        struct {
            T /*x=*/x, /*y=*/y, /*z=*/z, /*w=*/w;
        };
        struct {
            T /*r=*/r, /*g=*/g, /*b=*/b, /*a=*/a;
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
    VectorBase<T, 3> ret(src.y * des.z - src.z * des.y, src.z * des.x - src.x * des.z, src.x * des.y - src.y * des.x);

    return ret;
}

template <typename T> auto length(const VectorBase<T, 2>& vec) -> T {
    return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}

template <typename T> auto length(const VectorBase<T, 3>& vec) -> T {
    return std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

template <typename T> auto lengthSquared(const VectorBase<T, 2>& vec) -> T {
    return (vec.x * vec.x + vec.y * vec.y);
}

template <typename T> auto lengthSquared(const VectorBase<T, 3>& vec) -> T {
    return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

template <typename T, unsigned int N> auto distance(const VectorBase<T, N>& src, const VectorBase<T, N>& des) -> T {
    return length(src - des);
}

template <typename T, unsigned int N> auto distanceSquared(const VectorBase<T, N>& src, const VectorBase<T, N>& des) -> T {
    return lengthSquared(src - des);
}

template <typename T, unsigned int N> auto normalized(const VectorBase<T, N>& vec) -> VectorBase<T, N> {
    static_assert(N >= 2 && N <= 3, "Normalized doesn't support vector of size other than 2 and 3.");

    if (length(vec))
        return VectorBase<T, N>::ZERO();

    return vec / length(vec);
}

template <typename T, unsigned int N> auto angle(const VectorBase<T, N>& src, const VectorBase<T, N>& des) -> T {
    T value = std::clamp(dot(src, des), T(-1), T(1));
    T lengths = (length(src) * length(des));

    if (lengths == 0)
        return 0;

    return std::acos(value / lengths);
}

template <typename T, unsigned int N>
auto project(const VectorBase<T, N>& src, const VectorBase<T, N>& des) -> VectorBase<T, N> {
    T denom = lengthSquared(des);

    if (denom == 0.0)
        return VectorBase<T, N>::ZERO();

    auto scale = dot(src, des) / denom;

    return des * scale;
}

template <typename T, unsigned int N> auto toString(const VectorBase<T, N>& vec) -> std::string {
    throw std::out_of_range("Vector does not support vector size outside of 2, 3, or 4.");
}

template <typename T> auto toString(const VectorBase<T, 2>& vec, bool alt = false) -> std::string {
    std::stringstream ss;

    if (alt)
        ss << "u: " << vec.x << ", v: " << vec.y;
    else
        ss << "x: " << vec.x << ", y: " << vec.y;

    return ss.str();
}

template <typename T> auto toString(const VectorBase<T, 3>& vec, bool alt = false) -> std::string {
    std::stringstream ss;

    if (alt)
        ss << "r: " << vec.x << ", g: " << vec.y << ", b: " << vec.z;
    else
        ss << "x: " << vec.x << ", y: " << vec.y << ", z: " << vec.z;

    return ss.str();
}

template <typename T> auto toString(const VectorBase<T, 4>& vec, bool alt = false) -> std::string {
    std::stringstream ss;

    if (alt)
        ss << "r: " << vec.x << ", g: " << vec.y << ", b: " << vec.z << ", a: " << vec.w;
    else
        ss << "x: " << vec.x << ", y: " << vec.y << ", z: " << vec.z << ", w: " << vec.w;

    return ss.str();
}

using Point2 = VectorBase<unsigned int, 2>;
using Vector2 = VectorBase<float, 2>;
using Vector2i = VectorBase<int, 2>;

using Point3 = VectorBase<unsigned int, 3>;
using Vector3 = VectorBase<float, 3>;
using Vector3i = VectorBase<int, 3>;

using Point4 = VectorBase<unsigned int, 4>;
using Vector4 = VectorBase<float, 4>;
using Vector4i = VectorBase<int, 4>;
} // namespace ObsidianEdge
