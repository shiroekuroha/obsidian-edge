#pragma once

#include "vector.h"

#include "core/log/log.h"

namespace ObsidianEdge {
template <typename T, unsigned int Rows, unsigned int Cols> struct MatrixBase {
    constexpr MatrixBase() = default;
    constexpr MatrixBase(const MatrixBase &other) = default;
    constexpr MatrixBase(MatrixBase &&other) noexcept = default;
    constexpr auto operator=(const MatrixBase &other) -> MatrixBase & = default;
    constexpr auto operator=(MatrixBase &&other) noexcept -> MatrixBase & = default;
    ~MatrixBase() = default;

    constexpr MatrixBase(const std::initializer_list<T> &init) {
        unsigned int i = 0;
        for (const T &el : init) {
            this->at(i) = el;
            i++;
        }
    }

    constexpr MatrixBase(T scalar) {
        for (unsigned int row = 0; row < Rows; row++)
            for (unsigned int col = 0; col < Cols; col++)
                this->at(row, col) = scalar;
    }

    constexpr auto operator*=(T scalar) -> MatrixBase & {
        for (unsigned int row = 0; row < Rows; row++) {
            for (unsigned int col = 0; col < Cols; col++) {
                this->at(row, col) *= scalar;
            }
        }

        return *this;
    }

    constexpr auto operator==(const MatrixBase &other) const -> bool {
        for (unsigned int row = 0; row < Rows; row++) {
            for (unsigned int col = 0; col < Cols; col++) {
                if (this->at(row, col) != other.at(row, col))
                    return false;
            }
        }

        return true;
    }

    constexpr auto operator!=(const MatrixBase &other) const -> bool {
        for (unsigned int row = 0; row < Rows; row++) {
            for (unsigned int col = 0; col < Cols; col++) {
                if (this->at(row, col) != other.at(row, col))
                    return true;
            }
        }

        return false;
    }

    constexpr auto operator*(T scalar) -> MatrixBase {
        MatrixBase ret = *this;

        ret *= scalar;

        return ret;
    }

    constexpr auto operator/=(T scalar) -> MatrixBase & {
        for (unsigned int row = 0; row < Rows; row++) {
            for (unsigned int col = 0; col < Cols; col++) {
                this->at(row, col) /= scalar;
            }
        }

        return *this;
    }

    constexpr auto operator/(T scalar) -> MatrixBase {
        MatrixBase ret = *this;

        ret /= scalar;

        return ret;
    }

    constexpr auto operator+=(const MatrixBase &other) -> MatrixBase & {
        for (unsigned int row = 0; row < Rows; row++) {
            for (unsigned int col = 0; col < Cols; col++) {
                this->at(row, col) += other.at(row, col);
            }
        }

        return *this;
    }

    constexpr auto operator+(const MatrixBase &other) -> MatrixBase {
        MatrixBase ret = *this;

        ret += other;

        return ret;
    }

    constexpr auto operator-=(const MatrixBase &other) -> MatrixBase & {
        for (unsigned int row = 0; row < Rows; row++) {
            for (unsigned int col = 0; col < Cols; col++) {
                this->at(row, col) -= other.at(row, col);
            }
        }

        return *this;
    }

    constexpr auto operator-(const MatrixBase &other) -> MatrixBase {
        MatrixBase ret = *this;

        ret -= other;

        return ret;
    }

    constexpr auto at(unsigned int index) const -> const T & { return data[index / Cols][index % Cols]; }

    constexpr auto at(unsigned int index) -> T & { return data[index / Cols][index % Cols]; }

    constexpr auto at(unsigned int row, unsigned int col) const -> const T & { return data[row][col]; }

    constexpr auto at(unsigned int row, unsigned int col) -> T & { return data[row][col]; }

    constexpr auto operator[](unsigned int row) const -> const VectorBase<T, Cols> & { return data[row]; }

    constexpr auto operator[](unsigned int row) -> VectorBase<T, Cols> & { return data[row]; }

    inline auto getTrueArray() const -> std::array<T, Rows * Cols> {
        std::array<T, Rows * Cols> ret = {};

        for (unsigned int i = 0; i < Rows * Cols; i++) {
            ret[i] = this->at(i);
        }

        return ret;
    }

    VectorBase<T, Cols> data[Rows];
};

template <typename T, unsigned int N> struct MatrixSquare : public MatrixBase<T, N, N> {
    constexpr MatrixSquare() = default;
    constexpr MatrixSquare(const MatrixSquare &other) = default;
    constexpr MatrixSquare(MatrixSquare &&other) noexcept = default;
    constexpr auto operator=(const MatrixSquare &other) -> MatrixSquare & = default;
    constexpr auto operator=(MatrixSquare &&other) noexcept -> MatrixSquare & = default;
    ~MatrixSquare() = default;

    constexpr MatrixSquare(const MatrixBase<T, N, N> &other) {
        for (unsigned int row = 0; row < N; row++)
            for (unsigned int col = 0; col < N; col++)
                this->at(row, col) = other.at(row, col);
    }

    constexpr MatrixSquare(MatrixBase<T, N, N> &&other) noexcept {
        for (unsigned int row = 0; row < N; row++)
            for (unsigned int col = 0; col < N; col++)
                this->at(row, col) = std::move(other.at(row, col));
    }

    constexpr auto operator=(const MatrixBase<T, N, N> &other) -> MatrixSquare & {
        for (unsigned int row = 0; row < N; row++)
            for (unsigned int col = 0; col < N; col++)
                this->at(row, col) = other.at(row, col);

        return *this;
    }

    constexpr auto operator=(MatrixBase<T, N, N> &&other) noexcept -> MatrixSquare & {
        for (unsigned int row = 0; row < N; row++)
            for (unsigned int col = 0; col < N; col++)
                this->at(row, col) = std::move(other.at(row, col));

        return *this;
    }

    constexpr MatrixSquare(const std::initializer_list<T> &init) {
        unsigned int i = 0;
        for (const T &el : init) {
            this->at(i) = el;
            i++;
        }
    }

    constexpr MatrixSquare(T scalar) {
        for (unsigned int row = 0; row < N; row++)
            for (unsigned int col = 0; col < N; col++)
                this->at(row, col) = scalar;
    }

    static constexpr auto identity() -> MatrixSquare {
        MatrixSquare mat;

        for (unsigned int i = 0; i < N; i++)
            mat[i][i] = 1;

        return mat;
    }
};

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

/**
 * @brief Get string format of the matrix
 *
 * @tparam T (Type Deduction)
 * @tparam RowCount (Type Deduction)
 * @tparam ColCount (Type Deduction)
 * @param mat
 * @return std::string
 */
template <typename T, unsigned int RowCount, unsigned int ColCount>
auto toString(const MatrixBase<T, RowCount, ColCount> &mat) -> std::string {
    std::string ret;

    for (unsigned int row = 0; row < RowCount; row++) {
        if (row != 0)
            ret += ",";

        ret += "(" + toString(mat.data[row]) + ")";
    }

    return ret;
}

/**
 * @brief Flip square matrix diagonally
 *
 * @tparam T (Type Deduction)
 * @tparam RowCount (Type Deduction)
 * @tparam ColCount (Type Deduction)
 * @param mat
 * @return MatrixBase<T, RowCount, ColCount>
 */
template <typename T, unsigned int RowCount, unsigned int ColCount>
constexpr auto transpose(const MatrixBase<T, RowCount, ColCount> &mat) -> MatrixBase<T, ColCount, RowCount> {
    MatrixBase<T, ColCount, RowCount> ret;

    for (unsigned int row = 0; row < RowCount; row++) {
        for (unsigned int col = 0; col < ColCount; col++) {
            ret.at(col, row) = mat.at(row, col);
        }
    }

    return ret;
}

/**
 * @brief Get determinant of matrix square, this is for matrix square size 2
 *
 * @tparam T (Type Deduction)
 * @param mat
 * @return T
 */
template <typename T> constexpr auto determinant(const MatrixSquare<T, 2> &mat) -> T {
    return static_cast<T>(mat.at(0)) * static_cast<T>(mat.at(3)) - static_cast<T>(mat.at(1)) * static_cast<T>(mat.at(2));
}

/**
 * @brief Get determinant of matrix square, this is for ambiguous matrix square size N
 *
 * @tparam T (Type Deduction)
 * @tparam N (Type Deduction)
 * @param mat
 * @return T
 */
template <typename T, unsigned int N> constexpr auto determinant(const MatrixSquare<T, N> &mat) -> T {
    static_assert(N >= 2 && N <= 4, "Determinant don't support matrix size other than 2, 3 or 4.");

    T result = 0;

    for (unsigned int select = 0; select < N; select++) {
        MatrixSquare<T, N - 1> minor;

        for (unsigned int row = 1; row < N; row++) {
            for (unsigned int col = 0; col < N; col++) {
                if (col == select) {
                    continue;
                }

                if (col > select) {
                    minor.at(row - 1, col - 1) = mat.at(row, col);
                } else {
                    minor.at(row - 1, col) = mat.at(row, col);
                }
            }
        }

        if (select % 2 == 0) {
            T det = determinant(minor);
            result += mat.at(0, select) * det;
        } else {
            T det = determinant(minor);
            result -= mat.at(0, select) * det;
        }
    }

    return result;
}

/**
 * @brief Check if matrix is invertible
 *
 * @tparam T
 * @tparam N
 * @param mat
 * @return true
 * @return false
 */
template <typename T, unsigned int N> constexpr auto isInvertible(const MatrixSquare<T, N> &mat) -> bool {
    return determinant(mat) != 0;
}

template <typename T> constexpr auto invert(const MatrixSquare<T, 2> &mat) -> MatrixSquare<T, 2> {
    if (!isInvertible(mat)) {
        OE_CORE_ERROR("Invert failed, determinant is not 0.")
    }

    MatrixSquare<T, 2> ret = mat;
    T det = determinant(mat);

    ret.at(0) = mat.at(3);
    ret.at(1) = -mat.at(1);
    ret.at(2) = -mat.at(2);
    ret.at(3) = mat.at(0);

    ret /= det;

    return ret;
}

template <typename T, unsigned int N> constexpr auto invert(const MatrixSquare<T, N> &mat) -> MatrixSquare<T, N> {
    if (!isInvertible(mat)) {
        OE_CORE_ERROR("Invert failed, determinant is not 0.")
    }

    MatrixSquare<T, N> ret;

    for (unsigned int i = 0; i < N * N; i++) {
        unsigned int sel_x = i % N;
        unsigned int sel_y = i / N;

        MatrixSquare<T, N - 1> lower_mat;

        for (unsigned int local_y = 0; local_y < N; local_y++) {
            for (unsigned int local_x = 0; local_x < N; local_x++) {
                if (local_x == sel_x || local_y == sel_y)
                    continue;

                lower_mat.at(local_y > sel_y ? local_y - 1 : local_y, local_x > sel_x ? local_x - 1 : local_x) =
                    mat.at(local_y, local_x);
            }
        }

        ret.at(i) = determinant(lower_mat);
    }

    for (unsigned row = 0; row < N; ++row) {
        for (unsigned col = 0; col < N; ++col) {
            if ((row + col) % 2)
                ret.at(row, col) = -ret.at(row, col);
        }
    }

    ret = transpose(ret);
    ret = ret / determinant(mat);

    return ret;
}

template <typename T, unsigned int Rows, unsigned int Cols>
auto operator*(const MatrixBase<T, Rows, Cols> &mat, const VectorBase<T, Cols> &vec) -> VectorBase<T, Rows> {
    VectorBase<T, Rows> ret;

    for (unsigned int row = 0; row < Rows; row++) {
        T total = static_cast<T>(0);

        for (unsigned int col = 0; col < Cols; col++) {
            total += mat[row][col] * vec[col];
        }

        ret[row] = total;
    }

    return ret;
}
} // namespace ObsidianEdge
