#pragma once

namespace grim
{

struct Color
{
    double r;
    double g;
    double b;
    double a;

    Color(double r = 0.0, double g = 0.0, double b = 0.0, double a = 1.0) :
        r(r),
        g(g),
        b(b),
        a(a)
    {
    }
};

}