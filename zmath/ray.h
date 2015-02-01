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
struct ray_t {
    vec3_t<T> dir;
    vec3_t<T> pos;

    ray_t() {}
    ray_t(const vec3_t<T>& pos, const vec3_t<T>& dir) : dir(dir), pos(pos) {}

    bool operator == (const ray_t& r) const {
        return pos == r.pos && dir == r.dir;
    }

    bool operator != (const ray_t& r) const {
        return pos != r.pos || dir != r.dir;
    }
};

template<class T>
ray_t<T> normalize(const ray_t<T>& v) {
    return ray_t<T>(v.pos, normalize(v.dir));
}

template<class T>
ray_t<T> unproject(int x, int y, int w, int h, const mat4x4_t<T>& invView, const mat4x4_t<T>& proj) {
    vec3_t<T> v;
    v.x =  (((2 * x) / (T)w) - 1) / proj.m11;
    v.y = -(((2 * y) / (T)h) - 1) / proj.m22;
    v.z = -1;

    vec3_t<T> pos(invView.m41, invView.m42, invView.m43);
    vec3_t<T> dir(
        v.x * invView.m11 + v.y * invView.m21 + v.z * invView.m31,
        v.x * invView.m12 + v.y * invView.m22 + v.z * invView.m32,
        v.x * invView.m13 + v.y * invView.m23 + v.z * invView.m33);

    return ray_t<T>(pos, normalize(dir));
}
