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
struct vec2_t {
    T x, y;

    // Constructors
    vec2_t() {}
    vec2_t(T x, T y) : x(x), y(y) {}
    explicit vec2_t(const T* p) : x(p[0]), y(p[1]) {}

    // Unary operators
    vec2_t operator - () const {
        return vec2_t(-x, -y);
    }

    // Binary operators
    vec2_t operator * (T f) const {
        return vec2_t(x * f, y * f);
    }

    friend vec2_t operator * (T f, const vec2_t& v) {
        return vec2_t(v.x * f, v.y * f);
    }

    vec2_t operator / (T f) const {
        assert(fabs(f) > std::numeric_limits<T>::epsilon());
        return vec2_t(x / f, y / f);
    }

    friend vec2_t operator / (T f, const vec2_t& v) {
        assert(fabs(v.x) > std::numeric_limits<T>::epsilon());
        assert(fabs(v.y) > std::numeric_limits<T>::epsilon());
        return vec2_t(f / v.x, f / v.y);
    }

    vec2_t& operator *= (T f) {
        x *= f;
        y *= f;
        return *this;
    }

    vec2_t& operator /= (T f) {
        assert(fabs(f) > std::numeric_limits<T>::epsilon());
        x /= f;
        y /= f;
        return *this;
    }

    vec2_t operator + (const vec2_t& v) const {
        return vec2_t(x + v.x, y + v.y);
    }

    vec2_t operator - (const vec2_t& v) const {
        return vec2_t(x - v.x, y - v.y);
    }

    vec2_t operator * (const vec2_t& v) const {
        return vec2_t(x * v.x, y * v.y);
    }

    vec2_t operator / (const vec2_t& v) const {
        assert(fabs(v.x) > std::numeric_limits<T>::epsilon());
        assert(fabs(v.y) > std::numeric_limits<T>::epsilon());
        return vec2_t(x / v.x, y / v.y);
    }

    vec2_t& operator += (const vec2_t& v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    vec2_t& operator -= (const vec2_t& v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    vec2_t& operator *= (const vec2_t& v) {
        x *= v.x;
        y *= v.y;
        return *this;
    }

    vec2_t& operator /= (const vec2_t& v) {
        assert(fabs(v.x) > std::numeric_limits<T>::epsilon());
        assert(fabs(v.y) > std::numeric_limits<T>::epsilon());
        x /= v.x;
        y /= v.y;
        return *this;
    }

    vec2_t operator * (const mat2x2_t<T>& m) const {
        return vec2_t(x * m.m11 + y * m.m21,
                      x * m.m12 + y * m.m22);
    }

    vec2_t operator * (const mat3x3_t<T>& m) const {
        auto h = x * m.m13 + y * m.m23 + m.m33;
        assert(fabs(h) > std::numeric_limits<T>::epsilon());
        return vec2_t((x * m.m11 + y * m.m21 + m.m31) / h,
                      (x * m.m12 + y * m.m22 + m.m32) / h);
    }

    vec2_t& operator *= (const mat2x2_t<T>& m) {
        auto vx = x * m.m11 + y * m.m21;
        auto vy = x * m.m12 + y * m.m22;
        x = vx;
        y = vy;
        return *this;
    }

    vec2_t& operator *= (const mat3x3_t<T>& m) {
        auto h = x * m.m13 + y * m.m23 + m.m33;
        assert(fabs(h) > std::numeric_limits<T>::epsilon());

        auto vx = (x * m.m11 + y * m.m21 + m.m31) / h;
        auto vy = (x * m.m12 + y * m.m22 + m.m32) / h;
        x = vx;
        y = vy;
        return *this;
    }

    bool operator == (const vec2_t& v) const {
        return x == v.x && y == v.y;
    }

    bool operator != (const vec2_t& v) const {
        return x != v.x || y != v.y;
    }

    bool operator < (const vec2_t& v) const {
        return x < v.x && y < v.y;
    }

    T& operator [] (int index) {
        assert(index >= 0 && index <= 1);
        return *(&x + index);
    }

    T operator [] (int index) const {
        assert(index >= 0 && index <= 1);
        return *(&x + index);
    }

    T length() const {
        return sqrt(x*x + y*y);
    }

    // Swizzles
    vec2_t<T> xx()   const { return vec2_t<T>(x, x);       }
    vec2_t<T> xy()   const { return vec2_t<T>(x, y);       }
    vec2_t<T> yx()   const { return vec2_t<T>(y, x);       }
    vec2_t<T> yy()   const { return vec2_t<T>(y, y);       }
    vec3_t<T> xxx()  const { return vec3_t<T>(x, x, x);    }
    vec3_t<T> xxy()  const { return vec3_t<T>(x, x, y);    }
    vec3_t<T> xyx()  const { return vec3_t<T>(x, y, x);    }
    vec3_t<T> xyy()  const { return vec3_t<T>(x, y, y);    }
    vec3_t<T> yxx()  const { return vec3_t<T>(y, x, x);    }
    vec3_t<T> yxy()  const { return vec3_t<T>(y, x, y);    }
    vec3_t<T> yyx()  const { return vec3_t<T>(y, y, x);    }
    vec3_t<T> yyy()  const { return vec3_t<T>(y, y, y);    }
    vec4_t<T> xxxx() const { return vec4_t<T>(x, x, x, x); }
    vec4_t<T> xxxy() const { return vec4_t<T>(x, x, x, y); }
    vec4_t<T> xxyx() const { return vec4_t<T>(x, x, y, x); }
    vec4_t<T> xxyy() const { return vec4_t<T>(x, x, y, y); }
    vec4_t<T> xyxx() const { return vec4_t<T>(x, y, x, x); }
    vec4_t<T> xyxy() const { return vec4_t<T>(x, y, x, y); }
    vec4_t<T> xyyx() const { return vec4_t<T>(x, y, y, x); }
    vec4_t<T> xyyy() const { return vec4_t<T>(x, y, y, y); }
    vec4_t<T> yxxx() const { return vec4_t<T>(y, x, x, x); }
    vec4_t<T> yxxy() const { return vec4_t<T>(y, x, x, y); }
    vec4_t<T> yxyx() const { return vec4_t<T>(y, x, y, x); }
    vec4_t<T> yxyy() const { return vec4_t<T>(y, x, y, y); }
    vec4_t<T> yyxx() const { return vec4_t<T>(y, y, x, x); }
    vec4_t<T> yyxy() const { return vec4_t<T>(y, y, x, y); }
    vec4_t<T> yyyx() const { return vec4_t<T>(y, y, y, x); }
    vec4_t<T> yyyy() const { return vec4_t<T>(y, y, y, y); }
};

template<class T>
T dot(const vec2_t<T>& v1, const vec2_t<T>& v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

template<class T>
vec2_t<T> normalize(const vec2_t<T>& v) {
    auto m = v.length();

    if (m > std::numeric_limits<T>::epsilon()) {
        m = 1 / m;
    } else {
        m = 0;
    }

    return vec2_t<T>(v.x * m, v.y * m);
}

template<class T>
vec2_t<T> minimize(const vec2_t<T>& v1, const vec2_t<T>& v2) {
    return vec2_t<T>((v1.x < v2.x) ? v1.x : v2.x,
                     (v1.y < v2.y) ? v1.y : v2.y);
}

template<class T>
vec2_t<T> maximize(const vec2_t<T>& v1, const vec2_t<T>& v2) {
    return vec2_t<T>((v1.x > v2.x) ? v1.x : v2.x,
                     (v1.y > v2.y) ? v1.y : v2.y);
}

template<class T>
T length(const vec2_t<T>& v) {
    return sqrt(v.x*v.x + v.y*v.y);
}

template<class T>
T length2(const vec2_t<T>& v) {
    return v.x*v.x + v.y*v.y;
}

template<class T>
vec2_t<T> abs(const vec2_t<T>& v) {
    return vec2_t<T>((v.x < 0) ? -v.x : v.x,
                     (v.y < 0) ? -v.y : v.y);
}

template<class T>
vec2_t<T> clamp(const vec2_t<T>& v, T min, T max) {
    return vec2_t<T>((v.x < min) ? min : ((v.x > max) ? max : v.x),
                     (v.y < min) ? min : ((v.y > max) ? max : v.y));
}

template<class T>
vec2_t<T> clamp(const vec2_t<T>& v, const vec2_t<T>& min, const vec2_t<T>& max) {
    return vec2_t<T>((v.x < min.x) ? min.x : ((v.x > max.x) ? max.x : v.x),
                     (v.y < min.y) ? min.y : ((v.y > max.y) ? max.y : v.y));
}

template<class T>
vec2_t<T> lerp(const vec2_t<T>& min, const vec2_t<T>& max, T scale) {
    return vec2_t<T>(min.x + scale * (max.x - min.x),
                     min.y + scale * (max.y - min.y));
}

template<class T>
vec2_t<T> saturate(const vec2_t<T>& v) {
    return vec2_t<T>((v.x < 0) ? 0 : ((v.x > 1) ? 1 : v.x),
                     (v.y < 0) ? 0 : ((v.y > 1) ? 1 : v.y));
}
