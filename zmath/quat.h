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
struct quat_t {
    T x, y, z, w;

    quat_t() : x(0), y(0), z(0), w(1) {}
    quat_t(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
    explicit quat_t(const T* p) : x(p[0]), y(p[1]), z(p[2]), w(p[3]) {}

    // Unary operators
    quat_t operator - () const {
        return quat_t(-x, -y, -z, -w);
    }

    quat_t operator ! () const {
        return quat_t(-x, -y, -z, w);
    }

    // Binary operators
    quat_t operator * (T f) const {
        return quat_t(x * f, y * f, z * f, w * f);
    }

    friend quat_t operator * (T f, const quat_t& q) {
        return quat_t(q.x * f, q.y * f, q.z * f, q.w * f);
    }

    quat_t operator / (T f) const {
        assert(fabs(f) > std::numeric_limits<T>::epsilon());
        return quat_t(x / f, y / f, z / f, w / f);
    }

    quat_t& operator *= (T f) {
        x *= f;
        y *= f;
        z *= f;
        w *= f;
        return *this;
    }

    quat_t& operator /= (T f) {
        assert(fabs(f) > std::numeric_limits<T>::epsilon());
        x /= f;
        y /= f;
        z /= f;
        w /= f;
        return *this;
    }

    quat_t operator + (const quat_t& q) const {
        return quat_t(x + q.x, y + q.y, z + q.z, w + q.w);
    }

    quat_t operator - (const quat_t& q) const {
        return quat_t(x - q.x, y - q.y, z - q.z, w - q.w);
    }

    quat_t operator * (const quat_t& q) const {
        return quat_t(w * q.x + x * q.w + y * q.z - z * q.y,
                      w * q.y - x * q.z + y * q.w + z * q.x,
                      w * q.z + x * q.y - y * q.x + z * q.w,
                      w * q.w - x * q.x - y * q.y - z * q.z);
    }

    quat_t operator / (const quat_t& q) const {
        auto m = dot(q, q);
        assert(m > std::numeric_limits<T>::epsilon());
        return quat_t((-w * q.x + x * q.w - y * q.z + z * q.y) / m,
                      (-w * q.y + x * q.z + y * q.w - z * q.x) / m,
                      (-w * q.z - x * q.y + y * q.x + z * q.w) / m,
                      ( w * q.w + x * q.x + y * q.y + z * q.z) / m);
    }

    quat_t& operator += (const quat_t& q) {
        x += q.x;
        y += q.y;
        z += q.z;
        w += q.w;
        return *this;
    }

    quat_t& operator -= (const quat_t& q) {
        x -= q.x;
        y -= q.y;
        z -= q.z;
        w -= q.w;
        return *this;
    }

    quat_t& operator *= (const quat_t& q) {
        auto qx = w * q.x + x * q.w + y * q.z - z * q.y;
        auto qy = w * q.y + y * q.w + z * q.x - x * q.z;
        auto qz = w * q.z + z * q.w + x * q.y - y * q.x;
        auto qw = w * q.w - x * q.x - y * q.y - z * q.z;
        x = qx; y = qy; z = qz; w = qw;
        return *this;
    }

    // Comparison operators
    bool operator == (const quat_t& q) const {
        return x == q.x && y == q.y && z == q.z && w == q.w;
    }

    bool operator != (const quat_t& q) const {
        return x != q.x || y != q.y || z != q.z || w != q.w;
    }

    T length() const {
        return sqrt(x*x + y*y + z*z + w*w);
    }

    static quat_t rotation(T pitch, T yaw, T roll) {
        return rotation_y(yaw) * rotation_x(pitch) * rotation_z(roll);
    }

    static quat_t rotation_axis(const vec3_t<T>& v, T angle) {
        auto sine = sin(angle / 2);
        return quat_t(sine * v.x, sine * v.y, sine * v.z, cos(angle / 2));
    }

    static quat_t rotation_x(T angle) {
        return quat_t(sin(angle / 2), 0, 0, cos(angle / 2));
    }

    static quat_t rotation_y(T angle) {
        return quat_t(0, sin(angle / 2), 0, cos(angle / 2));
    }

    static quat_t rotation_z(T angle) {
        return quat_t(0, 0, sin(angle / 2), cos(angle / 2));
    }

    static quat_t shortest_arc(const vec3_t<T>& from, const vec3_t<T>& to) {
        auto c = cross(from, to);
        quat_t q(c.x, c.y, c.z, dot(from, to) + 1);
        q = normalize(q);

        if (q.w <= std::numeric_limits<T>::min()) {
            if (from.z*from.z > from.x*from.x) {
                q.x =  0;
                q.y =  from.z;
                q.z = -from.y;
            } else {
                q.x =  from.y;
                q.y = -from.x;
                q.z =  0;
            }
        }

        return normalize(q);
    }

    static quat_t from_matrix(const mat3x3_t<T>& m) {
        auto tr = m.m11 + m.m22 + m.m33;
        T qx, qy, qz, qw;

        if (tr > 0) {
            auto s = sqrt(tr + 1) * 2;
            qw = s / 4;
            qx = (m.m32 - m.m23) / s;
            qy = (m.m13 - m.m31) / s;
            qz = (m.m21 - m.m12) / s;
        } else if (m.m11 > m.m22 && m.m11 > m.m33) {
            auto s = sqrt(m.m11 - m.m22 - m.m33 + 1) * 2;
            qw = (m.m32 - m.m23) / s;
            qx = s / 4;
            qy = (m.m12 + m.m21) / s;
            qz = (m.m13 + m.m31) / s;
        } else if (m.m22 > m.m33) {
            auto s = sqrt(m.m22 - m.m11 - m.m33 + 1) * 2;
            qw = (m.m13 - m.m31) / s;
            qx = (m.m12 + m.m21) / s;
            qy = s / 4;
            qz = (m.m23 + m.m32) / s;
        } else {
            auto s = sqrt(m.m33 - m.m11 - m.m22 + 1) * 2;
            qw = (m.m21 - m.m12) / s;
            qx = (m.m13 + m.m31) / s;
            qy = (m.m23 + m.m32) / s;
            qz = s / 4;
        }

        return quat_t(qx, qy, qz, qw);
    }

    static quat_t from_matrix(const mat4x4_t<T>& m) {
        auto tr = m.m11 + m.m22 + m.m33;
        T qx, qy, qz, qw;

        if (tr > 0) {
            auto s = sqrt(tr + 1) * 2;
            qw = s / 4;
            qx = (m.m32 - m.m23) / s;
            qy = (m.m13 - m.m31) / s;
            qz = (m.m21 - m.m12) / s;
        } else if (m.m11 > m.m22 && m.m11 > m.m33) {
            auto s = sqrt(m.m11 - m.m22 - m.m33 + 1) * 2;
            qw = (m.m32 - m.m23) / s;
            qx = s / 4;
            qy = (m.m12 + m.m21) / s;
            qz = (m.m13 + m.m31) / s;
        } else if (m.m22 > m.m33) {
            auto s = sqrt(m.m22 - m.m11 - m.m33 + 1) * 2;
            qw = (m.m13 - m.m31) / s;
            qx = (m.m12 + m.m21) / s;
            qy = s / 4;
            qz = (m.m23 + m.m32) / s;
        } else {
            auto s = sqrt(m.m33 - m.m11 - m.m22 + 1) * 2;
            qw = (m.m21 - m.m12) / s;
            qx = (m.m13 + m.m31) / s;
            qy = (m.m23 + m.m32) / s;
            qz = s / 4;
        }

        return quat_t(qx, qy, qz, qw);
    }

    void getAngles(T& pitch, T& yaw, T& roll) {
        pitch = atan2(2 * (w*x + y*z), 1 - 2 * (x*x + y*y));
        yaw   = asin( 2 * (w*y - z*x));
        roll  = atan2(2 * (w*z + x*y), 1 - 2 * (y*y + z*z));
    }

    enum {
        PACK_COEFF_YZ = 1 << 20,
        PACK_COEFF_X  = 1 << 21,
    };

    long long pack() const {
        int w_sign = (w >= 0) ? 1 : -1;

        long long xbits = int(x * PACK_COEFF_X)  * w_sign & ((1 << 22) - 1);
        long long ybits = int(y * PACK_COEFF_YZ) * w_sign & ((1 << 21) - 1);
        long long zbits = int(z * PACK_COEFF_YZ) * w_sign & ((1 << 21) - 1);
        return zbits | (ybits << 21) | (xbits << 42);
    }

    void setPacked(long long packed) {
        const int mask = (1 << 21) - 1;

        // 22 bits + 21 bit + 21 bit
        x = T(packed >> 42) / (T)PACK_COEFF_X;
        y = T((packed >> 21) & mask) / (T)PACK_COEFF_YZ;
        z = T(packed & mask) / (T)PACK_COEFF_YZ;
        w = sqrt(1 - (x*x + y*y + z*z));
    }

    static quat_t slerp(const quat_t& from, const quat_t& to, T scale) {
        if (scale <= T(0)) {
            return from;
        }

        if (scale >= T(1)) {
            return to;
        }

        T cosphi = from.x*to.x + from.y*to.y + from.z*to.z + from.w*to.w;
        quat_t temp = to;

        if (cosphi < T(0)) {
            temp = -temp;
            cosphi = -cosphi;
        }

        T scale0, scale1;

        if ((T(1) - cosphi) > T(1e-6)) {
            T phi = acos(cosphi);
            T sinphi = T(1) / sin(phi);
            scale0 = sin((T(1) - scale) * phi) * sinphi;
            scale1 = sin(scale * phi) * sinphi;
        } else {
            scale0 = T(1) - scale;
            scale1 = scale;
        }

        return scale0 * from + scale1 * temp;
    }
};

template<class T>
T dot(const quat_t<T>& q1, const quat_t<T>& q2) {
    return q1.x*q2.x + q1.y*q2.y + q1.z*q2.z + q1.w*q2.w;
}

template<class T>
T length(const quat_t<T>& q) {
    return q.length();
}

template<class T>
quat_t<T> normalize(const quat_t<T>& q) {
    auto m = q.length();

    if (m > std::numeric_limits<T>::epsilon()) {
        m = 1 / m;
    } else {
        m = 0;
    }

    return quat_t<T>(q.x * m, q.y * m, q.z * m, q.w * m);
}
