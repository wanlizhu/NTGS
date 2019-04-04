#pragma once

#include "Math/Vector.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include <type_traits>

namespace NTGS {
    template<typename T, typename U, int Cols, int Rows>
    inline Matrix<T, Cols, Rows> Mul(const Matrix<T, Cols, Rows>& m1, const Matrix<U, Cols, Rows>& m2) {
        using Index = typename Matrix<T, Cols, Rows>::Index;
        Matrix<T, Cols, Rows> result;
        for (int i = 0; i < Cols; i++)
            for (int j = 0; j < Rows; j++)
                result.mArray[Index(i, j)] = m1.mArray[Index(i, j)] * m2.mArray[Index(i, j)];
        return result;
    }

    template<typename T, int N>
    inline T Length(const Vector<T, N>& vec) {
        T sum = 0;
        for (int i = 0; i < N; i++)
            sum += vec[i] * vec[i];
        return std::sqrt(sum);
    }

    template<typename T, int N>
    inline Vector<T, N> Normalize(const Vector<T, N>& vec) {
        return Vector<T, N>(vec) /= Length(vec);
    }

    template<typename T, int MN,
             typename = typename std::enable_if<(1 < MN)>::type>
    inline bool SetIdentity(Matrix<T, MN, MN>& m) {
        using Index = typename Matrix<T, MN, MN>::Index;
        for (int i = 0; i < MN; i++)
            for (int j = 0; j < MN; j++) {
                m.mArray[Index(i, j)] = (i == j ? 1 : 0);
            }
        return true;
    }

    template<typename T, int MN,
             typename = typename std::enable_if<(1 < MN)>::type>
    inline bool IsIdentity(const Matrix<T, MN, MN>& m) {
        for (int i = 0; i < MN; i++)
            for (int j = 0; j < MN; j++) {
                if (i == j && !FLOAT_EQ(m[i][j], T(1)))
                    return false;
                if (i != j && !FLOAT_EQ(m[i][j], T(0)))
                    return false;
            }
        return true;
    }

    template<typename T, typename U, int N>
    inline T operator*(const Vector<T, N>& v1, 
                       const Vector<U, N>& v2) {
        T sum = 0;
        for (int i = 0; i < N; i++)
            sum += v1[i] * v2[i];
        return sum;
    }

    template<typename T, typename U>
    inline Vector<T, 3> operator^(const Vector<T, 3>& v1,
                                  const Vector<U, 3>& v2) {
        return Vector<T, 3>(
            v1.y * v2.z - v2.y * v1.z,
            v1.z * v2.x - v2.z * v1.x,
            v1.x * v2.y - v2.x * v1.y);
    }
}