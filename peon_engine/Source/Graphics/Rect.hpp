#pragma once

namespace grim
{

namespace graphics
{

struct Rect
{
    float x;
    float y;
    float width;
    float height;

    Rect(float x = 0, float y = 0, float width = 0, float height = 0) :
        x(x),
        y(y),
        width(width),
        height(height)
    {
    }

    inline bool ContainsPoint(const glm::vec2& point);
    inline bool ContainsPoint(const glm::vec2& point) const;
};

inline bool Rect::ContainsPoint(const glm::vec2& point)
{
    float left = x;
    float right = x + width;
    float top = y;
    float bottom = y + height;

    return (point.x >= left) && (point.x <= right) && (point.y >= top) && (point.y <= bottom);

    return false;
}

inline bool Rect::ContainsPoint(const glm::vec2& point) const
{
    float left = x;
    float right = x + width;
    float top = y;
    float bottom = y + height;

    return (point.x >= left) && (point.x <= right) && (point.y >= top) && (point.y <= bottom);

    return false;
}

}

}