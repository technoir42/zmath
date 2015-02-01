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
struct mat4x3_t {
    union {
        struct {
            T m11, m12, m13,
              m21, m22, m23,
              m31, m32, m33,
              m41, m42, m43;
        };

        T m[4][3];
    };

    // Constructors
    mat4x3_t() {}
    mat4x3_t(T m11, T m12, T m13,
             T m21, T m22, T m23,
             T m31, T m32, T m33,
             T m41, T m42, T m43) :
        m11(m11), m12(m12), m13(m13),
        m21(m21), m22(m22), m23(m23),
        m31(m31), m32(m32), m33(m33),
        m41(m41), m42(m42), m43(m43) {}
    explicit mat4x3_t(const mat3x3_t<T>& mat) :
        m11(mat.m11), m12(mat.m12), m13(mat.m13),
        m21(mat.m21), m22(mat.m22), m23(mat.m23),
        m31(mat.m31), m32(mat.m32), m33(mat.m33),
        m41(0),       m42(0),       m43(0) {}
    explicit mat4x3_t(const quat_t<T>& q) :
        m11(1 - 2 * (q.y * q.y + q.z * q.z)), m12(2 * (q.x * q.y - q.z * q.w)),     m13(2 * (q.x * q.z + q.y * q.w)),
        m21(2 * (q.x * q.y + q.z * q.w)),     m22(1 - 2 * (q.x * q.x + q.z * q.z)), m23(2 * (q.y * q.z - q.x * q.w)),
        m31(2 * (q.x * q.z - q.y * q.w)),     m32(2 * (q.y * q.z + q.x * q.w)),     m33(1 - 2 * (q.x * q.x + q.y * q.y)),
        m41(0),                               m42(0),                               m43(0) {}
    mat4x3_t(const quat_t<T>& q, const vec3_t<T>& pos) :
        m11(1 - 2 * (q.y * q.y + q.z * q.z)), m12(2 * (q.x * q.y - q.z * q.w)),     m13(2 * (q.x * q.z + q.y * q.w)),
        m21(2 * (q.x * q.y + q.z * q.w)),     m22(1 - 2 * (q.x * q.x + q.z * q.z)), m23(2 * (q.y * q.z - q.x * q.w)),
        m31(2 * (q.x * q.z - q.y * q.w)),     m32(2 * (q.y * q.z + q.x * q.w)),     m33(1 - 2 * (q.x * q.x + q.y * q.y)),
        m41(pos.x),                           m42(pos.y),                           m43(pos.z) {}
    explicit mat4x3_t(const T* p) :
        m11(p[0]), m12(p[1]),  m13(p[2]),
        m21(p[3]), m22(p[4]),  m23(p[5]),
        m31(p[6]), m32(p[7]),  m33(p[8]),
        m41(p[9]), m42(p[10]), m43(p[11]) {}

    // Unary operators
    mat4x3_t operator - () const {
        return mat4x3_t(-m11, -m12, -m13,
                        -m21, -m22, -m23,
                        -m31, -m32, -m33,
                        -m41, -m42, -m43);
    }

    // Binary operators
    mat4x3_t operator + (const mat4x3_t& mat) const {
        return mat4x3_t(m11 + mat.m11, m12 + mat.m12, m13 + mat.m13,
                        m21 + mat.m21, m22 + mat.m22, m23 + mat.m23,
                        m31 + mat.m31, m32 + mat.m32, m33 + mat.m33,
                        m41 + mat.m41, m42 + mat.m42, m43 + mat.m43);
    }

    mat4x3_t operator - (const mat4x3_t& mat) const {
        return mat4x3_t(m11 - mat.m11, m12 - mat.m12, m13 - mat.m13,
                        m21 - mat.m21, m22 - mat.m22, m23 - mat.m23,
                        m31 - mat.m31, m32 - mat.m32, m33 - mat.m33,
                        m41 - mat.m41, m42 - mat.m42, m43 - mat.m43);
    }

    mat4x3_t operator * (const mat4x3_t& mat) const {
        mat4x3_t tmp;

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 3; ++j) {
                tmp.m[i][j] = 0;

                for (int k = 0; k < 3; ++k) {
                    tmp.m[i][j] += m[i][k] * mat.m[k][j];
                }
            }
        }

        return tmp;
    }

    mat4x3_t operator * (T f) const {
        return mat4x3_t(m11 * f, m12 * f, m13 * f,
                        m21 * f, m22 * f, m23 * f,
                        m31 * f, m32 * f, m33 * f,
                        m41 * f, m42 * f, m43 * f);
    }

    friend mat4x3_t operator * (T f, const mat4x3_t& mat) {
        return mat4x3_t(mat.m11 * f, mat.m12 * f, mat.m13 * f,
                        mat.m21 * f, mat.m22 * f, mat.m23 * f,
                        mat.m31 * f, mat.m32 * f, mat.m33 * f,
                        mat.m41 * f, mat.m42 * f, mat.m43 * f);
    }

    mat4x3_t operator / (T f) const {
        assert(fabs(f) > std::numeric_limits<T>::epsilon());
        return mat4x3_t(m11 / f, m12 / f, m13 / f,
                        m21 / f, m22 / f, m23 / f,
                        m31 / f, m32 / f, m33 / f,
                        m41 / f, m42 / f, m43 / f);
    }

    mat4x3_t& operator *= (T f) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 3; ++j) {
                m[i][j] *= f;
            }
        }

        return *this;
    }

    mat4x3_t& operator /= (T f) {
        assert(fabs(f) > std::numeric_limits<T>::epsilon());

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 3; ++j) {
                m[i][j] /= f;
            }
        }

        return *this;
    }

    mat4x3_t& operator += (const mat4x3_t& mat) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 3; ++j) {
                m[i][j] += mat.m[i][j];
            }
        }

        return *this;
    }

    mat4x3_t& operator -= (const mat4x3_t& mat) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 3; ++j) {
                m[i][j] -= mat.m[i][j];
            }
        }

        return *this;
    }

    mat4x3_t& operator *= (const mat4x3_t& mat) {
        mat4x3_t tmp;

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 3; ++j) {
                tmp.m[i][j] = 0;

                for (int k = 0; k < 3; ++k) {
                    tmp.m[i][j] += m[i][k] * mat.m[k][j];
                }
            }
        }

        *this = tmp;
        return *this;
    }

    bool operator == (const mat4x3_t& mat) const {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (m[i][j] != mat.m[i][j]) {
                    return false;
                }
            }
        }

        return true;
    }

    bool operator != (const mat4x3_t& mat) const {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 3; ++j) {
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

    T (&operator [] (int row))[3] {
        assert(row >= 0 && row < 4);
        return m[row];
    }

    vec3_t<T> row(int index) const {
        assert(index >= 0 && index < 4);
        return vec3_t<T>(m[index][0], m[index][1], m[index][2]);
    }

    vec4_t<T> column(int index) const {
        assert(index >= 0 && index < 3);
        return vec4_t<T>(m[0][index], m[1][index], m[2][index], m[3][index]);
    }

    static mat4x3_t identity() {
        return mat4x3_t(1, 0, 0,
                        0, 1, 0,
                        0, 0, 1,
                        0, 0, 0);
    }

    static mat4x3_t zero() {
        return mat4x3_t(0, 0, 0,
                        0, 0, 0,
                        0, 0, 0,
                        0, 0, 0);
    }

    static mat4x3_t rotation(const vec3_t<T>& axis, T angle) {
        auto ca = cos(angle);
        auto sa = sin(angle);
        auto dir = normalize(axis);
        auto g = 1 - ca;
        return mat4x3_t(dir.x * dir.x * g + ca,         dir.x * dir.y * g - dir.z * sa, dir.x * dir.z * g + dir.y * sa,
                        dir.y * dir.x * g + dir.z * sa, dir.y * dir.y * g + ca,         dir.y * dir.z * g - dir.x * sa,
                        dir.z * dir.x * g - dir.y * sa, dir.z * dir.y * g + dir.x * sa, dir.z * dir.z * g + ca,
                        0,                              0,                              0                             );
    }

    static mat4x3_t rotation(T pitch, T yaw, T roll) {
        auto sx = sin(pitch);
        auto cx = cos(pitch);
        auto sy = sin(yaw);
        auto cy = cos(yaw);
        auto sz = sin(roll);
        auto cz = cos(roll);
        auto c1 = cy * -sz;
        auto c2 = sy *  sz;
        return mat4x3_t( cy * cz, (c1 * cx) + (sy * sx), (c1 * -sx) + (sy * cx),
                         sz,       cz * cx,               cz * -sx,
                        -sy * cz, (c2 * cx) + (cy * sx), (c2 * -sx) + (cy * cx),
                         0,        0,                     0                    );
    }

    static mat4x3_t rotationX(T angle) {
        auto cosAngle = cos(angle);
        auto sinAngle = sin(angle);
        return mat4x3_t(1,  0,        0,
                        0,  cosAngle, sinAngle,
                        0, -sinAngle, cosAngle,
                        0,  0,        0       );
    }

    static mat4x3_t rotationY(T angle) {
        auto cosAngle = cos(angle);
        auto sinAngle = sin(angle);
        return mat4x3_t(cosAngle, 0, -sinAngle,
                        0,        1,  0,
                        sinAngle, 0,  cosAngle,
                        0,        0,  0       );
    }

    static mat4x3_t rotationZ(T angle) {
        auto cosAngle = cos(angle);
        auto sinAngle = sin(angle);
        return mat4x3_t( cosAngle, sinAngle, 0,
                        -sinAngle, cosAngle, 0,
                         0,        0,        1,
                         0,        0,        0);
    }

    static mat4x3_t translation(T dx, T dy, T dz) {
        return mat4x3_t(1,  0,  0,
                        0,  1,  0,
                        0,  0,  1,
                        dx, dy, dz);
    }

    static mat4x3_t translation(const vec3_t<T>& t) {
        return mat4x3_t(1,   0,   0,
                        0,   1,   0,
                        0,   0,   1,
                        t.x, t.y, t.z);
    }

    static mat4x3_t scale(T s) {
        return mat4x3_t(s,  0, 0,
                        0,  s, 0,
                        0,  0, s,
                        0,  0, 0);
    }

    static mat4x3_t scale(T sx, T sy, T sz) {
        return mat4x3_t(sx,  0,  0,
                        0,  sy,  0,
                        0,   0, sz,
                        0,   0,  0);
    }

    static mat4x3_t scale(const vec3_t<T>& s) {
        return mat4x3_t(s.x, 0,   0,
                        0,   s.y, 0,
                        0,   0,   s.z,
                        0,   0,   0  );
    }
};
