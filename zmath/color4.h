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
struct color4_t {
    T r, g, b, a;

    color4_t() : r(0), g(0), b(0), a(1) {}
    color4_t(T r, T g, T b, T a) : r(r), g(g), b(b), a(a) {}

    color4_t operator * (const color4_t& c) const {
        return color4_t(r * c.r, g * c.g, b * c.b, a * c.a);
    }

    color4_t operator + (const color4_t& c) const {
        return color4_t(r + c.r, g + c.g, b + c.b, a + c.a);
    }

    color4_t operator - (const color4_t& c) const {
        return color4_t(r - c.r, g - c.g, b - c.b, a - c.a);
    }

    color4_t operator * (T f) const {
        return color4_t(r * f, g * f, b * f, a * f);
    }

    friend color4_t operator * (T f, const color4_t& c) {
        return color4_t(c.r * f, c.g * f, c.b * f, c.a * f);
    }

    color4_t operator / (T f) const {
        return color4_t(r / f, g / f, b / f, a / f);
    }

    color4_t& operator += (const color4_t& c) {
        r += c.r;
        g += c.g;
        b += c.b;
        a += c.a;
        return *this;
    }

    color4_t& operator -= (const color4_t& c) {
        r -= c.r;
        g -= c.g;
        b -= c.b;
        a -= c.a;
        return *this;
    }

    color4_t& operator *= (const color4_t& c) {
        r *= c.r;
        g *= c.g;
        b *= c.b;
        a *= c.a;
        return *this;
    }

    color4_t& operator /= (const color4_t& c) {
        r /= c.r;
        g /= c.g;
        b /= c.b;
        a /= c.a;
        return *this;
    }

    color4_t& operator *= (T f) {
        r *= f;
        g *= f;
        b *= f;
        a *= f;
        return *this;
    }

    color4_t& operator /= (T f) {
        r /= f;
        g /= f;
        b /= f;
        a /= f;
        return *this;
    }

    bool operator == (const color4_t& c) const {
        return r == c.r && g == c.g && b == c.b && a == c.a;
    }

    bool operator != (const color4_t& c) const {
        return r != c.r || g != c.g || b != c.b || a != c.a;
    }

    bool operator < (const color4_t& c) const {
        return r < c.r && g < c.g && b < c.b && a < c.a;
    }

    color3_t<T> rgb()  const { return color3_t<T>(r, g, b);    }
    color3_t<T> bgr()  const { return color3_t<T>(b, g, r);    }
    color4_t<T> rgba() const { return color4_t<T>(r, g, b, a); }
    color4_t<T> bgra() const { return color4_t<T>(b, g, r, a); }

    static color4_t aliceBlue()            { return color4_t(T(0.941),  T(0.973),   T(1),       T(1)); }
    static color4_t antiqueWhite()         { return color4_t(T(0.98),   T(0.922),   T(0.843),   T(1)); }
    static color4_t aqua()                 { return color4_t(T(0),      T(1),       T(1),       T(1)); }
    static color4_t aquamarine()           { return color4_t(T(0.498),  T(1),       T(0.831),   T(1)); }
    static color4_t azure()                { return color4_t(T(0.941),  T(1),       T(1),       T(1)); }
    static color4_t beige()                { return color4_t(T(0.961),  T(0.961),   T(0.863),   T(1)); }
    static color4_t bisque()               { return color4_t(T(1),      T(0.894),   T(0.769),   T(1)); }
    static color4_t black()                { return color4_t(T(0),      T(0),       T(0),       T(1)); }
    static color4_t blanchedAlmond()       { return color4_t(T(1),      T(0.922),   T(0.804),   T(1)); }
    static color4_t blue()                 { return color4_t(T(0),      T(0),       T(1),       T(1)); }
    static color4_t blueViolet()           { return color4_t(T(0.541),  T(0.169),   T(0.886),   T(1)); }
    static color4_t brown()                { return color4_t(T(0.647),  T(0.165),   T(0.165),   T(1)); }
    static color4_t burlyWood()            { return color4_t(T(0.871),  T(0.722),   T(0.529),   T(1)); }
    static color4_t cadetBlue()            { return color4_t(T(0.373),  T(0.62),    T(0.627),   T(1)); }
    static color4_t chartreuse()           { return color4_t(T(0.498),  T(1),       T(0),       T(1)); }
    static color4_t chocolate()            { return color4_t(T(0.824),  T(0.412),   T(0.118),   T(1)); }
    static color4_t coral()                { return color4_t(T(1),      T(0.498),   T(0.314),   T(1)); }
    static color4_t cornflowerBlue()       { return color4_t(T(0.392),  T(0.584),   T(0.929),   T(1)); }
    static color4_t cornsilk()             { return color4_t(T(1),      T(0.973),   T(0.863),   T(1)); }
    static color4_t crimson()              { return color4_t(T(0.863),  T(0.0784),  T(0.235),   T(1)); }
    static color4_t cyan()                 { return color4_t(T(0),      T(1),       T(1),       T(1)); }
    static color4_t darkBlue()             { return color4_t(T(0),      T(0),       T(0.545),   T(1)); }
    static color4_t darkCyan()             { return color4_t(T(0),      T(0.545),   T(0.545),   T(1)); }
    static color4_t darkGoldenrod()        { return color4_t(T(0.722),  T(0.525),   T(0.0431),  T(1)); }
    static color4_t darkGray()             { return color4_t(T(0.663),  T(0.663),   T(0.663),   T(1)); }
    static color4_t darkGreen()            { return color4_t(T(0),      T(0.392),   T(0),       T(1)); }
    static color4_t darkKhaki()            { return color4_t(T(0.741),  T(0.718),   T(0.42),    T(1)); }
    static color4_t darkMagenta()          { return color4_t(T(0.545),  T(0),       T(0.545),   T(1)); }
    static color4_t darkOliveGreen()       { return color4_t(T(0.333),  T(0.42),    T(0.184),   T(1)); }
    static color4_t darkOrange()           { return color4_t(T(1),      T(0.549),   T(0),       T(1)); }
    static color4_t darkOrchid()           { return color4_t(T(0.6),    T(0.196),   T(0.8),     T(1)); }
    static color4_t darkRed()              { return color4_t(T(0.545),  T(0),       T(0),       T(1)); }
    static color4_t darkSalmon()           { return color4_t(T(0.914),  T(0.588),   T(0.478),   T(1)); }
    static color4_t darkSeaGreen()         { return color4_t(T(0.561),  T(0.737),   T(0.545),   T(1)); }
    static color4_t darkSlateBlue()        { return color4_t(T(0.282),  T(0.239),   T(0.545),   T(1)); }
    static color4_t darkSlateGray()        { return color4_t(T(0.184),  T(0.31),    T(0.31),    T(1)); }
    static color4_t darkTurquoise()        { return color4_t(T(0),      T(0.808),   T(0.82),    T(1)); }
    static color4_t darkViolet()           { return color4_t(T(0.58),   T(0),       T(0.827),   T(1)); }
    static color4_t deepPink()             { return color4_t(T(1),      T(0.0784),  T(0.576),   T(1)); }
    static color4_t deepSkyBlue()          { return color4_t(T(0),      T(0.749),   T(1),       T(1)); }
    static color4_t dimGray()              { return color4_t(T(0.412),  T(0.412),   T(0.412),   T(1)); }
    static color4_t dodgerBlue()           { return color4_t(T(0.118),  T(0.565),   T(1),       T(1)); }
    static color4_t firebrick()            { return color4_t(T(0.698),  T(0.133),   T(0.133),   T(1)); }
    static color4_t floralWhite()          { return color4_t(T(1),      T(0.98),    T(0.941),   T(1)); }
    static color4_t forestGreen()          { return color4_t(T(0.133),  T(0.545),   T(0.133),   T(1)); }
    static color4_t fuchsia()              { return color4_t(T(1),      T(0),       T(1),       T(1)); }
    static color4_t gainsboro()            { return color4_t(T(0.863),  T(0.863),   T(0.863),   T(1)); }
    static color4_t ghostWhite()           { return color4_t(T(0.973),  T(0.973),   T(1),       T(1)); }
    static color4_t gold()                 { return color4_t(T(1),      T(0.843),   T(0),       T(1)); }
    static color4_t goldenrod()            { return color4_t(T(0.855),  T(0.647),   T(0.125),   T(1)); }
    static color4_t gray()                 { return color4_t(T(0.502),  T(0.502),   T(0.502),   T(1)); }
    static color4_t green()                { return color4_t(T(0),      T(0.502),   T(0),       T(1)); }
    static color4_t greenYellow()          { return color4_t(T(0.678),  T(1),       T(0.184),   T(1)); }
    static color4_t honeydew()             { return color4_t(T(0.941),  T(1),       T(0.941),   T(1)); }
    static color4_t hotPink()              { return color4_t(T(1),      T(0.412),   T(0.706),   T(1)); }
    static color4_t indianRed()            { return color4_t(T(0.804),  T(0.361),   T(0.361),   T(1)); }
    static color4_t indigo()               { return color4_t(T(0.294),  T(0),       T(0.51),    T(1)); }
    static color4_t ivory()                { return color4_t(T(1),      T(1),       T(0.941),   T(1)); }
    static color4_t khaki()                { return color4_t(T(0.941),  T(0.902),   T(0.549),   T(1)); }
    static color4_t lavender()             { return color4_t(T(0.902),  T(0.902),   T(0.98),    T(1)); }
    static color4_t lavenderBlush()        { return color4_t(T(1),      T(0.941),   T(0.961),   T(1)); }
    static color4_t lawnGreen()            { return color4_t(T(0.486),  T(0.988),   T(0),       T(1)); }
    static color4_t lemonChiffon()         { return color4_t(T(1),      T(0.98),    T(0.804),   T(1)); }
    static color4_t lightBlue()            { return color4_t(T(0.678),  T(0.847),   T(0.902),   T(1)); }
    static color4_t lightCoral()           { return color4_t(T(0.941),  T(0.502),   T(0.502),   T(1)); }
    static color4_t lightCyan()            { return color4_t(T(0.878),  T(1),       T(1),       T(1)); }
    static color4_t lightGoldenrodYellow() { return color4_t(T(0.98),   T(0.98),    T(0.824),   T(1)); }
    static color4_t lightGray()            { return color4_t(T(0.827),  T(0.827),   T(0.827),   T(1)); }
    static color4_t lightGreen()           { return color4_t(T(0.565),  T(0.933),   T(0.565),   T(1)); }
    static color4_t lightPink()            { return color4_t(T(1),      T(0.714),   T(0.757),   T(1)); }
    static color4_t lightSalmon()          { return color4_t(T(1),      T(0.627),   T(0.478),   T(1)); }
    static color4_t lightSeaGreen()        { return color4_t(T(0.125),  T(0.698),   T(0.667),   T(1)); }
    static color4_t lightSkyBlue()         { return color4_t(T(0.529),  T(0.808),   T(0.98),    T(1)); }
    static color4_t lightSlateGray()       { return color4_t(T(0.467),  T(0.533),   T(0.6),     T(1)); }
    static color4_t lightSteelBlue()       { return color4_t(T(0.69),   T(0.769),   T(0.871),   T(1)); }
    static color4_t lightYellow()          { return color4_t(T(1),      T(1),       T(0.878),   T(1)); }
    static color4_t lime()                 { return color4_t(T(0),      T(1),       T(0),       T(1)); }
    static color4_t limeGreen()            { return color4_t(T(0.196),  T(0.804),   T(0.196),   T(1)); }
    static color4_t linen()                { return color4_t(T(0.98),   T(0.941),   T(0.902),   T(1)); }
    static color4_t magenta()              { return color4_t(T(1),      T(0),       T(1),       T(1)); }
    static color4_t maroon()               { return color4_t(T(0.502),  T(0),       T(0),       T(1)); }
    static color4_t mediumAquamarine()     { return color4_t(T(0.4),    T(0.804),   T(0.667),   T(1)); }
    static color4_t mediumBlue()           { return color4_t(T(0),      T(0),       T(0.804),   T(1)); }
    static color4_t mediumOrchid()         { return color4_t(T(0.729),  T(0.333),   T(0.827),   T(1)); }
    static color4_t mediumPurple()         { return color4_t(T(0.576),  T(0.439),   T(0.859),   T(1)); }
    static color4_t mediumSeaGreen()       { return color4_t(T(0.235),  T(0.702),   T(0.443),   T(1)); }
    static color4_t mediumSlateBlue()      { return color4_t(T(0.482),  T(0.408),   T(0.933),   T(1)); }
    static color4_t mediumSpringGreen()    { return color4_t(T(0),      T(0.98),    T(0.604),   T(1)); }
    static color4_t mediumTurquoise()      { return color4_t(T(0.282),  T(0.82),    T(0.8),     T(1)); }
    static color4_t mediumVioletRed()      { return color4_t(T(0.78),   T(0.0824),  T(0.522),   T(1)); }
    static color4_t midnightBlue()         { return color4_t(T(0.098),  T(0.098),   T(0.439),   T(1)); }
    static color4_t mintCream()            { return color4_t(T(0.961),  T(1),       T(0.98),    T(1)); }
    static color4_t mistyRose()            { return color4_t(T(1),      T(0.894),   T(0.882),   T(1)); }
    static color4_t moccasin()             { return color4_t(T(1),      T(0.894),   T(0.71),    T(1)); }
    static color4_t navajoWhite()          { return color4_t(T(1),      T(0.871),   T(0.678),   T(1)); }
    static color4_t navy()                 { return color4_t(T(0),      T(0),       T(0.502),   T(1)); }
    static color4_t oldLace()              { return color4_t(T(0.992),  T(0.961),   T(0.902),   T(1)); }
    static color4_t olive()                { return color4_t(T(0.502),  T(0.502),   T(0),       T(1)); }
    static color4_t oliveDrab()            { return color4_t(T(0.42),   T(0.557),   T(0.137),   T(1)); }
    static color4_t orange()               { return color4_t(T(1),      T(0.647),   T(0),       T(1)); }
    static color4_t orangeRed()            { return color4_t(T(1),      T(0.271),   T(0),       T(1)); }
    static color4_t orchid()               { return color4_t(T(0.855),  T(0.439),   T(0.839),   T(1)); }
    static color4_t paleGoldenrod()        { return color4_t(T(0.933),  T(0.91),    T(0.667),   T(1)); }
    static color4_t paleGreen()            { return color4_t(T(0.596),  T(0.984),   T(0.596),   T(1)); }
    static color4_t paleTurquoise()        { return color4_t(T(0.686),  T(0.933),   T(0.933),   T(1)); }
    static color4_t paleVioletRed()        { return color4_t(T(0.859),  T(0.439),   T(0.576),   T(1)); }
    static color4_t papayaWhip()           { return color4_t(T(1),      T(0.937),   T(0.835),   T(1)); }
    static color4_t peachPuff()            { return color4_t(T(1),      T(0.855),   T(0.725),   T(1)); }
    static color4_t peru()                 { return color4_t(T(0.804),  T(0.522),   T(0.247),   T(1)); }
    static color4_t pink()                 { return color4_t(T(1),      T(0.753),   T(0.796),   T(1)); }
    static color4_t plum()                 { return color4_t(T(0.867),  T(0.627),   T(0.867),   T(1)); }
    static color4_t powderBlue()           { return color4_t(T(0.69),   T(0.878),   T(0.902),   T(1)); }
    static color4_t purple()               { return color4_t(T(0.502),  T(0),       T(0.502),   T(1)); }
    static color4_t red()                  { return color4_t(T(1),      T(0),       T(0),       T(1)); }
    static color4_t rosyBrown()            { return color4_t(T(0.737),  T(0.561),   T(0.561),   T(1)); }
    static color4_t royalBlue()            { return color4_t(T(0.255),  T(0.412),   T(0.882),   T(1)); }
    static color4_t saddleBrown()          { return color4_t(T(0.545),  T(0.271),   T(0.0745),  T(1)); }
    static color4_t salmon()               { return color4_t(T(0.98),   T(0.502),   T(0.447),   T(1)); }
    static color4_t sandyBrown()           { return color4_t(T(0.957),  T(0.643),   T(0.376),   T(1)); }
    static color4_t seaGreen()             { return color4_t(T(0.18),   T(0.545),   T(0.341),   T(1)); }
    static color4_t seaShell()             { return color4_t(T(1),      T(0.961),   T(0.933),   T(1)); }
    static color4_t sienna()               { return color4_t(T(0.627),  T(0.322),   T(0.176),   T(1)); }
    static color4_t silver()               { return color4_t(T(0.753),  T(0.753),   T(0.753),   T(1)); }
    static color4_t skyBlue()              { return color4_t(T(0.529),  T(0.808),   T(0.922),   T(1)); }
    static color4_t slateBlue()            { return color4_t(T(0.416),  T(0.353),   T(0.804),   T(1)); }
    static color4_t slateGray()            { return color4_t(T(0.439),  T(0.502),   T(0.565),   T(1)); }
    static color4_t snow()                 { return color4_t(T(1),      T(0.98),    T(0.98),    T(1)); }
    static color4_t springGreen()          { return color4_t(T(0),      T(1),       T(0.498),   T(1)); }
    static color4_t steelBlue()            { return color4_t(T(0.275),  T(0.51),    T(0.706),   T(1)); }
    static color4_t tan()                  { return color4_t(T(0.824),  T(0.706),   T(0.549),   T(1)); }
    static color4_t teal()                 { return color4_t(T(0),      T(0.502),   T(0.502),   T(1)); }
    static color4_t thistle()              { return color4_t(T(0.847),  T(0.749),   T(0.847),   T(1)); }
    static color4_t tomato()               { return color4_t(T(1),      T(0.388),   T(0.278),   T(1)); }
    static color4_t transparent()          { return color4_t(T(1),      T(1),       T(1),       T(0)); }
    static color4_t turquoise()            { return color4_t(T(0.251),  T(0.878),   T(0.816),   T(1)); }
    static color4_t violet()               { return color4_t(T(0.933),  T(0.51),    T(0.933),   T(1)); }
    static color4_t wheat()                { return color4_t(T(0.961),  T(0.871),   T(0.702),   T(1)); }
    static color4_t white()                { return color4_t(T(1),      T(1),       T(1),       T(1)); }
    static color4_t whiteSmoke()           { return color4_t(T(0.961),  T(0.961),   T(0.961),   T(1)); }
    static color4_t yellow()               { return color4_t(T(1),      T(1),       T(0),       T(1)); }
    static color4_t yellowGreen()          { return color4_t(T(0.604),  T(0.804),   T(0.196),   T(1)); }
};

template<class T>
color4_t<T> clamp(const color4_t<T>& c, T min, T max) {
    auto r = (c.r > max) ? max : ((c.r < min) ? min : c.r);
    auto g = (c.g > max) ? max : ((c.g < min) ? min : c.g);
    auto b = (c.b > max) ? max : ((c.b < min) ? min : c.b);
    auto a = (c.a > max) ? max : ((c.a < min) ? min : c.a);
    return color4_t<T>(r, g, b, a);
}

template<class T>
color4_t<T> lerp(const color4_t<T>& min, const color4_t<T>& max, T scale) {
    auto r = min.r + scale * (max.r - min.r);
    auto g = min.g + scale * (max.g - min.g);
    auto b = min.b + scale * (max.b - min.b);
    auto a = min.a + scale * (max.a - min.a);
    return color4_t<T>(r, g, b, a);
}

template<class T>
color4_t<T> saturate(const color4_t<T>& c) {
    return clamp<T>(c, 0, 1);
}
