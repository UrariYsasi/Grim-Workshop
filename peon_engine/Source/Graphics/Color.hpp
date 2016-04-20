#pragma once

namespace grim
{

namespace graphics
{

/*
    An RGBA color.
*/
struct Color
{
    float r;
    float g;
    float b;
    float a;

    Color(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f) :
        r(r),
        g(g),
        b(b),
        a(a)
    {
    }

    inline bool Color::operator==(const Color& other)
    {
        return (r == other.r) && (g == other.g) && (b == other.b) && (a == other.a);
    }

    inline bool Color::operator!=(const Color& other)
    {
        return (r != other.r) && (g != other.g) && (b != other.b) && (a != other.a);
    }
};

}

}