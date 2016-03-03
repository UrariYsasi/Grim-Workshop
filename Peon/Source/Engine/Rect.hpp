#pragma once

struct Rect
{
    double x;
    double y;
    double width;
    double height;

    Rect(double x = 0, double y = 0, double width = 0, double height = 0) :
        x(x),
        y(y),
        width(width),
        height(height)
    {
    }

    inline bool ContainsPoint(const glm::vec2& point);
};

inline bool Rect::ContainsPoint(const glm::vec2& point)
{
    double left = x;
    double right = x + width;
    double top = y;
    double bottom = y + height;

    return (point.x >= left) && (point.x <= right) && (point.y >= top) && (point.y <= bottom);

    return false;
}