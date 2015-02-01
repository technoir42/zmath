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

static const double PI = 3.141592653589793238463;

template<class T>
bool float_eq(T a, T b, T maxError = 1e-6) {
    auto delta = a-b;
    if (fabs(delta) < std::numeric_limits<T>::epsilon()) {
        return true;
    }
    T relativeError;
    if (fabs(b) > fabs(a)) {
        relativeError = fabs(delta / b);
    } else {
        relativeError = fabs(delta / a);
    }
    if (relativeError <= maxError) {
        return true;
    }
    return false;
}

template<class T>
T sqr(T x) {
    return x * x;
}

template<class T>
T radians(T x) {
    return x * (T)PI / (T)180;
}

template<class T>
T degrees(T x) {
    return x * 180 / (T)PI;
}

template<class T>
bool ispow2(T x) {
    return x != 0 && (x & (x-1)) == 0;
}

template<class T>
T lerp(T min, T max, T scale) {
    return min + (max - min) * scale;
}

template<class T>
T clamp(T value, T min, T max) {
    return (value < min) ? min : ((value > max) ? max : value);
}

template<class T>
T saturate(T x) {
    return (x < 0) ? 0 : ((x > 1) ? 1 : x);
}

template<class T>
T det2x2(T m11, T m12,
         T m21, T m22) {
    return m11 * m22 - m21 * m12;
}

template<class T>
T det3x3(T m11, T m12, T m13,
         T m21, T m22, T m23,
         T m31, T m32, T m33) {
    return m11 * det2x2(m22, m23,
                        m32, m33)

          -m21 * det2x2(m12, m13,
                        m32, m33)

          +m31 * det2x2(m12, m13,
                        m22, m23);
}

template<class T>
T det4x4(T m11, T m12, T m13, T m14,
         T m21, T m22, T m23, T m24,
         T m31, T m32, T m33, T m34,
         T m41, T m42, T m43, T m44) {
    return m11 * det3x3(m22, m23, m24,
                        m32, m33, m34,
                        m42, m43, m44)

          -m21 * det3x3(m12, m13, m14,
                        m32, m33, m34,
                        m42, m43, m44)

          +m31 * det3x3(m12, m13, m14,
                        m22, m23, m24,
                        m42, m43, m44)

          -m41 * det3x3(m12, m13, m14,
                        m22, m23, m24,
                        m32, m33, m34);
}
