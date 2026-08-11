#pragma once

#include "core.h"

#include "core/data/maths/vector.h"

#include "core/data/maths/common.h"

namespace ObsidianEdge {
template <typename T, unsigned int Rows, unsigned int Cols> struct OE_API MatrixBase {
    static_assert(std::is_arithmetic_v<T>, "Cannot create matrix with non-arithmetic type.");
    static_assert(Rows > 0, "Matrix must have at least one row");
    static_assert(Cols > 0, "Matrix must have at least one column");

private:
    static constexpr unsigned int TOTAL_ELEMENTS = Rows * Cols;

public:
    constexpr MatrixBase() = default;
    ~MatrixBase() = default;

    constexpr MatrixBase(const MatrixBase& other) = default;
    constexpr MatrixBase(MatrixBase&& other) noexcept = default;

    constexpr auto operator=(const MatrixBase& other) -> MatrixBase& = default;
    constexpr auto operator=(MatrixBase&& other) noexcept -> MatrixBase& = default;

    template <typename... Args> constexpr MatrixBase(Args&&... args) {
        static_assert(sizeof...(Args) == TOTAL_ELEMENTS, "Wrong number of matrix elements");

        auto array = std::array<T, TOTAL_ELEMENTS>{T(std::forward<Args>(args))...};

        for (unsigned int i = 0; i < TOTAL_ELEMENTS; i++) {
            data[i / Cols][i % Cols] = array[i];
        }
    }

    constexpr MatrixBase(T scalar) {
        for (unsigned int row = 0; row < Rows; row++) {
            for (unsigned int col = 0; col < Cols; col++) {
                this->at(row, col) = scalar;
            }
        }
    }

    constexpr auto operator==(const MatrixBase& other) const -> bool {
        if (this == &other) {
            return true;
        }

        for (unsigned int row = 0; row < Rows; row++) {
            for (unsigned int col = 0; col < Cols; col++) {
                if (this->at(row, col) != other.at(row, col)) {
                    return false;
                }
            }
        }

        return true;
    }

    constexpr auto operator!=(const MatrixBase& other) const -> bool {
        if (this == &other) {
            return false;
        }

        return !(*this == other);
    }

    constexpr auto operator*=(T scalar) -> MatrixBase& {
        for (unsigned int row = 0; row < Rows; row++) {
            for (unsigned int col = 0; col < Cols; col++) {
                this->at(row, col) *= scalar;
            }
        }

        return *this;
    }

    constexpr auto operator*(T scalar) const -> MatrixBase {
        MatrixBase ret = *this;

        ret *= scalar;

        return ret;
    }

    constexpr auto operator/=(T scalar) -> MatrixBase& {
        if (scalar == T(0)) {
            OE_CORE_ERROR("Division by zero is not allowed.");
            throw std::invalid_argument("Division by zero is not allowed.");
        }

        for (unsigned int row = 0; row < Rows; row++) {
            for (unsigned int col = 0; col < Cols; col++) {
                this->at(row, col) /= scalar;
            }
        }

        return *this;
    }

    constexpr auto operator/(T scalar) const -> MatrixBase {
        if (scalar == T(0)) {
            OE_CORE_ERROR("Division by zero is not allowed.");
            throw std::invalid_argument("Division by zero is not allowed.");
        }

        MatrixBase ret = *this;

        ret /= scalar;

        return ret;
    }

    constexpr auto operator+=(const MatrixBase& other) -> MatrixBase& {
        for (unsigned int row = 0; row < Rows; row++) {
            for (unsigned int col = 0; col < Cols; col++) {
                this->at(row, col) += other.at(row, col);
            }
        }

        return *this;
    }

    constexpr auto operator+(const MatrixBase& other) const -> MatrixBase {
        MatrixBase ret = *this;

        ret += other;

        return ret;
    }

    constexpr auto operator-=(const MatrixBase& other) -> MatrixBase& {
        for (unsigned int row = 0; row < Rows; row++) {
            for (unsigned int col = 0; col < Cols; col++) {
                this->at(row, col) -= other.at(row, col);
            }
        }

        return *this;
    }

    constexpr auto operator-(const MatrixBase& other) const -> MatrixBase {
        MatrixBase ret = *this;

        ret -= other;

        return ret;
    }

    constexpr auto at(unsigned int index) const -> const T& {
        if (index >= TOTAL_ELEMENTS) {
            OE_CORE_ERROR("Accessing matrix's element out of bound.");
            throw std::out_of_range("Accessing matrix's element out of bound.");
        }

        return data[index / Cols][index % Cols];
    }

    constexpr auto at(unsigned int index) -> T& {
        if (index >= TOTAL_ELEMENTS) {
            OE_CORE_ERROR("Accessing matrix's element out of bound.");
            throw std::out_of_range("Accessing matrix's element out of bound.");
        }

        return data[index / Cols][index % Cols];
    }

    constexpr auto at(unsigned int row, unsigned int col) const -> const T& {
        if (row >= Rows || col >= Cols) {
            OE_CORE_ERROR("Accessing matrix's element out of bound.");
            throw std::out_of_range("Accessing matrix's element out of bound.");
        }

        return (*this)[row][col];
    }

    constexpr auto at(unsigned int row, unsigned int col) -> T& {
        if (row >= Rows || col >= Cols) {
            OE_CORE_ERROR("Accessing matrix's element out of bound.");
            throw std::out_of_range("Accessing matrix's element out of bound.");
        }

        return (*this)[row][col];
    }

    constexpr auto operator[](unsigned int row) const -> const VectorBase<T, Cols>& {
        if (row >= Rows) {
            OE_CORE_ERROR("Invalid matrix access: out of range");
            throw std::out_of_range("Invalid matrix access: out of range");
        }

        return data.at(row);
    }

    constexpr auto operator[](unsigned int row) -> VectorBase<T, Cols>& {
        if (row >= Rows) {
            OE_CORE_ERROR("Invalid matrix access: out of range");
            throw std::out_of_range("Invalid matrix access: out of range");
        }

        return data.at(row);
    }

    static constexpr auto zero() -> MatrixBase {
        return MatrixBase(0);
    }

    auto get() const -> std::array<T, static_cast<std::size_t>(Rows* Cols)> {
        std::array<T, static_cast<std::size_t>(Rows * Cols)> ret = {};

        for (unsigned int i = 0; i < Rows * Cols; i++) {
            ret[i] = this->at(i);
        }

        return ret;
    }

    std::array<VectorBase<T, Cols>, Rows> data;
};

template <typename T, unsigned int N> struct OE_API MatrixSquare : public MatrixBase<T, N, N> {
    static_assert(std::is_arithmetic_v<T>, "Cannot create matrix with non-arithmetic type.");
    static_assert(N > 1, "Matrix must have at least dimension of 2");

private:
    static constexpr unsigned int TOTAL_ELEMENTS = N * N;

public:
    constexpr MatrixSquare() = default;
    ~MatrixSquare() = default;

    constexpr MatrixSquare(const MatrixSquare& other) = default;
    constexpr MatrixSquare(MatrixSquare&& other) noexcept = default;

    constexpr auto operator=(const MatrixSquare& other) -> MatrixSquare& = default;
    constexpr auto operator=(MatrixSquare&& other) noexcept -> MatrixSquare& = default;

    constexpr MatrixSquare(const MatrixBase<T, N, N>& other) {
        *this = other;
    }

    constexpr MatrixSquare(MatrixBase<T, N, N>&& other) noexcept {
        *this = std::move(other);
    }

    constexpr auto operator=(const MatrixBase<T, N, N>& other) -> MatrixSquare& {
        for (unsigned int row = 0; row < N; row++) {
            (*this)[row] = (other[row]);
        }

        return *this;
    }

    constexpr auto operator=(MatrixBase<T, N, N>&& other) noexcept // NOLINT(cppcoreguidelines-rvalue-reference-param-not-moved)
        -> MatrixSquare& {
        for (unsigned int row = 0; row < N; row++) {
            (*this)[row] = std::move(other[row]);
        }

        return *this;
    }

    constexpr MatrixSquare(MatrixSquare<T, N - 1> minor) {
        for (unsigned int row = 0; row < N - 1; row++) {
            for (unsigned int col = 0; col < N - 1; col++) {
                this->at(row, col) = minor.at(row, col);
            }
        }
    }

    constexpr MatrixSquare(const std::initializer_list<T>& init) {
        if (init.size() != TOTAL_ELEMENTS) {
            OE_CORE_ERROR("Wrong number of matrix elements");
            throw std::out_of_range("Wrong number of matrix elements");
        }

        unsigned int index = 0;
        for (const T& value : init) {
            this->at(index) = value;
            index++;
        }
    }

    constexpr MatrixSquare(T scalar) {
        *this = identity() * scalar;
    }

    static constexpr auto identity() -> MatrixSquare {
        MatrixSquare mat;

        for (unsigned int i = 0; i < N; i++) {
            mat[i][i] = 1;
        }

        return mat;
    }
};

template <typename T, unsigned int RowCount, unsigned int ColCount>
constexpr auto transpose(const MatrixBase<T, RowCount, ColCount>& mat) -> MatrixBase<T, ColCount, RowCount> {
    MatrixBase<T, ColCount, RowCount> ret;

    for (unsigned int row = 0; row < RowCount; row++) {
        for (unsigned int col = 0; col < ColCount; col++) {
            ret.at(col, row) = mat.at(row, col);
        }
    }

    return ret;
}

template <typename T, unsigned int N>
constexpr auto selectSubMatrixSquare(const MatrixSquare<T, N>& mat, Point2 selected) -> MatrixSquare<T, N - 1> {
    if (selected.row >= N || selected.col >= N) {
        OE_CORE_ERROR("Matrix selection out of bounds: ({0}, {1}) for a {2}x{2} matrix.", selected.col, selected.row, N);
        throw std::out_of_range("Matrix selection out of bounds.");
    }

    MatrixSquare<T, N - 1> ret;

    for (unsigned int row = 0; row < N; row++) {
        for (unsigned int col = 0; col < N; col++) {
            if (row == selected.row || col == selected.col) {
                continue;
            }

            ret.at(row - (row > selected.row ? 1 : 0), col - (col > selected.col ? 1 : 0)) = mat.at(row, col);
        }
    }

    return ret;
};

template <typename T> constexpr auto determinant(const MatrixSquare<T, 2>& mat) -> T {
    return (mat.at(0, 0) * mat.at(1, 1)) - (mat.at(0, 1) * mat.at(1, 0));
}

template <typename T, unsigned int N> constexpr auto determinant(const MatrixSquare<T, N>& mat) -> T {
    T result = 0;

    for (unsigned int select = 0; select < N; select++) {
        MatrixSquare<T, N - 1> minor;

        minor = selectSubMatrixSquare(mat, {0, select});

        const T DET = determinant(minor);

        if (select % 2 == 0) {
            result += mat.at(0, select) * DET;
        } else {
            result -= mat.at(0, select) * DET;
        }
    }

    return result;
}

template <typename T, unsigned int N> constexpr auto isInvertible(const MatrixSquare<T, N>& mat) -> bool {
    return std::abs(determinant(mat)) > EPSILON;
}

template <typename T> constexpr auto invert(const MatrixSquare<T, 2>& mat) -> MatrixSquare<T, 2> {
    MatrixSquare<T, 2> ret = mat;
    const T DET = determinant(mat);

    if (DET == T(0)) {
        OE_CORE_ERROR("Cannot invert a singular matrix. Returning the ZERO matrix.");
        return MatrixSquare<T, 2>::zero();
    }

    ret.at(0, 0) = mat.at(1, 1);
    ret.at(0, 1) = -mat.at(0, 1);
    ret.at(1, 0) = -mat.at(1, 0);
    ret.at(1, 1) = mat.at(0, 0);

    ret /= DET;

    return ret;
}

template <typename T, unsigned int N> constexpr auto invert(const MatrixSquare<T, N>& mat) -> MatrixSquare<T, N> {
    MatrixSquare<T, N> ret;
    const T DET = determinant(mat);

    if (DET == T(0)) {
        OE_CORE_WARN("Cannot invert a singular matrix. Returning the ZERO matrix.");
        return MatrixSquare<T, N>::zero();
    }

    for (unsigned int row = 0; row < N; row++) {
        for (unsigned int col = 0; col < N; col++) {
            ret.at(row, col) = determinant(selectSubMatrixSquare(mat, {col, row}));
        }
    }

    for (unsigned row = 0; row < N; row++) {
        for (unsigned col = 0; col < N; col++) {
            if ((row + col) % 2) {
                ret.at(row, col) = -ret.at(row, col);
            }
        }
    }

    ret = ret / DET;

    return ret;
}

template <typename T, unsigned int N>
auto operator*(const MatrixSquare<T, N>& mat, const VectorBase<T, N>& vec) -> VectorBase<T, N> {
    VectorBase<T, N> ret;

    for (unsigned int row = 0; row < N; row++) {
        for (unsigned int col = 0; col < N; col++) {
            ret.at(row) += mat.at(row, col) * vec.at(col);
        }
    }

    return ret;
}

template <typename T, unsigned int N>
constexpr auto operator*(const VectorBase<T, N>& vec, const MatrixSquare<T, N>& mat) -> VectorBase<T, N> {
    VectorBase<T, N> ret{};

    for (unsigned int col = 0; col < N; col++) {
        for (unsigned int row = 0; row < N; row++) {
            ret.at(col) += vec.at(row) * mat.at(row, col);
        }
    }

    return ret;
}

template <typename T, unsigned int M, unsigned int N, unsigned int P>
constexpr auto operator*(const MatrixBase<T, M, N>& matA, const MatrixBase<T, N, P>& matB) -> MatrixBase<T, M, P> {
    MatrixBase<T, M, P> ret;

    // TODO: Optimize for better caching, for better code documentation leave this be for now.

    for (unsigned int row = 0; row < M; row++) {
        for (unsigned int exCol = 0; exCol < P; exCol++) {
            T total = T(0);

            for (unsigned int col = 0; col < N; col++) {
                total += matA.at(row, col) * matB.at(col, exCol);
            }

            ret.at(row, exCol) = total;
        }
    }

    return ret;
}

template <typename T, unsigned int RowCount, unsigned int ColCount>
auto toString(const MatrixBase<T, RowCount, ColCount>& mat) -> std::string {
    std::string ret;

    for (unsigned int row = 0; row < RowCount; row++) {
        if (row != 0) {
            ret += ",";
        }

        ret += "(" + toString(mat.data[row]) + ")";
    }

    return ret;
}

// clang-format off
/** @brief Matrix 2 float*/                 using Matrix2       = MatrixSquare<float, 2>;
/** @brief Matrix 2 double*/                using Matrix2p      = MatrixSquare<double, 2>;
/** @brief Matrix 2 unsigned int*/          using Matrix2i      = MatrixSquare<int, 2>;

/** @brief Matrix 3 float*/                 using Matrix3       = MatrixSquare<float, 3>;
/** @brief Matrix 3 double*/                using Matrix3p      = MatrixSquare<double, 3>;
/** @brief Matrix 3 unsigned int*/          using Matrix3i      = MatrixSquare<int, 3>;

/** @brief Matrix 4 float*/                 using Matrix4       = MatrixSquare<float, 4>;
/** @brief Matrix 4 double*/                using Matrix4p      = MatrixSquare<double, 4>;
/** @brief Matrix 4 unsigned int*/          using Matrix4i      = MatrixSquare<int, 4>;
// clang-format on

} // namespace ObsidianEdge
