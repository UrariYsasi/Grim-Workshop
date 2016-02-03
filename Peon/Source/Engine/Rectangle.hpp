#pragma once

struct Rectangle
{
    double x;
    double y;
    double width;
    double height;

    Rectangle(double x = 0, double y = 0, double width = 0, double height = 0) :
        x(x),
        y(y),
        width(width),
        height(height)
    {
    }
};