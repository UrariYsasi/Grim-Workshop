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

    inline bool ContainsPoint(const Vector2D& point);
};

inline bool Rectangle::ContainsPoint(const Vector2D& point)
{
    double left = x;
    double right = x + width;
    double top = y;
    double bottom = y + height;

    return (point.x >= left) && (point.x <= right) && (point.y >= top) && (point.y <= bottom);

    return false;
}