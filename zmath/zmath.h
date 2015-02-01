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

#include <cassert>
#include <cmath>
#include <limits>

// Forward declarations
template<class T> struct color3_t;
template<class T> struct color4_t;
template<class T> struct mat2x2_t;
template<class T> struct mat3x3_t;
template<class T> struct mat4x3_t;
template<class T> struct mat4x4_t;
template<class T> struct plane_t;
template<class T> struct quat_t;
template<class T> struct ray_t;
template<class T> struct vec2_t;
template<class T> struct vec3_t;
template<class T> struct vec4_t;

#include "color3.h"
#include "color4.h"
#include "shared.h"
#include "mat2x2.h"
#include "mat3x3.h"
#include "mat4x3.h"
#include "mat4x4.h"
#include "plane.h"
#include "quat.h"
#include "ray.h"
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"

typedef color3_t<float> color3;
typedef color4_t<float> color4;
typedef mat2x2_t<float> mat2x2;
typedef mat3x3_t<float> mat3x3;
typedef mat4x3_t<float> mat4x3;
typedef mat4x4_t<float> mat4x4;
typedef plane_t<float>  plane;
typedef quat_t<float>   quat;
typedef ray_t<float>    ray;
typedef vec2_t<float>   vec2;
typedef vec3_t<float>   vec3;
typedef vec4_t<float>   vec4;
