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
struct color3_t {
    T r, g, b;

    color3_t() : r(0), g(0), b(0) {}
    color3_t(T r, T g, T b) : r(r), g(g), b(b) {}

    color3_t operator * (const color3_t& c) const {
        return color3_t(r * c.r, g * c.g, b * c.b);
    }

    color3_t operator + (const color3_t& c) const {
        return color3_t(r + c.r, g + c.g, b + c.b);
    }

    color3_t operator - (const color3_t& c) const {
        return color3_t(r - c.r, g - c.g, b - c.b);
    }

    color3_t operator * (T f) const {
        return color3_t(r * f, g * f, b * f);
    }

    friend color3_t operator * (T f, const color3_t& c) {
        return color3_t(c.r * f, c.g * f, c.b * f);
    }

    color3_t operator / (T f) const {
        return color3_t(r / f, g / f, b / f);
    }

    color3_t& operator += (const color3_t& c) {
        r += c.r;
        g += c.g;
        b += c.b;
        return *this;
    }

    color3_t& operator -= (const color3_t& c) {
        r -= c.r;
        g -= c.g;
        b -= c.b;
        return *this;
    }

    color3_t& operator *= (const color3_t& c) {
        r *= c.r;
        g *= c.g;
        b *= c.b;
        return *this;
    }

    color3_t& operator /= (const color3_t& c) {
        r /= c.r;
        g /= c.g;
        b /= c.b;
        return *this;
    }

    color3_t& operator *= (T f) {
        r *= f;
        g *= f;
        b *= f;
        return *this;
    }

    color3_t& operator /= (T f) {
        r /= f;
        g /= f;
        b /= f;
        return *this;
    }

    bool operator == (const color3_t& c) const {
        return r == c.r && g == c.g && b == c.b;
    }

    bool operator != (const color3_t& c) const {
        return r != c.r || g != c.g || b != c.b;
    }

    bool operator < (const color3_t& c) const {
        return r < c.r && g < c.g && b < c.b;
    }

    color3_t<T> rgb()  const { return color3_t<T>(r, g, b);    }
    color3_t<T> bgr()  const { return color3_t<T>(b, g, r);    }
    color4_t<T> rgba() const { return color4_t<T>(r, g, b, 1); }
    color4_t<T> bgra() const { return color4_t<T>(b, g, r, 1); }

    static color3_t aliceBlue()            { return color3_t(T(0.941),  T(0.973),   T(1)     ); }
    static color3_t antiqueWhite()         { return color3_t(T(0.98),   T(0.922),   T(0.843) ); }
    static color3_t aqua()                 { return color3_t(T(0),      T(1),       T(1)     ); }
    static color3_t aquamarine()           { return color3_t(T(0.498),  T(1),       T(0.831) ); }
    static color3_t azure()                { return color3_t(T(0.941),  T(1),       T(1)     ); }
    static color3_t beige()                { return color3_t(T(0.961),  T(0.961),   T(0.863) ); }
    static color3_t bisque()               { return color3_t(T(1),      T(0.894),   T(0.769) ); }
    static color3_t black()                { return color3_t(T(0),      T(0),       T(0)     ); }
    static color3_t blanchedAlmond()       { return color3_t(T(1),      T(0.922),   T(0.804) ); }
    static color3_t blue()                 { return color3_t(T(0),      T(0),       T(1)     ); }
    static color3_t blueViolet()           { return color3_t(T(0.541),  T(0.169),   T(0.886) ); }
    static color3_t brown()                { return color3_t(T(0.647),  T(0.165),   T(0.165) ); }
    static color3_t burlyWood()            { return color3_t(T(0.871),  T(0.722),   T(0.529) ); }
    static color3_t cadetBlue()            { return color3_t(T(0.373),  T(0.62),    T(0.627) ); }
    static color3_t chartreuse()           { return color3_t(T(0.498),  T(1),       T(0)     ); }
    static color3_t chocolate()            { return color3_t(T(0.824),  T(0.412),   T(0.118) ); }
    static color3_t coral()                { return color3_t(T(1),      T(0.498),   T(0.314) ); }
    static color3_t cornflowerBlue()       { return color3_t(T(0.392),  T(0.584),   T(0.929) ); }
    static color3_t cornsilk()             { return color3_t(T(1),      T(0.973),   T(0.863) ); }
    static color3_t crimson()              { return color3_t(T(0.863),  T(0.0784),  T(0.235) ); }
    static color3_t cyan()                 { return color3_t(T(0),      T(1),       T(1)     ); }
    static color3_t darkBlue()             { return color3_t(T(0),      T(0),       T(0.545) ); }
    static color3_t darkCyan()             { return color3_t(T(0),      T(0.545),   T(0.545) ); }
    static color3_t darkGoldenrod()        { return color3_t(T(0.722),  T(0.525),   T(0.0431)); }
    static color3_t darkGray()             { return color3_t(T(0.663),  T(0.663),   T(0.663) ); }
    static color3_t darkGreen()            { return color3_t(T(0),      T(0.392),   T(0)     ); }
    static color3_t darkKhaki()            { return color3_t(T(0.741),  T(0.718),   T(0.42)  ); }
    static color3_t darkMagenta()          { return color3_t(T(0.545),  T(0),       T(0.545) ); }
    static color3_t darkOliveGreen()       { return color3_t(T(0.333),  T(0.42),    T(0.184) ); }
    static color3_t darkOrange()           { return color3_t(T(1),      T(0.549),   T(0)     ); }
    static color3_t darkOrchid()           { return color3_t(T(0.6),    T(0.196),   T(0.8)   ); }
    static color3_t darkRed()              { return color3_t(T(0.545),  T(0),       T(0)     ); }
    static color3_t darkSalmon()           { return color3_t(T(0.914),  T(0.588),   T(0.478) ); }
    static color3_t darkSeaGreen()         { return color3_t(T(0.561),  T(0.737),   T(0.545) ); }
    static color3_t darkSlateBlue()        { return color3_t(T(0.282),  T(0.239),   T(0.545) ); }
    static color3_t darkSlateGray()        { return color3_t(T(0.184),  T(0.31),    T(0.31)  ); }
    static color3_t darkTurquoise()        { return color3_t(T(0),      T(0.808),   T(0.82)  ); }
    static color3_t darkViolet()           { return color3_t(T(0.58),   T(0),       T(0.827) ); }
    static color3_t deepPink()             { return color3_t(T(1),      T(0.0784),  T(0.576) ); }
    static color3_t deepSkyBlue()          { return color3_t(T(0),      T(0.749),   T(1)     ); }
    static color3_t dimGray()              { return color3_t(T(0.412),  T(0.412),   T(0.412) ); }
    static color3_t dodgerBlue()           { return color3_t(T(0.118),  T(0.565),   T(1)     ); }
    static color3_t firebrick()            { return color3_t(T(0.698),  T(0.133),   T(0.133) ); }
    static color3_t floralWhite()          { return color3_t(T(1),      T(0.98),    T(0.941) ); }
    static color3_t forestGreen()          { return color3_t(T(0.133),  T(0.545),   T(0.133) ); }
    static color3_t fuchsia()              { return color3_t(T(1),      T(0),       T(1)     ); }
    static color3_t gainsboro()            { return color3_t(T(0.863),  T(0.863),   T(0.863) ); }
    static color3_t ghostWhite()           { return color3_t(T(0.973),  T(0.973),   T(1)     ); }
    static color3_t gold()                 { return color3_t(T(1),      T(0.843),   T(0)     ); }
    static color3_t goldenrod()            { return color3_t(T(0.855),  T(0.647),   T(0.125) ); }
    static color3_t gray()                 { return color3_t(T(0.502),  T(0.502),   T(0.502) ); }
    static color3_t green()                { return color3_t(T(0),      T(0.502),   T(0)     ); }
    static color3_t greenYellow()          { return color3_t(T(0.678),  T(1),       T(0.184) ); }
    static color3_t honeydew()             { return color3_t(T(0.941),  T(1),       T(0.941) ); }
    static color3_t hotPink()              { return color3_t(T(1),      T(0.412),   T(0.706) ); }
    static color3_t indianRed()            { return color3_t(T(0.804),  T(0.361),   T(0.361) ); }
    static color3_t indigo()               { return color3_t(T(0.294),  T(0),       T(0.51)  ); }
    static color3_t ivory()                { return color3_t(T(1),      T(1),       T(0.941) ); }
    static color3_t khaki()                { return color3_t(T(0.941),  T(0.902),   T(0.549) ); }
    static color3_t lavender()             { return color3_t(T(0.902),  T(0.902),   T(0.98)  ); }
    static color3_t lavenderBlush()        { return color3_t(T(1),      T(0.941),   T(0.961) ); }
    static color3_t lawnGreen()            { return color3_t(T(0.486),  T(0.988),   T(0)     ); }
    static color3_t lemonChiffon()         { return color3_t(T(1),      T(0.98),    T(0.804) ); }
    static color3_t lightBlue()            { return color3_t(T(0.678),  T(0.847),   T(0.902) ); }
    static color3_t lightCoral()           { return color3_t(T(0.941),  T(0.502),   T(0.502) ); }
    static color3_t lightCyan()            { return color3_t(T(0.878),  T(1),       T(1)     ); }
    static color3_t lightGoldenrodYellow() { return color3_t(T(0.98),   T(0.98),    T(0.824) ); }
    static color3_t lightGray()            { return color3_t(T(0.827),  T(0.827),   T(0.827) ); }
    static color3_t lightGreen()           { return color3_t(T(0.565),  T(0.933),   T(0.565) ); }
    static color3_t lightPink()            { return color3_t(T(1),      T(0.714),   T(0.757) ); }
    static color3_t lightSalmon()          { return color3_t(T(1),      T(0.627),   T(0.478) ); }
    static color3_t lightSeaGreen()        { return color3_t(T(0.125),  T(0.698),   T(0.667) ); }
    static color3_t lightSkyBlue()         { return color3_t(T(0.529),  T(0.808),   T(0.98)  ); }
    static color3_t lightSlateGray()       { return color3_t(T(0.467),  T(0.533),   T(0.6)   ); }
    static color3_t lightSteelBlue()       { return color3_t(T(0.69),   T(0.769),   T(0.871) ); }
    static color3_t lightYellow()          { return color3_t(T(1),      T(1),       T(0.878) ); }
    static color3_t lime()                 { return color3_t(T(0),      T(1),       T(0)     ); }
    static color3_t limeGreen()            { return color3_t(T(0.196),  T(0.804),   T(0.196) ); }
    static color3_t linen()                { return color3_t(T(0.98),   T(0.941),   T(0.902) ); }
    static color3_t magenta()              { return color3_t(T(1),      T(0),       T(1)     ); }
    static color3_t maroon()               { return color3_t(T(0.502),  T(0),       T(0)     ); }
    static color3_t mediumAquamarine()     { return color3_t(T(0.4),    T(0.804),   T(0.667) ); }
    static color3_t mediumBlue()           { return color3_t(T(0),      T(0),       T(0.804) ); }
    static color3_t mediumOrchid()         { return color3_t(T(0.729),  T(0.333),   T(0.827) ); }
    static color3_t mediumPurple()         { return color3_t(T(0.576),  T(0.439),   T(0.859) ); }
    static color3_t mediumSeaGreen()       { return color3_t(T(0.235),  T(0.702),   T(0.443) ); }
    static color3_t mediumSlateBlue()      { return color3_t(T(0.482),  T(0.408),   T(0.933) ); }
    static color3_t mediumSpringGreen()    { return color3_t(T(0),      T(0.98),    T(0.604) ); }
    static color3_t mediumTurquoise()      { return color3_t(T(0.282),  T(0.82),    T(0.8)   ); }
    static color3_t mediumVioletRed()      { return color3_t(T(0.78),   T(0.0824),  T(0.522) ); }
    static color3_t midnightBlue()         { return color3_t(T(0.098),  T(0.098),   T(0.439) ); }
    static color3_t mintCream()            { return color3_t(T(0.961),  T(1),       T(0.98)  ); }
    static color3_t mistyRose()            { return color3_t(T(1),      T(0.894),   T(0.882) ); }
    static color3_t moccasin()             { return color3_t(T(1),      T(0.894),   T(0.71)  ); }
    static color3_t navajoWhite()          { return color3_t(T(1),      T(0.871),   T(0.678) ); }
    static color3_t navy()                 { return color3_t(T(0),      T(0),       T(0.502) ); }
    static color3_t oldLace()              { return color3_t(T(0.992),  T(0.961),   T(0.902) ); }
    static color3_t olive()                { return color3_t(T(0.502),  T(0.502),   T(0)     ); }
    static color3_t oliveDrab()            { return color3_t(T(0.42),   T(0.557),   T(0.137) ); }
    static color3_t orange()               { return color3_t(T(1),      T(0.647),   T(0)     ); }
    static color3_t orangeRed()            { return color3_t(T(1),      T(0.271),   T(0)     ); }
    static color3_t orchid()               { return color3_t(T(0.855),  T(0.439),   T(0.839) ); }
    static color3_t paleGoldenrod()        { return color3_t(T(0.933),  T(0.91),    T(0.667) ); }
    static color3_t paleGreen()            { return color3_t(T(0.596),  T(0.984),   T(0.596) ); }
    static color3_t paleTurquoise()        { return color3_t(T(0.686),  T(0.933),   T(0.933) ); }
    static color3_t paleVioletRed()        { return color3_t(T(0.859),  T(0.439),   T(0.576) ); }
    static color3_t papayaWhip()           { return color3_t(T(1),      T(0.937),   T(0.835) ); }
    static color3_t peachPuff()            { return color3_t(T(1),      T(0.855),   T(0.725) ); }
    static color3_t peru()                 { return color3_t(T(0.804),  T(0.522),   T(0.247) ); }
    static color3_t pink()                 { return color3_t(T(1),      T(0.753),   T(0.796) ); }
    static color3_t plum()                 { return color3_t(T(0.867),  T(0.627),   T(0.867) ); }
    static color3_t powderBlue()           { return color3_t(T(0.69),   T(0.878),   T(0.902) ); }
    static color3_t purple()               { return color3_t(T(0.502),  T(0),       T(0.502) ); }
    static color3_t red()                  { return color3_t(T(1),      T(0),       T(0)     ); }
    static color3_t rosyBrown()            { return color3_t(T(0.737),  T(0.561),   T(0.561) ); }
    static color3_t royalBlue()            { return color3_t(T(0.255),  T(0.412),   T(0.882) ); }
    static color3_t saddleBrown()          { return color3_t(T(0.545),  T(0.271),   T(0.0745)); }
    static color3_t salmon()               { return color3_t(T(0.98),   T(0.502),   T(0.447) ); }
    static color3_t sandyBrown()           { return color3_t(T(0.957),  T(0.643),   T(0.376) ); }
    static color3_t seaGreen()             { return color3_t(T(0.18),   T(0.545),   T(0.341) ); }
    static color3_t seaShell()             { return color3_t(T(1),      T(0.961),   T(0.933) ); }
    static color3_t sienna()               { return color3_t(T(0.627),  T(0.322),   T(0.176) ); }
    static color3_t silver()               { return color3_t(T(0.753),  T(0.753),   T(0.753) ); }
    static color3_t skyBlue()              { return color3_t(T(0.529),  T(0.808),   T(0.922) ); }
    static color3_t slateBlue()            { return color3_t(T(0.416),  T(0.353),   T(0.804) ); }
    static color3_t slateGray()            { return color3_t(T(0.439),  T(0.502),   T(0.565) ); }
    static color3_t snow()                 { return color3_t(T(1),      T(0.98),    T(0.98)  ); }
    static color3_t springGreen()          { return color3_t(T(0),      T(1),       T(0.498) ); }
    static color3_t steelBlue()            { return color3_t(T(0.275),  T(0.51),    T(0.706) ); }
    static color3_t tan()                  { return color3_t(T(0.824),  T(0.706),   T(0.549) ); }
    static color3_t teal()                 { return color3_t(T(0),      T(0.502),   T(0.502) ); }
    static color3_t thistle()              { return color3_t(T(0.847),  T(0.749),   T(0.847) ); }
    static color3_t tomato()               { return color3_t(T(1),      T(0.388),   T(0.278) ); }
    static color3_t turquoise()            { return color3_t(T(0.251),  T(0.878),   T(0.816) ); }
    static color3_t violet()               { return color3_t(T(0.933),  T(0.51),    T(0.933) ); }
    static color3_t wheat()                { return color3_t(T(0.961),  T(0.871),   T(0.702) ); }
    static color3_t white()                { return color3_t(T(1),      T(1),       T(1)     ); }
    static color3_t whiteSmoke()           { return color3_t(T(0.961),  T(0.961),   T(0.961) ); }
    static color3_t yellow()               { return color3_t(T(1),      T(1),       T(0)     ); }
    static color3_t yellowGreen()          { return color3_t(T(0.604),  T(0.804),   T(0.196) ); }
};

template<class T>
color3_t<T> clamp(const color3_t<T>& c, T min, T max) {
    auto r = (c.r > max) ? max : ((c.r < min) ? min : c.r);
    auto g = (c.g > max) ? max : ((c.g < min) ? min : c.g);
    auto b = (c.b > max) ? max : ((c.b < min) ? min : c.b);
    return color3_t<T>(r, g, b);
}

template<class T>
color3_t<T> lerp(const color3_t<T>& min, const color3_t<T>& max, T scale) {
    auto r = min.r + scale * (max.r - min.r);
    auto g = min.g + scale * (max.g - min.g);
    auto b = min.b + scale * (max.b - min.b);
    return color3_t<T>(r, g, b);
}

template<class T>
color3_t<T> saturate(const color3_t<T>& c) {
    return clamp<T>(c, 0, 1);
}
