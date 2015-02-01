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
struct vec4_t {
    T x, y, z, w;

    // Constructors
    vec4_t() {}
    vec4_t(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
    vec4_t(const vec2_t<T>& v, T z, T w) : x(v.x), y(v.y), z(z), w(w) {}
    vec4_t(T x, const vec2_t<T>& v, T w) : x(x), y(v.x), z(v.y), w(w) {}
    vec4_t(T x, T y, const vec2_t<T>& v) : x(x), y(y), z(v.x), w(v.y) {}
    vec4_t(const vec3_t<T>& v, T w) : x(v.x), y(v.y), z(v.z), w(w) {}
    vec4_t(T x, const vec3_t<T>& v) : x(x), y(v.x), z(v.y), w(v.z) {}
    explicit vec4_t(const T* p) : x(p[0]), y(p[1]), z(p[2]), w(p[3]) {}

    // Unary operators
    vec4_t operator - () const {
        return vec4_t(-x, -y, -z, -w);
    }

    // Binary operators
    vec4_t operator * (T f) const {
        return vec4_t(x * f, y * f, z * f, w * f);
    }

    friend vec4_t operator * (T f, const vec4_t& v) {
        return vec4_t(v.x * f, v.y * f, v.z * f, v.w * f);
    }

    vec4_t operator / (T f) const {
        assert(fabs(f) > std::numeric_limits<T>::epsilon());
        return vec4_t(x / f, y / f, z / f, w / f);
    }

    vec4_t& operator *= (T f) {
        x *= f;
        y *= f;
        z *= f;
        w *= f;
        return *this;
    }

    vec4_t& operator /= (T f) {
        assert(fabs(f) > std::numeric_limits<T>::epsilon());
        x /= f;
        y /= f;
        z /= f;
        w /= f;
        return *this;
    }

    vec4_t operator + (const vec4_t& v) const {
        return vec4_t(x + v.x, y + v.y, z + v.z, w + v.w);
    }

    vec4_t operator - (const vec4_t& v) const {
        return vec4_t(x - v.x, y - v.y, z - v.z, w - v.w);
    }

    vec4_t operator * (const vec4_t& v) const {
        return vec4_t(x * v.x, y * v.y, z * v.z, w * v.w);
    }

    vec4_t operator / (const vec4_t& v) const {
        assert(fabs(v.x) > std::numeric_limits<T>::epsilon());
        assert(fabs(v.y) > std::numeric_limits<T>::epsilon());
        assert(fabs(v.z) > std::numeric_limits<T>::epsilon());
        assert(fabs(v.w) > std::numeric_limits<T>::epsilon());
        return vec4_t(x / v.x, y / v.y, z / v.z, w / v.w);
    }

    vec4_t& operator += (const vec4_t& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        w += v.w;
        return *this;
    }

    vec4_t& operator -= (const vec4_t& v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        w -= v.w;
        return *this;
    }

    vec4_t& operator *= (const vec4_t& v) {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        w *= v.w;
        return *this;
    }

    vec4_t& operator /= (const vec4_t& v) {
        assert(fabs(v.x) > std::numeric_limits<T>::epsilon());
        assert(fabs(v.y) > std::numeric_limits<T>::epsilon());
        assert(fabs(v.z) > std::numeric_limits<T>::epsilon());
        assert(fabs(v.w) > std::numeric_limits<T>::epsilon());
        x /= v.x;
        y /= v.y;
        z /= v.z;
        w /= v.w;
        return *this;
    }

    vec4_t operator * (const mat4x4_t<T>& m) const {
        return vec4_t(x * m.m11 + y * m.m21 + z * m.m31 + w * m.m41,
                      x * m.m12 + y * m.m22 + z * m.m32 + w * m.m42,
                      x * m.m13 + y * m.m23 + z * m.m33 + w * m.m43,
                      x * m.m14 + y * m.m24 + z * m.m34 + w * m.m44);
    }

    vec4_t& operator *= (const mat4x4_t<T>& m) {
        auto vx = x * m.m11 + y * m.m21 + z * m.m31 + w * m.m41;
        auto vy = x * m.m12 + y * m.m22 + z * m.m32 + w * m.m42;
        auto vz = x * m.m13 + y * m.m23 + z * m.m33 + w * m.m43;
        auto vw = x * m.m14 + y * m.m24 + z * m.m34 + w * m.m44;
        x = vx;
        y = vy;
        z = vz;
        w = vw;
        return *this;
    }

    bool operator == (const vec4_t& v) const {
        return x == v.x && y == v.y && z == v.z && w == v.w;
    }

    bool operator != (const vec4_t& v) const {
        return x != v.x || y != v.y || z != v.z || w != v.w;
    }

    bool operator < (const vec4_t& v) const {
        return x < v.x && y < v.y && z < v.z && w < v.w;
    }

    T& operator [] (int index) {
        assert(index >= 0 && index <= 3);
        return *(&x + index);
    }

    T operator [] (int index) const {
        assert(index >= 0 && index <= 3);
        return *(&x + index);
    }

    T length() const {
        return sqrt(x*x + y*y + z*z + w*w);
    }

    // Swizzles
    vec2_t<T> xx()   const { return vec2_t<T>(x, x);       }
    vec2_t<T> xy()   const { return vec2_t<T>(x, y);       }
    vec2_t<T> xz()   const { return vec2_t<T>(x, z);       }
    vec2_t<T> xw()   const { return vec2_t<T>(x, w);       }
    vec2_t<T> yx()   const { return vec2_t<T>(y, x);       }
    vec2_t<T> yy()   const { return vec2_t<T>(y, y);       }
    vec2_t<T> yz()   const { return vec2_t<T>(y, z);       }
    vec2_t<T> yw()   const { return vec2_t<T>(y, w);       }
    vec2_t<T> zx()   const { return vec2_t<T>(z, x);       }
    vec2_t<T> zy()   const { return vec2_t<T>(z, y);       }
    vec2_t<T> zz()   const { return vec2_t<T>(z, z);       }
    vec2_t<T> zw()   const { return vec2_t<T>(z, w);       }
    vec2_t<T> wx()   const { return vec2_t<T>(w, x);       }
    vec2_t<T> wy()   const { return vec2_t<T>(w, y);       }
    vec2_t<T> wz()   const { return vec2_t<T>(w, z);       }
    vec2_t<T> ww()   const { return vec2_t<T>(w, w);       }
    vec3_t<T> xxx()  const { return vec3_t<T>(x, x, x);    }
    vec3_t<T> xxy()  const { return vec3_t<T>(x, x, y);    }
    vec3_t<T> xxz()  const { return vec3_t<T>(x, x, z);    }
    vec3_t<T> xxw()  const { return vec3_t<T>(x, x, w);    }
    vec3_t<T> xyx()  const { return vec3_t<T>(x, y, x);    }
    vec3_t<T> xyy()  const { return vec3_t<T>(x, y, y);    }
    vec3_t<T> xyz()  const { return vec3_t<T>(x, y, z);    }
    vec3_t<T> xyw()  const { return vec3_t<T>(x, y, w);    }
    vec3_t<T> xzx()  const { return vec3_t<T>(x, z, x);    }
    vec3_t<T> xzy()  const { return vec3_t<T>(x, z, y);    }
    vec3_t<T> xzz()  const { return vec3_t<T>(x, z, z);    }
    vec3_t<T> xzw()  const { return vec3_t<T>(x, z, w);    }
    vec3_t<T> xwx()  const { return vec3_t<T>(x, w, x);    }
    vec3_t<T> xwy()  const { return vec3_t<T>(x, w, y);    }
    vec3_t<T> xwz()  const { return vec3_t<T>(x, w, z);    }
    vec3_t<T> xww()  const { return vec3_t<T>(x, w, w);    }
    vec3_t<T> yxx()  const { return vec3_t<T>(y, x, x);    }
    vec3_t<T> yxy()  const { return vec3_t<T>(y, x, y);    }
    vec3_t<T> yxz()  const { return vec3_t<T>(y, x, z);    }
    vec3_t<T> yxw()  const { return vec3_t<T>(y, x, w);    }
    vec3_t<T> yyx()  const { return vec3_t<T>(y, y, x);    }
    vec3_t<T> yyy()  const { return vec3_t<T>(y, y, y);    }
    vec3_t<T> yyz()  const { return vec3_t<T>(y, y, z);    }
    vec3_t<T> yyw()  const { return vec3_t<T>(y, y, w);    }
    vec3_t<T> yzx()  const { return vec3_t<T>(y, z, x);    }
    vec3_t<T> yzy()  const { return vec3_t<T>(y, z, y);    }
    vec3_t<T> yzz()  const { return vec3_t<T>(y, z, z);    }
    vec3_t<T> yzw()  const { return vec3_t<T>(y, z, w);    }
    vec3_t<T> ywx()  const { return vec3_t<T>(y, w, x);    }
    vec3_t<T> ywy()  const { return vec3_t<T>(y, w, y);    }
    vec3_t<T> ywz()  const { return vec3_t<T>(y, w, z);    }
    vec3_t<T> yww()  const { return vec3_t<T>(y, w, w);    }
    vec3_t<T> zxx()  const { return vec3_t<T>(z, x, x);    }
    vec3_t<T> zxy()  const { return vec3_t<T>(z, x, y);    }
    vec3_t<T> zxz()  const { return vec3_t<T>(z, x, z);    }
    vec3_t<T> zxw()  const { return vec3_t<T>(z, x, w);    }
    vec3_t<T> zyx()  const { return vec3_t<T>(z, y, x);    }
    vec3_t<T> zyy()  const { return vec3_t<T>(z, y, y);    }
    vec3_t<T> zyz()  const { return vec3_t<T>(z, y, z);    }
    vec3_t<T> zyw()  const { return vec3_t<T>(z, y, w);    }
    vec3_t<T> zzx()  const { return vec3_t<T>(z, z, x);    }
    vec3_t<T> zzy()  const { return vec3_t<T>(z, z, y);    }
    vec3_t<T> zzz()  const { return vec3_t<T>(z, z, z);    }
    vec3_t<T> zzw()  const { return vec3_t<T>(z, z, w);    }
    vec3_t<T> zwx()  const { return vec3_t<T>(z, w, x);    }
    vec3_t<T> zwy()  const { return vec3_t<T>(z, w, y);    }
    vec3_t<T> zwz()  const { return vec3_t<T>(z, w, z);    }
    vec3_t<T> zww()  const { return vec3_t<T>(z, w, w);    }
    vec3_t<T> wxx()  const { return vec3_t<T>(w, x, x);    }
    vec3_t<T> wxy()  const { return vec3_t<T>(w, x, y);    }
    vec3_t<T> wxz()  const { return vec3_t<T>(w, x, z);    }
    vec3_t<T> wxw()  const { return vec3_t<T>(w, x, w);    }
    vec3_t<T> wyx()  const { return vec3_t<T>(w, y, x);    }
    vec3_t<T> wyy()  const { return vec3_t<T>(w, y, y);    }
    vec3_t<T> wyz()  const { return vec3_t<T>(w, y, z);    }
    vec3_t<T> wyw()  const { return vec3_t<T>(w, y, w);    }
    vec3_t<T> wzx()  const { return vec3_t<T>(w, z, x);    }
    vec3_t<T> wzy()  const { return vec3_t<T>(w, z, y);    }
    vec3_t<T> wzz()  const { return vec3_t<T>(w, z, z);    }
    vec3_t<T> wzw()  const { return vec3_t<T>(w, z, w);    }
    vec3_t<T> wwx()  const { return vec3_t<T>(w, w, x);    }
    vec3_t<T> wwy()  const { return vec3_t<T>(w, w, y);    }
    vec3_t<T> wwz()  const { return vec3_t<T>(w, w, z);    }
    vec3_t<T> www()  const { return vec3_t<T>(w, w, w);    }
    vec4_t<T> xxxx() const { return vec4_t<T>(x, x, x, x); }
    vec4_t<T> xxxy() const { return vec4_t<T>(x, x, x, y); }
    vec4_t<T> xxxz() const { return vec4_t<T>(x, x, x, z); }
    vec4_t<T> xxxw() const { return vec4_t<T>(x, x, x, w); }
    vec4_t<T> xxyx() const { return vec4_t<T>(x, x, y, x); }
    vec4_t<T> xxyy() const { return vec4_t<T>(x, x, y, y); }
    vec4_t<T> xxyz() const { return vec4_t<T>(x, x, y, z); }
    vec4_t<T> xxyw() const { return vec4_t<T>(x, x, y, w); }
    vec4_t<T> xxzx() const { return vec4_t<T>(x, x, z, x); }
    vec4_t<T> xxzy() const { return vec4_t<T>(x, x, z, y); }
    vec4_t<T> xxzz() const { return vec4_t<T>(x, x, z, z); }
    vec4_t<T> xxzw() const { return vec4_t<T>(x, x, z, w); }
    vec4_t<T> xxwx() const { return vec4_t<T>(x, x, w, x); }
    vec4_t<T> xxwy() const { return vec4_t<T>(x, x, w, y); }
    vec4_t<T> xxwz() const { return vec4_t<T>(x, x, w, z); }
    vec4_t<T> xxww() const { return vec4_t<T>(x, x, w, w); }
    vec4_t<T> xyxx() const { return vec4_t<T>(x, y, x, x); }
    vec4_t<T> xyxy() const { return vec4_t<T>(x, y, x, y); }
    vec4_t<T> xyxz() const { return vec4_t<T>(x, y, x, z); }
    vec4_t<T> xyxw() const { return vec4_t<T>(x, y, x, w); }
    vec4_t<T> xyyx() const { return vec4_t<T>(x, y, y, x); }
    vec4_t<T> xyyy() const { return vec4_t<T>(x, y, y, y); }
    vec4_t<T> xyyz() const { return vec4_t<T>(x, y, y, z); }
    vec4_t<T> xyyw() const { return vec4_t<T>(x, y, y, w); }
    vec4_t<T> xyzx() const { return vec4_t<T>(x, y, z, x); }
    vec4_t<T> xyzy() const { return vec4_t<T>(x, y, z, y); }
    vec4_t<T> xyzz() const { return vec4_t<T>(x, y, z, z); }
    vec4_t<T> xyzw() const { return vec4_t<T>(x, y, z, w); }
    vec4_t<T> xywx() const { return vec4_t<T>(x, y, w, x); }
    vec4_t<T> xywy() const { return vec4_t<T>(x, y, w, y); }
    vec4_t<T> xywz() const { return vec4_t<T>(x, y, w, z); }
    vec4_t<T> xyww() const { return vec4_t<T>(x, y, w, w); }
    vec4_t<T> xzxx() const { return vec4_t<T>(x, z, x, x); }
    vec4_t<T> xzxy() const { return vec4_t<T>(x, z, x, y); }
    vec4_t<T> xzxz() const { return vec4_t<T>(x, z, x, z); }
    vec4_t<T> xzxw() const { return vec4_t<T>(x, z, x, w); }
    vec4_t<T> xzyx() const { return vec4_t<T>(x, z, y, x); }
    vec4_t<T> xzyy() const { return vec4_t<T>(x, z, y, y); }
    vec4_t<T> xzyz() const { return vec4_t<T>(x, z, y, z); }
    vec4_t<T> xzyw() const { return vec4_t<T>(x, z, y, w); }
    vec4_t<T> xzzx() const { return vec4_t<T>(x, z, z, x); }
    vec4_t<T> xzzy() const { return vec4_t<T>(x, z, z, y); }
    vec4_t<T> xzzz() const { return vec4_t<T>(x, z, z, z); }
    vec4_t<T> xzzw() const { return vec4_t<T>(x, z, z, w); }
    vec4_t<T> xzwx() const { return vec4_t<T>(x, z, w, x); }
    vec4_t<T> xzwy() const { return vec4_t<T>(x, z, w, y); }
    vec4_t<T> xzwz() const { return vec4_t<T>(x, z, w, z); }
    vec4_t<T> xzww() const { return vec4_t<T>(x, z, w, w); }
    vec4_t<T> xwxx() const { return vec4_t<T>(x, w, x, x); }
    vec4_t<T> xwxy() const { return vec4_t<T>(x, w, x, y); }
    vec4_t<T> xwxz() const { return vec4_t<T>(x, w, x, z); }
    vec4_t<T> xwxw() const { return vec4_t<T>(x, w, x, w); }
    vec4_t<T> xwyx() const { return vec4_t<T>(x, w, y, x); }
    vec4_t<T> xwyy() const { return vec4_t<T>(x, w, y, y); }
    vec4_t<T> xwyz() const { return vec4_t<T>(x, w, y, z); }
    vec4_t<T> xwyw() const { return vec4_t<T>(x, w, y, w); }
    vec4_t<T> xwzx() const { return vec4_t<T>(x, w, z, x); }
    vec4_t<T> xwzy() const { return vec4_t<T>(x, w, z, y); }
    vec4_t<T> xwzz() const { return vec4_t<T>(x, w, z, z); }
    vec4_t<T> xwzw() const { return vec4_t<T>(x, w, z, w); }
    vec4_t<T> xwwx() const { return vec4_t<T>(x, w, w, x); }
    vec4_t<T> xwwy() const { return vec4_t<T>(x, w, w, y); }
    vec4_t<T> xwwz() const { return vec4_t<T>(x, w, w, z); }
    vec4_t<T> xwww() const { return vec4_t<T>(x, w, w, w); }
    vec4_t<T> yxxx() const { return vec4_t<T>(y, x, x, x); }
    vec4_t<T> yxxy() const { return vec4_t<T>(y, x, x, y); }
    vec4_t<T> yxxz() const { return vec4_t<T>(y, x, x, z); }
    vec4_t<T> yxxw() const { return vec4_t<T>(y, x, x, w); }
    vec4_t<T> yxyx() const { return vec4_t<T>(y, x, y, x); }
    vec4_t<T> yxyy() const { return vec4_t<T>(y, x, y, y); }
    vec4_t<T> yxyz() const { return vec4_t<T>(y, x, y, z); }
    vec4_t<T> yxyw() const { return vec4_t<T>(y, x, y, w); }
    vec4_t<T> yxzx() const { return vec4_t<T>(y, x, z, x); }
    vec4_t<T> yxzy() const { return vec4_t<T>(y, x, z, y); }
    vec4_t<T> yxzz() const { return vec4_t<T>(y, x, z, z); }
    vec4_t<T> yxzw() const { return vec4_t<T>(y, x, z, w); }
    vec4_t<T> yxwx() const { return vec4_t<T>(y, x, w, x); }
    vec4_t<T> yxwy() const { return vec4_t<T>(y, x, w, y); }
    vec4_t<T> yxwz() const { return vec4_t<T>(y, x, w, z); }
    vec4_t<T> yxww() const { return vec4_t<T>(y, x, w, w); }
    vec4_t<T> yyxx() const { return vec4_t<T>(y, y, x, x); }
    vec4_t<T> yyxy() const { return vec4_t<T>(y, y, x, y); }
    vec4_t<T> yyxz() const { return vec4_t<T>(y, y, x, z); }
    vec4_t<T> yyxw() const { return vec4_t<T>(y, y, x, w); }
    vec4_t<T> yyyx() const { return vec4_t<T>(y, y, y, x); }
    vec4_t<T> yyyy() const { return vec4_t<T>(y, y, y, y); }
    vec4_t<T> yyyz() const { return vec4_t<T>(y, y, y, z); }
    vec4_t<T> yyyw() const { return vec4_t<T>(y, y, y, w); }
    vec4_t<T> yyzx() const { return vec4_t<T>(y, y, z, x); }
    vec4_t<T> yyzy() const { return vec4_t<T>(y, y, z, y); }
    vec4_t<T> yyzz() const { return vec4_t<T>(y, y, z, z); }
    vec4_t<T> yyzw() const { return vec4_t<T>(y, y, z, w); }
    vec4_t<T> yywx() const { return vec4_t<T>(y, y, w, x); }
    vec4_t<T> yywy() const { return vec4_t<T>(y, y, w, y); }
    vec4_t<T> yywz() const { return vec4_t<T>(y, y, w, z); }
    vec4_t<T> yyww() const { return vec4_t<T>(y, y, w, w); }
    vec4_t<T> yzxx() const { return vec4_t<T>(y, z, x, x); }
    vec4_t<T> yzxy() const { return vec4_t<T>(y, z, x, y); }
    vec4_t<T> yzxz() const { return vec4_t<T>(y, z, x, z); }
    vec4_t<T> yzxw() const { return vec4_t<T>(y, z, x, w); }
    vec4_t<T> yzyx() const { return vec4_t<T>(y, z, y, x); }
    vec4_t<T> yzyy() const { return vec4_t<T>(y, z, y, y); }
    vec4_t<T> yzyz() const { return vec4_t<T>(y, z, y, z); }
    vec4_t<T> yzyw() const { return vec4_t<T>(y, z, y, w); }
    vec4_t<T> yzzx() const { return vec4_t<T>(y, z, z, x); }
    vec4_t<T> yzzy() const { return vec4_t<T>(y, z, z, y); }
    vec4_t<T> yzzz() const { return vec4_t<T>(y, z, z, z); }
    vec4_t<T> yzzw() const { return vec4_t<T>(y, z, z, w); }
    vec4_t<T> yzwx() const { return vec4_t<T>(y, z, w, x); }
    vec4_t<T> yzwy() const { return vec4_t<T>(y, z, w, y); }
    vec4_t<T> yzwz() const { return vec4_t<T>(y, z, w, z); }
    vec4_t<T> yzww() const { return vec4_t<T>(y, z, w, w); }
    vec4_t<T> ywxx() const { return vec4_t<T>(y, w, x, x); }
    vec4_t<T> ywxy() const { return vec4_t<T>(y, w, x, y); }
    vec4_t<T> ywxz() const { return vec4_t<T>(y, w, x, z); }
    vec4_t<T> ywxw() const { return vec4_t<T>(y, w, x, w); }
    vec4_t<T> ywyx() const { return vec4_t<T>(y, w, y, x); }
    vec4_t<T> ywyy() const { return vec4_t<T>(y, w, y, y); }
    vec4_t<T> ywyz() const { return vec4_t<T>(y, w, y, z); }
    vec4_t<T> ywyw() const { return vec4_t<T>(y, w, y, w); }
    vec4_t<T> ywzx() const { return vec4_t<T>(y, w, z, x); }
    vec4_t<T> ywzy() const { return vec4_t<T>(y, w, z, y); }
    vec4_t<T> ywzz() const { return vec4_t<T>(y, w, z, z); }
    vec4_t<T> ywzw() const { return vec4_t<T>(y, w, z, w); }
    vec4_t<T> ywwx() const { return vec4_t<T>(y, w, w, x); }
    vec4_t<T> ywwy() const { return vec4_t<T>(y, w, w, y); }
    vec4_t<T> ywwz() const { return vec4_t<T>(y, w, w, z); }
    vec4_t<T> ywww() const { return vec4_t<T>(y, w, w, w); }
    vec4_t<T> zxxx() const { return vec4_t<T>(z, x, x, x); }
    vec4_t<T> zxxy() const { return vec4_t<T>(z, x, x, y); }
    vec4_t<T> zxxz() const { return vec4_t<T>(z, x, x, z); }
    vec4_t<T> zxxw() const { return vec4_t<T>(z, x, x, w); }
    vec4_t<T> zxyx() const { return vec4_t<T>(z, x, y, x); }
    vec4_t<T> zxyy() const { return vec4_t<T>(z, x, y, y); }
    vec4_t<T> zxyz() const { return vec4_t<T>(z, x, y, z); }
    vec4_t<T> zxyw() const { return vec4_t<T>(z, x, y, w); }
    vec4_t<T> zxzx() const { return vec4_t<T>(z, x, z, x); }
    vec4_t<T> zxzy() const { return vec4_t<T>(z, x, z, y); }
    vec4_t<T> zxzz() const { return vec4_t<T>(z, x, z, z); }
    vec4_t<T> zxzw() const { return vec4_t<T>(z, x, z, w); }
    vec4_t<T> zxwx() const { return vec4_t<T>(z, x, w, x); }
    vec4_t<T> zxwy() const { return vec4_t<T>(z, x, w, y); }
    vec4_t<T> zxwz() const { return vec4_t<T>(z, x, w, z); }
    vec4_t<T> zxww() const { return vec4_t<T>(z, x, w, w); }
    vec4_t<T> zyxx() const { return vec4_t<T>(z, y, x, x); }
    vec4_t<T> zyxy() const { return vec4_t<T>(z, y, x, y); }
    vec4_t<T> zyxz() const { return vec4_t<T>(z, y, x, z); }
    vec4_t<T> zyxw() const { return vec4_t<T>(z, y, x, w); }
    vec4_t<T> zyyx() const { return vec4_t<T>(z, y, y, x); }
    vec4_t<T> zyyy() const { return vec4_t<T>(z, y, y, y); }
    vec4_t<T> zyyz() const { return vec4_t<T>(z, y, y, z); }
    vec4_t<T> zyyw() const { return vec4_t<T>(z, y, y, w); }
    vec4_t<T> zyzx() const { return vec4_t<T>(z, y, z, x); }
    vec4_t<T> zyzy() const { return vec4_t<T>(z, y, z, y); }
    vec4_t<T> zyzz() const { return vec4_t<T>(z, y, z, z); }
    vec4_t<T> zyzw() const { return vec4_t<T>(z, y, z, w); }
    vec4_t<T> zywx() const { return vec4_t<T>(z, y, w, x); }
    vec4_t<T> zywy() const { return vec4_t<T>(z, y, w, y); }
    vec4_t<T> zywz() const { return vec4_t<T>(z, y, w, z); }
    vec4_t<T> zyww() const { return vec4_t<T>(z, y, w, w); }
    vec4_t<T> zzxx() const { return vec4_t<T>(z, z, x, x); }
    vec4_t<T> zzxy() const { return vec4_t<T>(z, z, x, y); }
    vec4_t<T> zzxz() const { return vec4_t<T>(z, z, x, z); }
    vec4_t<T> zzxw() const { return vec4_t<T>(z, z, x, w); }
    vec4_t<T> zzyx() const { return vec4_t<T>(z, z, y, x); }
    vec4_t<T> zzyy() const { return vec4_t<T>(z, z, y, y); }
    vec4_t<T> zzyz() const { return vec4_t<T>(z, z, y, z); }
    vec4_t<T> zzyw() const { return vec4_t<T>(z, z, y, w); }
    vec4_t<T> zzzx() const { return vec4_t<T>(z, z, z, x); }
    vec4_t<T> zzzy() const { return vec4_t<T>(z, z, z, y); }
    vec4_t<T> zzzz() const { return vec4_t<T>(z, z, z, z); }
    vec4_t<T> zzzw() const { return vec4_t<T>(z, z, z, w); }
    vec4_t<T> zzwx() const { return vec4_t<T>(z, z, w, x); }
    vec4_t<T> zzwy() const { return vec4_t<T>(z, z, w, y); }
    vec4_t<T> zzwz() const { return vec4_t<T>(z, z, w, z); }
    vec4_t<T> zzww() const { return vec4_t<T>(z, z, w, w); }
    vec4_t<T> zwxx() const { return vec4_t<T>(z, w, x, x); }
    vec4_t<T> zwxy() const { return vec4_t<T>(z, w, x, y); }
    vec4_t<T> zwxz() const { return vec4_t<T>(z, w, x, z); }
    vec4_t<T> zwxw() const { return vec4_t<T>(z, w, x, w); }
    vec4_t<T> zwyx() const { return vec4_t<T>(z, w, y, x); }
    vec4_t<T> zwyy() const { return vec4_t<T>(z, w, y, y); }
    vec4_t<T> zwyz() const { return vec4_t<T>(z, w, y, z); }
    vec4_t<T> zwyw() const { return vec4_t<T>(z, w, y, w); }
    vec4_t<T> zwzx() const { return vec4_t<T>(z, w, z, x); }
    vec4_t<T> zwzy() const { return vec4_t<T>(z, w, z, y); }
    vec4_t<T> zwzz() const { return vec4_t<T>(z, w, z, z); }
    vec4_t<T> zwzw() const { return vec4_t<T>(z, w, z, w); }
    vec4_t<T> zwwx() const { return vec4_t<T>(z, w, w, x); }
    vec4_t<T> zwwy() const { return vec4_t<T>(z, w, w, y); }
    vec4_t<T> zwwz() const { return vec4_t<T>(z, w, w, z); }
    vec4_t<T> zwww() const { return vec4_t<T>(z, w, w, w); }
    vec4_t<T> wxxx() const { return vec4_t<T>(w, x, x, x); }
    vec4_t<T> wxxy() const { return vec4_t<T>(w, x, x, y); }
    vec4_t<T> wxxz() const { return vec4_t<T>(w, x, x, z); }
    vec4_t<T> wxxw() const { return vec4_t<T>(w, x, x, w); }
    vec4_t<T> wxyx() const { return vec4_t<T>(w, x, y, x); }
    vec4_t<T> wxyy() const { return vec4_t<T>(w, x, y, y); }
    vec4_t<T> wxyz() const { return vec4_t<T>(w, x, y, z); }
    vec4_t<T> wxyw() const { return vec4_t<T>(w, x, y, w); }
    vec4_t<T> wxzx() const { return vec4_t<T>(w, x, z, x); }
    vec4_t<T> wxzy() const { return vec4_t<T>(w, x, z, y); }
    vec4_t<T> wxzz() const { return vec4_t<T>(w, x, z, z); }
    vec4_t<T> wxzw() const { return vec4_t<T>(w, x, z, w); }
    vec4_t<T> wxwx() const { return vec4_t<T>(w, x, w, x); }
    vec4_t<T> wxwy() const { return vec4_t<T>(w, x, w, y); }
    vec4_t<T> wxwz() const { return vec4_t<T>(w, x, w, z); }
    vec4_t<T> wxww() const { return vec4_t<T>(w, x, w, w); }
    vec4_t<T> wyxx() const { return vec4_t<T>(w, y, x, x); }
    vec4_t<T> wyxy() const { return vec4_t<T>(w, y, x, y); }
    vec4_t<T> wyxz() const { return vec4_t<T>(w, y, x, z); }
    vec4_t<T> wyxw() const { return vec4_t<T>(w, y, x, w); }
    vec4_t<T> wyyx() const { return vec4_t<T>(w, y, y, x); }
    vec4_t<T> wyyy() const { return vec4_t<T>(w, y, y, y); }
    vec4_t<T> wyyz() const { return vec4_t<T>(w, y, y, z); }
    vec4_t<T> wyyw() const { return vec4_t<T>(w, y, y, w); }
    vec4_t<T> wyzx() const { return vec4_t<T>(w, y, z, x); }
    vec4_t<T> wyzy() const { return vec4_t<T>(w, y, z, y); }
    vec4_t<T> wyzz() const { return vec4_t<T>(w, y, z, z); }
    vec4_t<T> wyzw() const { return vec4_t<T>(w, y, z, w); }
    vec4_t<T> wywx() const { return vec4_t<T>(w, y, w, x); }
    vec4_t<T> wywy() const { return vec4_t<T>(w, y, w, y); }
    vec4_t<T> wywz() const { return vec4_t<T>(w, y, w, z); }
    vec4_t<T> wyww() const { return vec4_t<T>(w, y, w, w); }
    vec4_t<T> wzxx() const { return vec4_t<T>(w, z, x, x); }
    vec4_t<T> wzxy() const { return vec4_t<T>(w, z, x, y); }
    vec4_t<T> wzxz() const { return vec4_t<T>(w, z, x, z); }
    vec4_t<T> wzxw() const { return vec4_t<T>(w, z, x, w); }
    vec4_t<T> wzyx() const { return vec4_t<T>(w, z, y, x); }
    vec4_t<T> wzyy() const { return vec4_t<T>(w, z, y, y); }
    vec4_t<T> wzyz() const { return vec4_t<T>(w, z, y, z); }
    vec4_t<T> wzyw() const { return vec4_t<T>(w, z, y, w); }
    vec4_t<T> wzzx() const { return vec4_t<T>(w, z, z, x); }
    vec4_t<T> wzzy() const { return vec4_t<T>(w, z, z, y); }
    vec4_t<T> wzzz() const { return vec4_t<T>(w, z, z, z); }
    vec4_t<T> wzzw() const { return vec4_t<T>(w, z, z, w); }
    vec4_t<T> wzwx() const { return vec4_t<T>(w, z, w, x); }
    vec4_t<T> wzwy() const { return vec4_t<T>(w, z, w, y); }
    vec4_t<T> wzwz() const { return vec4_t<T>(w, z, w, z); }
    vec4_t<T> wzww() const { return vec4_t<T>(w, z, w, w); }
    vec4_t<T> wwxx() const { return vec4_t<T>(w, w, x, x); }
    vec4_t<T> wwxy() const { return vec4_t<T>(w, w, x, y); }
    vec4_t<T> wwxz() const { return vec4_t<T>(w, w, x, z); }
    vec4_t<T> wwxw() const { return vec4_t<T>(w, w, x, w); }
    vec4_t<T> wwyx() const { return vec4_t<T>(w, w, y, x); }
    vec4_t<T> wwyy() const { return vec4_t<T>(w, w, y, y); }
    vec4_t<T> wwyz() const { return vec4_t<T>(w, w, y, z); }
    vec4_t<T> wwyw() const { return vec4_t<T>(w, w, y, w); }
    vec4_t<T> wwzx() const { return vec4_t<T>(w, w, z, x); }
    vec4_t<T> wwzy() const { return vec4_t<T>(w, w, z, y); }
    vec4_t<T> wwzz() const { return vec4_t<T>(w, w, z, z); }
    vec4_t<T> wwzw() const { return vec4_t<T>(w, w, z, w); }
    vec4_t<T> wwwx() const { return vec4_t<T>(w, w, w, x); }
    vec4_t<T> wwwy() const { return vec4_t<T>(w, w, w, y); }
    vec4_t<T> wwwz() const { return vec4_t<T>(w, w, w, z); }
    vec4_t<T> wwww() const { return vec4_t<T>(w, w, w, w); }
};

template<class T>
T dot(const vec4_t<T>& v1, const vec4_t<T>& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

template<class T>
vec4_t<T> normalize(const vec4_t<T>& v) {
    auto m = v.length();

    if (m > std::numeric_limits<T>::epsilon()) {
        m = 1 / m;
    } else {
        m = 0;
    }

    return vec4_t<T>(v.x * m, v.y * m, v.z * m, v.w * m);
}

template<class T>
vec4_t<T> minimize(const vec4_t<T>& v1, const vec4_t<T>& v2) {
    return vec4_t<T>((v1.x < v2.x) ? v1.x : v2.x,
                     (v1.y < v2.y) ? v1.y : v2.y,
                     (v1.z < v2.z) ? v1.z : v2.z,
                     (v1.w < v2.w) ? v1.w : v2.w);
}

template<class T>
vec4_t<T> maximize(const vec4_t<T>& v1, const vec4_t<T>& v2) {
    return vec4_t<T>((v1.x > v2.x) ? v1.x : v2.x,
                     (v1.y > v2.y) ? v1.y : v2.y,
                     (v1.z > v2.z) ? v1.z : v2.z,
                     (v1.w > v2.w) ? v1.w : v2.w);
}

template<class T>
T length(const vec4_t<T>& v) {
    return sqrt(v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w);
}

template<class T>
T length2(const vec4_t<T>& v) {
    return v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w;
}

template<class T>
vec4_t<T> abs(const vec4_t<T>& v) {
    return vec4_t<T>((v.x < 0) ? -v.x : v.x,
                     (v.y < 0) ? -v.y : v.y,
                     (v.z < 0) ? -v.z : v.z,
                     (v.w < 0) ? -v.w : v.w);
}

template<class T>
vec4_t<T> clamp(const vec4_t<T>& v, T min, T max) {
    return vec4_t<T>((v.x < min) ? min : ((v.x > max) ? max : v.x),
                     (v.y < min) ? min : ((v.y > max) ? max : v.y),
                     (v.z < min) ? min : ((v.z > max) ? max : v.z),
                     (v.w < min) ? min : ((v.w > max) ? max : v.w));
}

template<class T>
vec4_t<T> clamp(const vec4_t<T>& v, const vec4_t<T>& min, const vec4_t<T>& max) {
    return vec4_t<T>((v.x < min.x) ? min.x : ((v.x > max.x) ? max.x : v.x),
                     (v.y < min.y) ? min.y : ((v.y > max.y) ? max.y : v.y),
                     (v.z < min.z) ? min.z : ((v.z > max.z) ? max.z : v.z),
                     (v.w < min.w) ? min.w : ((v.w > max.w) ? max.w : v.w));
}

template<class T>
vec4_t<T> lerp(const vec4_t<T>& min, const vec4_t<T>& max, T scale) {
    return vec4_t<T>(min.x + scale * (max.x - min.x),
                     min.y + scale * (max.y - min.y),
                     min.z + scale * (max.z - min.z),
                     min.w + scale * (max.w - min.w));
}

template<class T>
vec4_t<T> saturate(const vec4_t<T>& v) {
    return vec4_t<T>((v.x < 0) ? 0 : ((v.x > 1) ? 1 : v.x),
                     (v.y < 0) ? 0 : ((v.y > 1) ? 1 : v.y),
                     (v.z < 0) ? 0 : ((v.z > 1) ? 1 : v.z),
                     (v.w < 0) ? 0 : ((v.w > 1) ? 1 : v.w));
}
