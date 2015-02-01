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
struct plane_t {
    vec3_t<T> normal;
    T dist;

    plane_t() {}
    plane_t(T a, T b, T c, T d) : normal(a, b, c), dist(d) {}
    plane_t(const vec3_t<T>& normal, T dist) : normal(normal), dist(dist) {}
    plane_t(const vec3_t<T>& normal, const vec3_t<T>& p) : normal(normal), dist(-dot(normal, p)) {}

    plane_t(const vec3_t<T>& p1, const vec3_t<T>& p2, const vec3_t<T>& p3) {
        normal = normalize(cross(p3 - p2, p1 - p2));
        dist = -dot(normal, p1);
    }

    plane_t operator * (T f) const {
        return plane_t(normal * f, dist * f);
    }

    plane_t operator / (T f) const {
        return plane_t(normal / f, dist / f);
    }

    plane_t& operator *= (T f) {
        normal *= f;
        dist *= f;
        return *this;
    }

    plane_t& operator /= (T f) {
        normal /= f;
        dist /= f;
        return *this;
    }

    plane_t operator - () const {
        return plane_t(-normal, -dist);
    }

    bool operator == (const plane_t& p) const {
        return normal == p.normal && dist == p.dist;
    }

    bool operator != (const plane_t& p) const {
        return normal != p.normal || dist != p.dist;
    }
};

template<class T>
plane_t<T> normalize(const plane_t<T>& p) {
    auto m = p.normal.length();

    if (m > std::numeric_limits<T>::epsilon()) {
        m = 1 / m;
    } else {
        m = 0;
    }

    return plane_t<T>(p.normal * m, p.dist * m);
}

template<class T>
T dot(const plane_t<T>& p, const vec3_t<T>& v) {
    return dot(p.normal, v) + p.dist;
}
