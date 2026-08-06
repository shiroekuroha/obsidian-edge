#include <pch.h>

#include "core/data/maths/matrix.h"
#include "core/data/maths/vector.h"

namespace ObsidianEdge {
static const VectorBase<short, 2> v_init_short_2 = {};
static const VectorBase<short, 3> v_init_short_3 = {};
static const VectorBase<short, 4> v_init_short_4 = {};

static const VectorBase<unsigned short, 2> v_init_u_short_2 = {};
static const VectorBase<unsigned short, 3> v_init_u_short_3 = {};
static const VectorBase<unsigned short, 4> v_init_u_short_4 = {};

static const VectorBase<int, 2> v_init_int_2 = {};
static const VectorBase<int, 3> v_init_int_3 = {};
static const VectorBase<int, 4> v_init_int_4 = {};

static const VectorBase<unsigned int, 2> v_init_u_int_2 = {};
static const VectorBase<unsigned int, 3> v_init_u_int_3 = {};
static const VectorBase<unsigned int, 4> v_init_u_int_4 = {};

static const VectorBase<long, 2> v_init_long_2 = {};
static const VectorBase<long, 3> v_init_long_3 = {};
static const VectorBase<long, 4> v_init_long_4 = {};

static const VectorBase<unsigned long, 2> v_init_u_long_2 = {};
static const VectorBase<unsigned long, 3> v_init_u_long_3 = {};
static const VectorBase<unsigned long, 4> v_init_u_long_4 = {};

static const VectorBase<float, 2> v_init_float_2 = {};
static const VectorBase<float, 3> v_init_float_3 = {};
static const VectorBase<float, 4> v_init_float_4 = {};

static const VectorBase<double, 2> v_init_double_2 = {};
static const VectorBase<double, 3> v_init_double_3 = {};
static const VectorBase<double, 4> v_init_double_4 = {};

static const MatrixBase<short, 2, 2> m_init_short_2 = {};
static const MatrixBase<short, 3, 2> m_init_short_3 = {};
static const MatrixBase<short, 4, 2> m_init_short_4 = {};

static const MatrixBase<unsigned short, 2, 2> m_init_u_short_2_2 = {};
static const MatrixBase<unsigned short, 3, 2> m_init_u_short_3_2 = {};
static const MatrixBase<unsigned short, 4, 2> m_init_u_short_4_2 = {};

static const MatrixBase<int, 2, 2> m_init_int_2_2 = {};
static const MatrixBase<int, 3, 2> m_init_int_3_2 = {};
static const MatrixBase<int, 4, 2> m_init_int_4_2 = {};

static const MatrixBase<unsigned int, 2, 2> m_init_u_int_2_2 = {};
static const MatrixBase<unsigned int, 3, 2> m_init_u_int_3_2 = {};
static const MatrixBase<unsigned int, 4, 2> m_init_u_int_4_2 = {};

static const MatrixBase<long, 2, 2> m_init_long_2_2 = {};
static const MatrixBase<long, 3, 2> m_init_long_3_2 = {};
static const MatrixBase<long, 4, 2> m_init_long_4_2 = {};

static const MatrixBase<unsigned long, 2, 2> m_init_u_long_2_2 = {};
static const MatrixBase<unsigned long, 3, 2> m_init_u_long_3_2 = {};
static const MatrixBase<unsigned long, 4, 2> m_init_u_long_4_2 = {};

static const MatrixBase<float, 2, 2> m_init_float_2_2 = {};
static const MatrixBase<float, 3, 2> m_init_float_3_2 = {};
static const MatrixBase<float, 4, 2> m_init_float_4_2 = {};

static const MatrixBase<double, 2, 2> m_init_double_2_2 = {};
static const MatrixBase<double, 3, 2> m_init_double_3_2 = {};
static const MatrixBase<double, 4, 2> m_init_double_4_2 = {};

static const MatrixBase<unsigned short, 2, 3> m_init_u_short_2_3 = {};
static const MatrixBase<unsigned short, 3, 3> m_init_u_short_3_3 = {};
static const MatrixBase<unsigned short, 4, 3> m_init_u_short_4_3 = {};

static const MatrixBase<int, 2, 3> m_init_int_2_3 = {};
static const MatrixBase<int, 3, 3> m_init_int_3_3 = {};
static const MatrixBase<int, 4, 3> m_init_int_4_3 = {};

static const MatrixBase<unsigned int, 2, 3> m_init_u_int_2_3 = {};
static const MatrixBase<unsigned int, 3, 3> m_init_u_int_3_3 = {};
static const MatrixBase<unsigned int, 4, 3> m_init_u_int_4_3 = {};

static const MatrixBase<long, 2, 3> m_init_long_2_3 = {};
static const MatrixBase<long, 3, 3> m_init_long_3_3 = {};
static const MatrixBase<long, 4, 3> m_init_long_4_3 = {};

static const MatrixBase<unsigned long, 2, 3> m_init_u_long_2_3 = {};
static const MatrixBase<unsigned long, 3, 3> m_init_u_long_3_3 = {};
static const MatrixBase<unsigned long, 4, 3> m_init_u_long_4_3 = {};

static const MatrixBase<float, 2, 3> m_init_float_2_3 = {};
static const MatrixBase<float, 3, 3> m_init_float_3_3 = {};
static const MatrixBase<float, 4, 3> m_init_float_4_3 = {};

static const MatrixBase<double, 2, 3> m_init_double_2_3 = {};
static const MatrixBase<double, 3, 3> m_init_double_3_3 = {};
static const MatrixBase<double, 4, 3> m_init_double_4_3 = {};

static const MatrixBase<unsigned short, 2, 4> m_init_u_short_2_4 = {};
static const MatrixBase<unsigned short, 3, 4> m_init_u_short_3_4 = {};
static const MatrixBase<unsigned short, 4, 4> m_init_u_short_4_4 = {};

static const MatrixBase<int, 2, 4> m_init_int_2_4 = {};
static const MatrixBase<int, 3, 4> m_init_int_3_4 = {};
static const MatrixBase<int, 4, 4> m_init_int_4_4 = {};

static const MatrixBase<unsigned int, 2, 4> m_init_u_int_2_4 = {};
static const MatrixBase<unsigned int, 3, 4> m_init_u_int_3_4 = {};
static const MatrixBase<unsigned int, 4, 4> m_init_u_int_4_4 = {};

static const MatrixBase<long, 2, 4> m_init_long_2_4 = {};
static const MatrixBase<long, 3, 4> m_init_long_3_4 = {};
static const MatrixBase<long, 4, 4> m_init_long_4_4 = {};

static const MatrixBase<unsigned long, 2, 4> m_init_u_long_2_4 = {};
static const MatrixBase<unsigned long, 3, 4> m_init_u_long_3_4 = {};
static const MatrixBase<unsigned long, 4, 4> m_init_u_long_4_4 = {};

static const MatrixBase<float, 2, 4> m_init_float_2_4 = {};
static const MatrixBase<float, 3, 4> m_init_float_3_4 = {};
static const MatrixBase<float, 4, 4> m_init_float_4_4 = {};

static const MatrixBase<double, 2, 4> m_init_double_2_4 = {};
static const MatrixBase<double, 3, 4> m_init_double_3_4 = {};
static const MatrixBase<double, 4, 4> m_init_double_4_4 = {};
} // namespace ObsidianEdge
