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

    Rect(float x = 0.0f, float y = 0.0f, float width = 0.0f, float height = 0.0f) :
        x(x),
        y(y),
        width(width),
        height(height)
    {
    }

    inline bool ContainsPoint(const glm::vec2& point)
    {
        float left = x;
        float right = x + width;
        float top = y;
        float bottom = y + height;

        return (point.x >= left) && (point.x <= right) && (point.y >= top) && (point.y <= bottom);
    }

    inline bool ContainsPoint(const glm::vec2& point) const
    {
        float left = x;
        float right = x + width;
        float top = y;
        float bottom = y + height;

        return (point.x >= left) && (point.x <= right) && (point.y >= top) && (point.y <= bottom);
    }

    inline bool IsCollidingWith(const Rect other)
    {
        float leftA = x;
        float rightA = x + width;
        float topA = y;
        float bottomA = y + height;

        float leftB = other.x;
        float rightB = other.x + other.width;
        float topB = other.y;
        float bottomB = other.y + other.height;

        return !((leftB > rightA)
               || (rightB < leftA)
               || (topB > bottomA)
               || (bottomB < topA));
    }
};

}

}