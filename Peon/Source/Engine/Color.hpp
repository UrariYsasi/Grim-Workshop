#pragma once

namespace grim
{

/*
    An RGBA color.
*/
struct Color
{
    double r;
    double g;
    double b;
    double a;

    Color(double r = 1.0, double g = 1.0, double b = 1.0, double a = 1.0) :
        r(r),
        g(g),
        b(b),
        a(a)
    {
    }
};

}