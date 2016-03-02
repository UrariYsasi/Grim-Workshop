#pragma once

struct Vector2D
{
    double x;
    double y;

    Vector2D(double x = 0, double y = 0) :
        x(x),
        y(y)
    {
    }

    inline void operator+=(const Vector2D& other);
    inline Vector2D operator+(const Vector2D& other);
    inline Vector2D operator+(const Vector2D& other) const;
    inline void operator+=(const double& val);
    inline Vector2D operator+(const double& val);
    inline Vector2D operator+(const double& val) const;

    inline void operator-=(const Vector2D& other);
    inline Vector2D operator-(const Vector2D& other);
    inline Vector2D operator-(const Vector2D& other) const;
    inline void operator-=(const double& val);
    inline Vector2D operator-(const double& val);
    inline Vector2D operator-(const double& val) const;

    inline void operator*=(const Vector2D& other);
    inline Vector2D operator*(const Vector2D& other);
    inline Vector2D operator*(const Vector2D& other) const;
    inline void operator*=(const double& val);
    inline Vector2D operator*(const double& val);
    inline Vector2D operator*(const double& val) const;

    inline void operator/=(const Vector2D& other);
    inline Vector2D operator/(const Vector2D& other);
    inline Vector2D operator/(const Vector2D& other) const;
    inline void operator/=(const double& val);
    inline Vector2D operator/(const double& val);
    inline Vector2D operator/(const double& val) const;

    inline void operator=(const Vector2D& other);
    inline bool operator==(const Vector2D& other) const;
    inline bool operator!=(const Vector2D& other) const;

    inline void Rotate(const double& radians);
    inline void Normalize();

    inline static double Distance(Vector2D left, Vector2D right);
    inline static double Magnitude(Vector2D vec);
};

inline void Vector2D::operator+=(const Vector2D& other)
{
    x += other.x;
    y += other.y;
}

inline Vector2D Vector2D::operator+(const Vector2D& other)
{
    return Vector2D(x + other.x, y + other.y);
}

inline Vector2D Vector2D::operator+(const Vector2D& other) const
{
    return Vector2D(x + other.x, y + other.y);
}

inline void Vector2D::operator+=(const double& val)
{
    x += val;
    y += val;
}

inline Vector2D Vector2D::operator+(const double& val)
{
    return Vector2D(x + val, y + val);
}

inline Vector2D Vector2D::operator+(const double& val) const
{
    return Vector2D(x + val, y + val);
}

inline void Vector2D::operator-=(const Vector2D& other)
{
    x -= other.x;
    y -= other.y;
}

inline Vector2D Vector2D::operator-(const Vector2D& other)
{
    return Vector2D(x - other.x, y - other.y);
}

inline Vector2D Vector2D::operator-(const Vector2D& other) const
{
    return Vector2D(x - other.x, y - other.y);
}

inline void Vector2D::operator-=(const double& val)
{
    x -= val;
    y -= val;
}

inline Vector2D Vector2D::operator-(const double& val)
{
    return Vector2D(x - val, y - val);
}

inline Vector2D Vector2D::operator-(const double& val) const
{
    return Vector2D(x - val, y - val);
}

inline void Vector2D::operator*=(const Vector2D& other)
{
    x *= other.x;
    y *= other.y;
}

inline Vector2D Vector2D::operator*(const Vector2D& other)
{
    return Vector2D(x * other.x, y * other.y);
}

inline Vector2D Vector2D::operator*(const Vector2D& other) const
{
    return Vector2D(x * other.x, y * other.y);
}

inline void Vector2D::operator*=(const double& val)
{
    x *= val;
    y *= val;
}

inline Vector2D Vector2D::operator*(const double& val)
{
    return Vector2D(x * val, y * val);
}

inline Vector2D Vector2D::operator*(const double& val) const
{
    return Vector2D(x * val, y * val);
}

inline void Vector2D::operator/=(const Vector2D& other)
{
    x /= other.x;
    y /= other.y;
}

inline Vector2D Vector2D::operator/(const Vector2D& other)
{
    return Vector2D(x / other.x, y / other.y);
}

inline Vector2D Vector2D::operator/(const Vector2D& other) const
{
    return Vector2D(x / other.x, y / other.y);
}

inline void Vector2D::operator/=(const double& val)
{
    x /= val;
    y /= val;
}

inline Vector2D Vector2D::operator/(const double& val)
{
    return Vector2D(x / val, y / val);
}

inline Vector2D Vector2D::operator/(const double& val) const
{
    return Vector2D(x / val, y / val);
}

inline void Vector2D::operator=(const Vector2D& other)
{
    x = other.x;
    y = other.y;
}

inline bool Vector2D::operator==(const Vector2D& other) const
{
    return (x == other.x && y == other.y);
}

inline bool Vector2D::operator!=(const Vector2D& other) const
{
    return (x != other.x || y != other.y);
}

inline void Vector2D::Rotate(const double& degrees)
{
    double radians = degrees * (M_PI / 180.0);
    double newX = x * cos(radians) - y * sin(radians);
    double newY = x * sin(radians) + y * cos(radians);

    x = newX;
    y = newY;
}

inline void Vector2D::Normalize()
{
    double magnitude = Vector2D::Magnitude(*this);
    x /= magnitude;
    y /= magnitude;
}

inline double Vector2D::Distance(Vector2D left, Vector2D right)
{
    return Vector2D::Magnitude(right - left);
}

inline double Vector2D::Magnitude(Vector2D vec)
{
    return sqrt((vec.x * vec.x) + (vec.y * vec.y));
}

// Hash
namespace std {
    template <>
    struct hash<Vector2D>
    {
        inline std::size_t operator()(const Vector2D& vec) const
        {
            return ((hash<double>()(vec.x)
                ^ (hash<double>()(vec.y) << 1)) >> 1);
        }
    };
}

namespace std {
template <>
struct hash<glm::vec2>
{
    inline std::size_t operator()(const glm::vec2& vec) const
    {
        return ((hash<float>()(vec.x)
            ^ (hash<float>()(vec.y) << 1)) >> 1);
    }
};
}