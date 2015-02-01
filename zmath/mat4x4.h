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
struct mat4x4_t {
    union {
        struct {
            T m11, m12, m13, m14,
              m21, m22, m23, m24,
              m31, m32, m33, m34,
              m41, m42, m43, m44;
        };

        T m[4][4];
    };

    // Constructors
    mat4x4_t() {}
    mat4x4_t(T m11, T m12, T m13, T m14,
             T m21, T m22, T m23, T m24,
             T m31, T m32, T m33, T m34,
             T m41, T m42, T m43, T m44) :
        m11(m11), m12(m12), m13(m13), m14(m14),
        m21(m21), m22(m22), m23(m23), m24(m24),
        m31(m31), m32(m32), m33(m33), m34(m34),
        m41(m41), m42(m42), m43(m43), m44(m44) {}
    explicit mat4x4_t(const mat3x3_t<T>& mat) :
        m11(mat.m11), m12(mat.m12), m13(mat.m13), m14(0),
        m21(mat.m21), m22(mat.m22), m23(mat.m23), m24(0),
        m31(mat.m31), m32(mat.m32), m33(mat.m33), m34(0),
        m41(0),       m42(0),       m43(0),       m44(0) {}
    explicit mat4x4_t(const quat_t<T>& q) :
        m11(1 - 2 * (q.y * q.y + q.z * q.z)), m12(2 * (q.x * q.y - q.z * q.w)),     m13(2 * (q.x * q.z + q.y * q.w)),     m14(0),
        m21(2 * (q.x * q.y + q.z * q.w)),     m22(1 - 2 * (q.x * q.x + q.z * q.z)), m23(2 * (q.y * q.z - q.x * q.w)),     m24(0),
        m31(2 * (q.x * q.z - q.y * q.w)),     m32(2 * (q.y * q.z + q.x * q.w)),     m33(1 - 2 * (q.x * q.x + q.y * q.y)), m34(0),
        m41(0),                               m42(0),                               m43(0),                               m44(1) {}
    mat4x4_t(const quat_t<T>& q, const vec3_t<T>& pos) :
        m11(1 - 2 * (q.y * q.y + q.z * q.z)), m12(2 * (q.x * q.y - q.z * q.w)),     m13(2 * (q.x * q.z + q.y * q.w)),     m14(0),
        m21(2 * (q.x * q.y + q.z * q.w)),     m22(1 - 2 * (q.x * q.x + q.z * q.z)), m23(2 * (q.y * q.z - q.x * q.w)),     m24(0),
        m31(2 * (q.x * q.z - q.y * q.w)),     m32(2 * (q.y * q.z + q.x * q.w)),     m33(1 - 2 * (q.x * q.x + q.y * q.y)), m34(0),
        m41(pos.x),                           m42(pos.y),                           m43(pos.z),                           m44(1) {}
    explicit mat4x4_t(const T* p) :
        m11(p[0]),  m12(p[1]),  m13(p[2]),  m14(p[3]),
        m21(p[4]),  m22(p[5]),  m23(p[6]),  m24(p[7]),
        m31(p[8]),  m32(p[9]),  m33(p[10]), m34(p[11]),
        m41(p[12]), m42(p[13]), m43(p[14]), m44(p[15]) {}

    // Unary operators
    mat4x4_t operator - () const {
        return mat4x4_t(-m11, -m12, -m13, -m14,
                        -m21, -m22, -m23, -m24,
                        -m31, -m32, -m33, -m34,
                        -m41, -m42, -m43, -m44);
    }

    mat4x4_t operator ! () const {
        auto c11 =  det3x3(m22, m23, m24, m32, m33, m34, m42, m43, m44);
        auto c12 = -det3x3(m12, m13, m14, m32, m33, m34, m42, m43, m44);
        auto c13 =  det3x3(m12, m13, m14, m22, m23, m24, m42, m43, m44);
        auto c14 = -det3x3(m12, m13, m14, m22, m23, m24, m32, m33, m34);
        auto det = m11 * c11 + m21 * c12 + m31 * c13 + m41 * c14;
        assert(fabs(det) > std::numeric_limits<T>::epsilon());
        return mat4x4_t( c11 / det,                                                  c12 / det,                                                  c13 / det,                                                  c14 / det,
                        -det3x3(m21, m23, m24, m31, m33, m34, m41, m43, m44) / det,  det3x3(m11, m13, m14, m31, m33, m34, m41, m43, m44) / det, -det3x3(m11, m13, m14, m21, m23, m24, m41, m43, m44) / det,  det3x3(m11, m13, m14, m21, m23, m24, m31, m33, m34) / det,
                         det3x3(m21, m22, m24, m31, m32, m34, m41, m42, m44) / det, -det3x3(m11, m12, m14, m31, m32, m34, m41, m42, m44) / det,  det3x3(m11, m12, m14, m21, m22, m24, m41, m42, m44) / det, -det3x3(m11, m12, m14, m21, m22, m24, m31, m32, m34) / det,
                        -det3x3(m21, m22, m23, m31, m32, m33, m41, m42, m43) / det,  det3x3(m11, m12, m13, m31, m32, m33, m41, m42, m43) / det, -det3x3(m11, m12, m13, m21, m22, m23, m41, m42, m43) / det,  det3x3(m11, m12, m13, m21, m22, m23, m31, m32, m33) / det);
    }

    // Binary operators
    mat4x4_t operator + (const mat4x4_t& mat) const {
        return mat4x4_t(m11 + mat.m11, m12 + mat.m12, m13 + mat.m13, m14 + mat.m14,
                        m21 + mat.m21, m22 + mat.m22, m23 + mat.m23, m24 + mat.m24,
                        m31 + mat.m31, m32 + mat.m32, m33 + mat.m33, m34 + mat.m34,
                        m41 + mat.m41, m42 + mat.m42, m43 + mat.m43, m44 + mat.m44);
    }

    mat4x4_t operator - (const mat4x4_t& mat) const {
        return mat4x4_t(m11 - mat.m11, m12 - mat.m12, m13 - mat.m13, m14 - mat.m14,
                        m21 - mat.m21, m22 - mat.m22, m23 - mat.m23, m24 - mat.m24,
                        m31 - mat.m31, m32 - mat.m32, m33 - mat.m33, m34 - mat.m34,
                        m41 - mat.m41, m42 - mat.m42, m43 - mat.m43, m44 - mat.m44);
    }

    mat4x4_t operator * (const mat4x4_t& mat) const {
        mat4x4_t tmp;

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                tmp.m[i][j] = 0;

                for (int k = 0; k < 4; ++k) {
                    tmp.m[i][j] += m[i][k] * mat.m[k][j];
                }
            }
        }

        return tmp;
    }

    mat4x4_t operator * (T f) const {
        return mat4x4_t(m11 * f, m12 * f, m13 * f, m14 * f,
                        m21 * f, m22 * f, m23 * f, m24 * f,
                        m31 * f, m32 * f, m33 * f, m34 * f,
                        m41 * f, m42 * f, m43 * f, m44 * f);
    }

    friend mat4x4_t operator * (T f, const mat4x4_t& mat) {
        return mat4x4_t(mat.m11 * f, mat.m12 * f, mat.m13 * f, mat.m14 * f,
                        mat.m21 * f, mat.m22 * f, mat.m23 * f, mat.m24 * f,
                        mat.m31 * f, mat.m32 * f, mat.m33 * f, mat.m34 * f,
                        mat.m41 * f, mat.m42 * f, mat.m43 * f, mat.m44 * f);
    }

    mat4x4_t operator / (T f) const {
        assert(fabs(f) > std::numeric_limits<T>::epsilon());
        return mat4x4_t(m11 / f, m12 / f, m13 / f, m14 / f,
                        m21 / f, m22 / f, m23 / f, m24 / f,
                        m31 / f, m32 / f, m33 / f, m34 / f,
                        m41 / f, m42 / f, m43 / f, m44 / f);
    }

    mat4x4_t& operator *= (T f) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                m[i][j] *= f;
            }
        }

        return *this;
    }

    mat4x4_t& operator /= (T f) {
        assert(fabs(f) > std::numeric_limits<T>::epsilon());

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                m[i][j] /= f;
            }
        }

        return *this;
    }

    mat4x4_t& operator += (const mat4x4_t& mat) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                m[i][j] += mat.m[i][j];
            }
        }

        return *this;
    }

    mat4x4_t& operator -= (const mat4x4_t& mat) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                m[i][j] -= mat.m[i][j];
            }
        }

        return *this;
    }

    mat4x4_t& operator *= (const mat4x4_t& mat) {
        mat4x4_t tmp;

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                tmp.m[i][j] = 0;

                for (int k = 0; k < 4; ++k) {
                    tmp.m[i][j] += m[i][k] * mat.m[k][j];
                }
            }
        }

        *this = tmp;
        return *this;
    }

    bool operator == (const mat4x4_t& mat) const {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (m[i][j] != mat.m[i][j]) {
                    return false;
                }
            }
        }

        return true;
    }

    bool operator != (const mat4x4_t& mat) const {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
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

    T (&operator [] (int row))[4] {
        assert(row >= 0 && row < 4);
        return m[row];
    }

    vec4_t<T> row(int index) const {
        assert(index >= 0 && index < 4);
        return vec4_t<T>(m[index][0], m[index][1], m[index][2], m[index][3]);
    }

    vec4_t<T> column(int index) const {
        assert(index >= 0 && index < 4);
        return vec4_t<T>(m[0][index], m[1][index], m[2][index], m[3][index]);
    }

    T determinant() const {
        return det4x4(m11, m12, m13, m14,
                      m21, m22, m23, m24,
                      m31, m32, m33, m34,
                      m41, m42, m43, m44);
    }

    static mat4x4_t identity() {
        return mat4x4_t(1, 0, 0, 0,
                        0, 1, 0, 0,
                        0, 0, 1, 0,
                        0, 0, 0, 1);
    }

    static mat4x4_t zero() {
        return mat4x4_t(0, 0, 0, 0,
                        0, 0, 0, 0,
                        0, 0, 0, 0,
                        0, 0, 0, 0);
    }

    static mat4x4_t rotation(const vec3_t<T>& axis, T angle) {
        auto ca = cos(angle);
        auto sa = sin(angle);
        auto dir = normalize(axis);
        auto g = 1 - ca;
        return mat4x4_t(dir.x * dir.x * g + ca,         dir.x * dir.y * g - dir.z * sa, dir.x * dir.z * g + dir.y * sa, 0,
                        dir.y * dir.x * g + dir.z * sa, dir.y * dir.y * g + ca,         dir.y * dir.z * g - dir.x * sa, 0,
                        dir.z * dir.x * g - dir.y * sa, dir.z * dir.y * g + dir.x * sa, dir.z * dir.z * g + ca,         0,
                        0,                              0,                              0,                              1);
    }

    static mat4x4_t rotation(T pitch, T yaw, T roll) {
        auto sx = sin(pitch);
        auto cx = cos(pitch);
        auto sy = sin(yaw);
        auto cy = cos(yaw);
        auto sz = sin(roll);
        auto cz = cos(roll);
        auto c1 = cy * -sz;
        auto c2 = sy *  sz;
        return mat4x4_t( cy * cz, (c1 * cx) + (sy * sx), (c1 * -sx) + (sy * cx), 0,
                         sz,       cz * cx,               cz * -sx,              0,
                        -sy * cz, (c2 * cx) + (cy * sx), (c2 * -sx) + (cy * cx), 0,
                         0,        0,                     0,                     1);
    }

    static mat4x4_t rotationX(T angle) {
        auto cosAngle = cos(angle);
        auto sinAngle = sin(angle);
        return mat4x4_t(1,  0,        0,        0,
                        0,  cosAngle, sinAngle, 0,
                        0, -sinAngle, cosAngle, 0,
                        0,  0,        0,        1);
    }

    static mat4x4_t rotationY(T angle) {
        auto cosAngle = cos(angle);
        auto sinAngle = sin(angle);
        return mat4x4_t(cosAngle, 0, -sinAngle, 0,
                        0,        1,  0,        0,
                        sinAngle, 0,  cosAngle, 0,
                        0,        0,  0,        1);
    }

    static mat4x4_t rotationZ(T angle) {
        auto cosAngle = cos(angle);
        auto sinAngle = sin(angle);
        return mat4x4_t( cosAngle, sinAngle, 0, 0,
                        -sinAngle, cosAngle, 0, 0,
                         0,        0,        1, 0,
                         0,        0,        0, 1);
    }

    static mat4x4_t translation(T dx, T dy, T dz) {
        return mat4x4_t(1,  0,  0,  0,
                        0,  1,  0,  0,
                        0,  0,  1,  0,
                        dx, dy, dz, 1);
    }

    static mat4x4_t translation(const vec3_t<T>& t) {
        return mat4x4_t(1,   0,   0,  0,
                        0,   1,   0,  0,
                        0,   0,   1,  0,
                        t.x, t.y, t.z, 1);
    }

    static mat4x4_t scale(T s) {
        return mat4x4_t(s,  0, 0, 0,
                        0,  s, 0, 0,
                        0,  0, s, 0,
                        0,  0, 0, 1);
    }

    static mat4x4_t scale(T sx, T sy, T sz) {
        return mat4x4_t(sx,  0,  0, 0,
                        0,  sy,  0, 0,
                        0,   0, sz, 0,
                        0,   0,  0, 1);
    }

    static mat4x4_t scale(const vec3_t<T>& s) {
        return mat4x4_t(s.x, 0,   0,   0,
                        0,   s.y, 0,   0,
                        0,   0,   s.z, 0,
                        0,   0,   0,   1);
    }

    static mat4x4_t bias(T width, T height, T bias) {
        assert(width  > std::numeric_limits<T>::epsilon());
        assert(height > std::numeric_limits<T>::epsilon());

        auto offsetX = T(0.5) + (T(0.5) / (T)width);
        auto offsetY = T(0.5) + (T(0.5) / (T)height);
        return mat4x4_t(T(0.5),   0,       0,    0,
                        0,       -T(0.5),  0,    0,
                        0,        0,       1,    0,
                        offsetX,  offsetY, bias, 1);
    }

    static mat4x4_t perspectiveLH(T fov, T aspect, T minZ, T maxZ) {
        assert(fabs(maxZ - minZ) > std::numeric_limits<T>::epsilon());
        assert(fabs(sin(fov / 2)) > std::numeric_limits<T>::epsilon());

        auto ctg = cos(fov / 2) / sin(fov / 2);
        auto q = maxZ / (maxZ - minZ);
        return mat4x4_t<T>(ctg/aspect, 0,    0,        0,
                           0,          ctg,  0,        0,
                           0,          0,    q,        1,
                           0,          0,   -2*minZ*q, 0);
    }

    static mat4x4_t perspectiveRH(T fov, T aspect, T minZ, T maxZ) {
        assert(fabs(minZ - maxZ) > std::numeric_limits<T>::epsilon());
        assert(fabs(sin(fov / 2)) > std::numeric_limits<T>::epsilon());

        auto ctg = cos(fov / 2) / sin(fov / 2);
        auto q = maxZ / (minZ - maxZ);
        return mat4x4_t(ctg/aspect, 0,   0,         0,
                        0,          ctg, 0,         0,
                        0,          0,   q,        -1,
                        0,          0,   2*minZ*q,  0);
    }

    static mat4x4_t lookatLH(const vec3_t<T>& eye, const vec3_t<T>& at, const vec3_t<T>& up) {
        auto z_axis = normalize(at - eye);
        auto x_axis = normalize(cross(up, z_axis));
        auto y_axis = normalize(cross(z_axis, x_axis));
        return mat4x4_t( x_axis.x,          y_axis.x,          z_axis.x,         0,
                         x_axis.y,          y_axis.y,          z_axis.y,         0,
                         x_axis.z,          y_axis.z,          z_axis.z,         0,
                        -dot(x_axis, eye), -dot(y_axis, eye), -dot(z_axis, eye), 1);
    }

    static mat4x4_t lookatRH(const vec3_t<T>& eye, const vec3_t<T>& at, const vec3_t<T>& up) {
        auto z_axis = normalize(eye - at);
        auto x_axis = normalize(cross(up, z_axis));
        auto y_axis = normalize(cross(z_axis, x_axis));
        return mat4x4_t( x_axis.x,          y_axis.x,          z_axis.x,         0,
                         x_axis.y,          y_axis.y,          z_axis.y,         0,
                         x_axis.z,          y_axis.z,          z_axis.z,         0,
                        -dot(x_axis, eye), -dot(y_axis, eye), -dot(z_axis, eye), 1);
    }

    static mat4x4_t orthoLH(T width, T height, T minZ, T maxZ) {
        assert(fabs(width) > std::numeric_limits<T>::epsilon());
        assert(fabs(height) > std::numeric_limits<T>::epsilon());
        assert(fabs(minZ - maxZ) > std::numeric_limits<T>::epsilon());

        auto range = 1 / (maxZ - minZ);
        return mat4x4_t(2/width, 0,         0,          0,
                        0,       2/height,  0,          0,
                        0,       0,         range,      0,
                        0,       0,        -range*minZ, 1);
    }

    static mat4x4_t orthoRH(T width, T height, T minZ, T maxZ) {
        assert(fabs(width) > std::numeric_limits<T>::epsilon());
        assert(fabs(height) > std::numeric_limits<T>::epsilon());
        assert(fabs(minZ - maxZ) > std::numeric_limits<T>::epsilon());

        auto range = 1 / (minZ - maxZ);
        return mat4x4_t(2/width, 0,        0,          0,
                        0,       2/height, 0,          0,
                        0,       0,        range,      0,
                        0,       0,        range*minZ, 1);
    }

    static mat4x4_t viewport(int width, int height, int x, int y, T minZ, T maxZ) {
        return mat4x4_t(width/(T)2,      0,               0,           0,
                        0,              -height/(T)2,     0,           0,
                        0,               0,               maxZ - minZ, 0,
                        x + width/(T)2,  y + height/(T)2, minZ,        1);
    }
};

template<class T>
mat4x4_t<T> transpose(const mat4x4_t<T>& mat) {
    return mat4x4_t<T>(mat.m11, mat.m21, mat.m31, mat.m41,
                       mat.m12, mat.m22, mat.m32, mat.m42,
                       mat.m13, mat.m23, mat.m33, mat.m43,
                       mat.m14, mat.m24, mat.m34, mat.m44);
}
