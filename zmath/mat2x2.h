//
// Copyright (c) 2009-2015 Sergey Chelombitko
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
#pragma once

template<class T>
struct mat2x2_t {
    union {
        struct {
            T m11, m12,
              m21, m22;
        };

        T m[2][2];
    };

    // Constructors
    mat2x2_t() {}
    mat2x2_t(T m11, T m12,
             T m21, T m22) :
        m11(m11), m12(m12),
        m21(m21), m22(m22) {}
    explicit mat2x2_t(const mat3x3_t<T>& mat) :
        m11(mat.m11), m12(mat.m12),
        m21(mat.m21), m22(mat.m22) {}
    explicit mat2x2_t(const T* p) :
        m11(p[0]), m12(p[1]),
        m21(p[2]), m22(p[3]) {}

    // Unary operators
    mat2x2_t operator - () const {
        return mat2x2_t(-m11, -m12,
                        -m21, -m22);
    }

    mat2x2_t operator ! () const {
        auto det = determinant();
        assert(fabs(det) > std::numeric_limits<T>::epsilon());
        return mat2x2_t( m22 / det, -m12 / det,
                        -m21 / det,  m11 / det);
    }

    // Binary operators
    mat2x2_t operator * (T f) const {
        return mat2x2_t(m11 * f, m12 * f,
                        m21 * f, m22 * f);
    }

    friend mat2x2_t operator * (T f, const mat2x2_t& mat) {
        return mat2x2_t(mat.m11 * f, mat.m12 * f,
                        mat.m21 * f, mat.m22 * f);
    }

    mat2x2_t operator / (T f) const {
        assert(fabs(f) > std::numeric_limits<T>::epsilon());
        return mat2x2_t(m11 / f, m12 / f,
                        m21 / f, m22 / f);
    }

    mat2x2_t operator + (const mat2x2_t& mat) const {
        return mat2x2_t(m11 + mat.m11, m12 + mat.m12,
                        m21 + mat.m21, m22 + mat.m22);
    }

    mat2x2_t operator - (const mat2x2_t& mat) const {
        return mat2x2_t(m11 - mat.m11, m12 - mat.m12,
                        m21 - mat.m21, m22 - mat.m22);
    }

    mat2x2_t operator * (const mat2x2_t& mat) const {
        mat2x2_t tmp;

        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                tmp.m[i][j] = 0;

                for (int k = 0; k < 2; ++k) {
                    tmp.m[i][j] += m[i][k] * mat.m[k][j];
                }
            }
        }

        return tmp;
    }

    mat2x2_t& operator *= (T f) {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                m[i][j] *= f;
            }
        }

        return *this;
    }

    mat2x2_t& operator /= (T f) {
        assert(fabs(f) > std::numeric_limits<T>::epsilon());

        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                m[i][j] /= f;
            }
        }

        return *this;
    }

    mat2x2_t& operator += (const mat2x2_t& mat) {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                m[i][j] += mat.m[i][j];
            }
        }

        return *this;
    }

    mat2x2_t& operator -= (const mat2x2_t& mat) {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                m[i][j] -= mat.m[i][j];
            }
        }

        return *this;
    }

    mat2x2_t& operator *= (const mat2x2_t& mat) {
        mat2x2_t tmp;

        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                tmp.m[i][j] = 0;

                for (int k = 0; k < 2; ++k) {
                    tmp.m[i][j] += m[i][k] * mat.m[k][j];
                }
            }
        }

        *this = tmp;
        return *this;
    }

    bool operator == (const mat2x2_t& mat) const {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                if (m[i][j] != mat.m[i][j]) {
                    return false;
                }
            }
        }

        return true;
    }

    bool operator != (const mat2x2_t& mat) const {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                if (m[i][j] != mat.m[i][j]) {
                    return true;
                }
            }
        }

        return false;
    }

    // Conversion operators
    explicit operator T* () {
        return &m[0][0];
    }

    explicit operator const T* () const {
        return &m[0][0];
    }

    T (&operator [] (int row))[2] {
        assert(row >= 0 && row < 2);
        return m[row];
    }

    vec2_t<T> row(int index) const {
        assert(index >= 0 && index < 2);
        return vec2_t<T>(m[index][0], m[index][1]);
    }

    vec2_t<T> column(int index) const {
        assert(index >= 0 && index < 2);
        return vec2_t<T>(m[0][index], m[1][index]);
    }

    T determinant() const {
        return det2x2(m11, m12,
                      m21, m22);
    }

    static mat2x2_t identity() {
        return mat2x2_t(1, 0,
                        0, 1);
    }

    static mat2x2_t zero() {
        return mat2x2_t(0, 0,
                        0, 0);
    }

    static mat2x2_t rotation(T angle) {
        auto cosAngle = cos(angle);
        auto sinAngle = sin(angle);

        return mat2x2_t( cosAngle, sinAngle,
                        -sinAngle, cosAngle);
    }

    static mat2x2_t scale(T sx, T sy) {
        return mat2x2_t(sx, 0,
                        0,  sy);
    }

    static mat2x2_t scale(const vec2_t<T>& s) {
        return mat2x2_t(s.x, 0,
                        0,   s.y);
    }
};

template<class T>
mat2x2_t<T> transpose(const mat2x2_t<T>& mat) {
    return mat2x2_t<T>(mat.m11, mat.m21,
                       mat.m12, mat.m22);
}
