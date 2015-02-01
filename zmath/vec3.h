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
struct vec3_t {
    T x, y, z;

    // Constructors
    vec3_t() {}
    vec3_t(T x, T y, T z) : x(x), y(y), z(z) {}
    vec3_t(const vec2_t<T>& v, T z) : x(v.x), y(v.y), z(z) {}
    vec3_t(T x, const vec2_t<T>& v) : x(x), y(v.x), z(v.y) {}
    explicit vec3_t(const T* p) : x(p[0]), y(p[1]), z(p[2]) {}

    // Unary operators
    vec3_t operator - () const {
        return vec3_t(-x, -y, -z);
    }

    // Binary operators
    vec3_t operator * (T f) const {
        return vec3_t(x * f, y * f, z * f);
    }

    friend vec3_t operator * (T f, const vec3_t& v) {
        return vec3_t(v.x * f, v.y * f, v.z * f);
    }

    vec3_t operator / (T f) const {
        assert(fabs(f) > std::numeric_limits<T>::epsilon());
        return vec3_t(x / f, y / f, z / f);
    }

    vec3_t& operator *= (T f) {
        x *= f;
        y *= f;
        z *= f;
        return *this;
    }

    vec3_t& operator /= (T f) {
        assert(fabs(f) > std::numeric_limits<T>::epsilon());
        x /= f;
        y /= f;
        z /= f;
        return *this;
    }

    vec3_t operator + (const vec3_t& v) const {
        return vec3_t(x + v.x, y + v.y, z + v.z);
    }

    vec3_t operator - (const vec3_t& v) const {
        return vec3_t(x - v.x, y - v.y, z - v.z);
    }

    vec3_t operator * (const vec3_t& v) const {
        return vec3_t(x * v.x, y * v.y, z * v.z);
    }

    vec3_t operator / (const vec3_t& v) const {
        assert(fabs(v.x) > std::numeric_limits<T>::epsilon());
        assert(fabs(v.y) > std::numeric_limits<T>::epsilon());
        assert(fabs(v.z) > std::numeric_limits<T>::epsilon());
        return vec3_t(x / v.x, y / v.y, z / v.z);
    }

    vec3_t& operator += (const vec3_t& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    vec3_t& operator -= (const vec3_t& v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    vec3_t& operator *= (const vec3_t& v) {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        return *this;
    }

    vec3_t& operator /= (const vec3_t& v) {
        assert(fabs(v.x) > std::numeric_limits<T>::epsilon());
        assert(fabs(v.y) > std::numeric_limits<T>::epsilon());
        assert(fabs(v.z) > std::numeric_limits<T>::epsilon());
        x /= v.x;
        y /= v.y;
        z /= v.z;
        return *this;
    }

    vec3_t operator * (const mat3x3_t<T>& m) const {
        return vec3_t(x * m.m11 + y * m.m21 + z * m.m31,
                      x * m.m12 + y * m.m22 + z * m.m32,
                      x * m.m13 + y * m.m23 + z * m.m33);
    }

    vec3_t operator * (const mat4x4_t<T>& m) const {
        auto h = x * m.m14 + y * m.m24 + z * m.m34 + m.m44;
        assert(fabs(h) > std::numeric_limits<T>::epsilon());
        return vec3_t((x * m.m11 + y * m.m21 + z * m.m31 + m.m41) / h,
                      (x * m.m12 + y * m.m22 + z * m.m32 + m.m42) / h,
                      (x * m.m13 + y * m.m23 + z * m.m33 + m.m43) / h);
    }

    vec3_t& operator *= (const mat3x3_t<T>& m) {
        auto vx = x * m.m11 + y * m.m21 + z * m.m31;
        auto vy = x * m.m12 + y * m.m22 + z * m.m32;
        auto vz = x * m.m13 + y * m.m23 + z * m.m33;
        x = vx;
        y = vy;
        z = vz;
        return *this;
    }

    vec3_t& operator *= (const mat4x4_t<T>& m) {
        auto h = x * m.m14 + y * m.m24 + z * m.m34 + m.m44;
        assert(fabs(h) > std::numeric_limits<T>::epsilon());
        auto vx = (x * m.m11 + y * m.m21 + z * m.m31 + m.m41) / h;
        auto vy = (x * m.m12 + y * m.m22 + z * m.m32 + m.m42) / h;
        auto vz = (x * m.m13 + y * m.m23 + z * m.m33 + m.m43) / h;
        x = vx;
        y = vy;
        z = vz;
        return *this;
    }

    bool operator == (const vec3_t& v) const {
        return x == v.x && y == v.y && z == v.z;
    }

    bool operator != (const vec3_t& v) const {
        return x != v.x || y != v.y || z != v.z;
    }

    bool operator < (const vec3_t& v) const {
        return x < v.x && y < v.y && z < v.z;
    }

    T& operator [] (int index) {
        assert(index >= 0 && index <= 2);
        return *(&x + index);
    }

    T operator [] (int index) const {
        assert(index >= 0 && index <= 2);
        return *(&x + index);
    }

    T length() const {
        return sqrt(x*x + y*y + z*z);
    }

    // Swizzles
    vec2_t<T> xx()   const { return vec2_t<T>(x, x);       }
    vec2_t<T> xy()   const { return vec2_t<T>(x, y);       }
    vec2_t<T> xz()   const { return vec2_t<T>(x, z);       }
    vec2_t<T> yx()   const { return vec2_t<T>(y, x);       }
    vec2_t<T> yy()   const { return vec2_t<T>(y, y);       }
    vec2_t<T> yz()   const { return vec2_t<T>(y, z);       }
    vec2_t<T> zx()   const { return vec2_t<T>(z, x);       }
    vec2_t<T> zy()   const { return vec2_t<T>(z, y);       }
    vec2_t<T> zz()   const { return vec2_t<T>(z, z);       }
    vec3_t<T> xxx()  const { return vec3_t<T>(x, x, x);    }
    vec3_t<T> xxy()  const { return vec3_t<T>(x, x, y);    }
    vec3_t<T> xxz()  const { return vec3_t<T>(x, x, z);    }
    vec3_t<T> xyx()  const { return vec3_t<T>(x, y, x);    }
    vec3_t<T> xyy()  const { return vec3_t<T>(x, y, y);    }
    vec3_t<T> xyz()  const { return vec3_t<T>(x, y, z);    }
    vec3_t<T> xzx()  const { return vec3_t<T>(x, z, x);    }
    vec3_t<T> xzy()  const { return vec3_t<T>(x, z, y);    }
    vec3_t<T> xzz()  const { return vec3_t<T>(x, z, z);    }
    vec3_t<T> yxx()  const { return vec3_t<T>(y, x, x);    }
    vec3_t<T> yxy()  const { return vec3_t<T>(y, x, y);    }
    vec3_t<T> yxz()  const { return vec3_t<T>(y, x, z);    }
    vec3_t<T> yyx()  const { return vec3_t<T>(y, y, x);    }
    vec3_t<T> yyy()  const { return vec3_t<T>(y, y, y);    }
    vec3_t<T> yyz()  const { return vec3_t<T>(y, y, z);    }
    vec3_t<T> yzx()  const { return vec3_t<T>(y, z, x);    }
    vec3_t<T> yzy()  const { return vec3_t<T>(y, z, y);    }
    vec3_t<T> yzz()  const { return vec3_t<T>(y, z, z);    }
    vec3_t<T> zxx()  const { return vec3_t<T>(z, x, x);    }
    vec3_t<T> zxy()  const { return vec3_t<T>(z, x, y);    }
    vec3_t<T> zxz()  const { return vec3_t<T>(z, x, z);    }
    vec3_t<T> zyx()  const { return vec3_t<T>(z, y, x);    }
    vec3_t<T> zyy()  const { return vec3_t<T>(z, y, y);    }
    vec3_t<T> zyz()  const { return vec3_t<T>(z, y, z);    }
    vec3_t<T> zzx()  const { return vec3_t<T>(z, z, x);    }
    vec3_t<T> zzy()  const { return vec3_t<T>(z, z, y);    }
    vec3_t<T> zzz()  const { return vec3_t<T>(z, z, z);    }
    vec4_t<T> xxxx() const { return vec4_t<T>(x, x, x, x); }
    vec4_t<T> xxxy() const { return vec4_t<T>(x, x, x, y); }
    vec4_t<T> xxxz() const { return vec4_t<T>(x, x, x, z); }
    vec4_t<T> xxyx() const { return vec4_t<T>(x, x, y, x); }
    vec4_t<T> xxyy() const { return vec4_t<T>(x, x, y, y); }
    vec4_t<T> xxyz() const { return vec4_t<T>(x, x, y, z); }
    vec4_t<T> xxzx() const { return vec4_t<T>(x, x, z, x); }
    vec4_t<T> xxzy() const { return vec4_t<T>(x, x, z, y); }
    vec4_t<T> xxzz() const { return vec4_t<T>(x, x, z, z); }
    vec4_t<T> xyxx() const { return vec4_t<T>(x, y, x, x); }
    vec4_t<T> xyxy() const { return vec4_t<T>(x, y, x, y); }
    vec4_t<T> xyxz() const { return vec4_t<T>(x, y, x, z); }
    vec4_t<T> xyyx() const { return vec4_t<T>(x, y, y, x); }
    vec4_t<T> xyyy() const { return vec4_t<T>(x, y, y, y); }
    vec4_t<T> xyyz() const { return vec4_t<T>(x, y, y, z); }
    vec4_t<T> xyzx() const { return vec4_t<T>(x, y, z, x); }
    vec4_t<T> xyzy() const { return vec4_t<T>(x, y, z, y); }
    vec4_t<T> xyzz() const { return vec4_t<T>(x, y, z, z); }
    vec4_t<T> xzxx() const { return vec4_t<T>(x, z, x, x); }
    vec4_t<T> xzxy() const { return vec4_t<T>(x, z, x, y); }
    vec4_t<T> xzxz() const { return vec4_t<T>(x, z, x, z); }
    vec4_t<T> xzyx() const { return vec4_t<T>(x, z, y, x); }
    vec4_t<T> xzyy() const { return vec4_t<T>(x, z, y, y); }
    vec4_t<T> xzyz() const { return vec4_t<T>(x, z, y, z); }
    vec4_t<T> xzzx() const { return vec4_t<T>(x, z, z, x); }
    vec4_t<T> xzzy() const { return vec4_t<T>(x, z, z, y); }
    vec4_t<T> xzzz() const { return vec4_t<T>(x, z, z, z); }
    vec4_t<T> yxxx() const { return vec4_t<T>(y, x, x, x); }
    vec4_t<T> yxxy() const { return vec4_t<T>(y, x, x, y); }
    vec4_t<T> yxxz() const { return vec4_t<T>(y, x, x, z); }
    vec4_t<T> yxyx() const { return vec4_t<T>(y, x, y, x); }
    vec4_t<T> yxyy() const { return vec4_t<T>(y, x, y, y); }
    vec4_t<T> yxyz() const { return vec4_t<T>(y, x, y, z); }
    vec4_t<T> yxzx() const { return vec4_t<T>(y, x, z, x); }
    vec4_t<T> yxzy() const { return vec4_t<T>(y, x, z, y); }
    vec4_t<T> yxzz() const { return vec4_t<T>(y, x, z, z); }
    vec4_t<T> yyxx() const { return vec4_t<T>(y, y, x, x); }
    vec4_t<T> yyxy() const { return vec4_t<T>(y, y, x, y); }
    vec4_t<T> yyxz() const { return vec4_t<T>(y, y, x, z); }
    vec4_t<T> yyyx() const { return vec4_t<T>(y, y, y, x); }
    vec4_t<T> yyyy() const { return vec4_t<T>(y, y, y, y); }
    vec4_t<T> yyyz() const { return vec4_t<T>(y, y, y, z); }
    vec4_t<T> yyzx() const { return vec4_t<T>(y, y, z, x); }
    vec4_t<T> yyzy() const { return vec4_t<T>(y, y, z, y); }
    vec4_t<T> yyzz() const { return vec4_t<T>(y, y, z, z); }
    vec4_t<T> yzxx() const { return vec4_t<T>(y, z, x, x); }
    vec4_t<T> yzxy() const { return vec4_t<T>(y, z, x, y); }
    vec4_t<T> yzxz() const { return vec4_t<T>(y, z, x, z); }
    vec4_t<T> yzyx() const { return vec4_t<T>(y, z, y, x); }
    vec4_t<T> yzyy() const { return vec4_t<T>(y, z, y, y); }
    vec4_t<T> yzyz() const { return vec4_t<T>(y, z, y, z); }
    vec4_t<T> yzzx() const { return vec4_t<T>(y, z, z, x); }
    vec4_t<T> yzzy() const { return vec4_t<T>(y, z, z, y); }
    vec4_t<T> yzzz() const { return vec4_t<T>(y, z, z, z); }
    vec4_t<T> zxxx() const { return vec4_t<T>(z, x, x, x); }
    vec4_t<T> zxxy() const { return vec4_t<T>(z, x, x, y); }
    vec4_t<T> zxxz() const { return vec4_t<T>(z, x, x, z); }
    vec4_t<T> zxyx() const { return vec4_t<T>(z, x, y, x); }
    vec4_t<T> zxyy() const { return vec4_t<T>(z, x, y, y); }
    vec4_t<T> zxyz() const { return vec4_t<T>(z, x, y, z); }
    vec4_t<T> zxzx() const { return vec4_t<T>(z, x, z, x); }
    vec4_t<T> zxzy() const { return vec4_t<T>(z, x, z, y); }
    vec4_t<T> zxzz() const { return vec4_t<T>(z, x, z, z); }
    vec4_t<T> zyxx() const { return vec4_t<T>(z, y, x, x); }
    vec4_t<T> zyxy() const { return vec4_t<T>(z, y, x, y); }
    vec4_t<T> zyxz() const { return vec4_t<T>(z, y, x, z); }
    vec4_t<T> zyyx() const { return vec4_t<T>(z, y, y, x); }
    vec4_t<T> zyyy() const { return vec4_t<T>(z, y, y, y); }
    vec4_t<T> zyyz() const { return vec4_t<T>(z, y, y, z); }
    vec4_t<T> zyzx() const { return vec4_t<T>(z, y, z, x); }
    vec4_t<T> zyzy() const { return vec4_t<T>(z, y, z, y); }
    vec4_t<T> zyzz() const { return vec4_t<T>(z, y, z, z); }
    vec4_t<T> zzxx() const { return vec4_t<T>(z, z, x, x); }
    vec4_t<T> zzxy() const { return vec4_t<T>(z, z, x, y); }
    vec4_t<T> zzxz() const { return vec4_t<T>(z, z, x, z); }
    vec4_t<T> zzyx() const { return vec4_t<T>(z, z, y, x); }
    vec4_t<T> zzyy() const { return vec4_t<T>(z, z, y, y); }
    vec4_t<T> zzyz() const { return vec4_t<T>(z, z, y, z); }
    vec4_t<T> zzzx() const { return vec4_t<T>(z, z, z, x); }
    vec4_t<T> zzzy() const { return vec4_t<T>(z, z, z, y); }
    vec4_t<T> zzzz() const { return vec4_t<T>(z, z, z, z); }
};

template<class T>
T dot(const vec3_t<T>& v1, const vec3_t<T>& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

template<class T>
vec3_t<T> cross(const vec3_t<T>& v1, const vec3_t<T>& v2) {
    return vec3_t<T>(v1.y * v2.z - v1.z * v2.y,
                     v1.z * v2.x - v1.x * v2.z,
                     v1.x * v2.y - v1.y * v2.x);
}

template<class T>
vec3_t<T> normalize(const vec3_t<T>& v) {
    auto m = v.length();

    if (m > std::numeric_limits<T>::epsilon()) {
        m = 1 / m;
    } else {
        m = 0;
    }

    return vec3_t<T>(v.x * m, v.y * m, v.z * m);
}

template<class T>
vec3_t<T> minimize(const vec3_t<T>& v1, const vec3_t<T>& v2) {
    return vec3_t<T>((v1.x < v2.x) ? v1.x : v2.x,
                     (v1.y < v2.y) ? v1.y : v2.y,
                     (v1.z < v2.z) ? v1.z : v2.z);
}

template<class T>
vec3_t<T> maximize(const vec3_t<T>& v1, const vec3_t<T>& v2) {
    return vec3_t<T>((v1.x > v2.x) ? v1.x : v2.x,
                     (v1.y > v2.y) ? v1.y : v2.y,
                     (v1.z > v2.z) ? v1.z : v2.z);
}

template<class T>
T length(const vec3_t<T>& v) {
    return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

template<class T>
T length2(const vec3_t<T>& v) {
    return v.x*v.x + v.y*v.y + v.z*v.z;
}

template<class T>
vec3_t<T> reflect(const vec3_t<T>& v, const vec3_t<T>& n) {
    return v - n * 2 * dot(n, v);
}

template<class T>
vec3_t<T> abs(const vec3_t<T>& v) {
    return vec3_t<T>((v.x < 0) ? -v.x : v.x,
                     (v.y < 0) ? -v.y : v.y,
                     (v.z < 0) ? -v.z : v.z);
}

template<class T>
vec3_t<T> clamp(const vec3_t<T>& v, T min, T max) {
    return vec3_t<T>((v.x < min) ? min : ((v.x > max) ? max : v.x),
                     (v.y < min) ? min : ((v.y > max) ? max : v.y),
                     (v.z < min) ? min : ((v.z > max) ? max : v.z));
}

template<class T>
vec3_t<T> clamp(const vec3_t<T>& v, const vec3_t<T>& min, const vec3_t<T>& max) {
    return vec3_t<T>((v.x < min.x) ? min.x : ((v.x > max.x) ? max.x : v.x),
                     (v.y < min.y) ? min.y : ((v.y > max.y) ? max.y : v.y),
                     (v.z < min.z) ? min.z : ((v.z > max.z) ? max.z : v.z));
}

template<class T>
vec3_t<T> lerp(const vec3_t<T>& min, const vec3_t<T>& max, T scale) {
    return vec3_t<T>(min.x + scale * (max.x - min.x),
                     min.y + scale * (max.y - min.y),
                     min.z + scale * (max.z - min.z));
}

template<class T>
vec3_t<T> saturate(const vec3_t<T>& v) {
    return vec3_t<T>((v.x < 0) ? 0 : ((v.x > 1) ? 1 : v.x),
                     (v.y < 0) ? 0 : ((v.y > 1) ? 1 : v.y),
                     (v.z < 0) ? 0 : ((v.z > 1) ? 1 : v.z));
}
