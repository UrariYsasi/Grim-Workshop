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

// TODO: IMPLEMENT
/*
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

Vector2D Vector2D::operator+(const Vector2D& other)
{
    Vector2D vec;
    vec.m_x = m_x + other.m_x;
    vec.m_y = m_y + other.m_y;

    return vec;
}

Vector2D Vector2D::operator+(const Vector2D& other) const
{
    Vector2D vec;
    vec.m_x = m_x + other.m_x;
    vec.m_y = m_y + other.m_y;

    return vec;
}

void Vector2D::operator+=(const Vector2D& other)
{
    m_x += other.m_x;
    m_y += other.m_y;
}

Vector2D Vector2D::operator+(const double& val)
{
    Vector2D vec;
    vec.m_x = m_x + val;
    vec.m_y = m_y + val;

    return vec;
}

Vector2D Vector2D::operator-(const double& val)
{
    Vector2D vec;
    vec.m_x = m_x - val;
    vec.m_y = m_y - val;

    return vec;
}

Vector2D Vector2D::operator/(const double& val)
{
    Vector2D vec;
    vec.m_x = m_x / val;
    vec.m_y = m_y / val;

    return vec;
}

void Vector2D::operator/=(const double& val)
{
    m_x = m_x / val;
    m_y = m_y / val;
}

Vector2D Vector2D::operator-(const Vector2D& other)
{
    Vector2D vec;
    vec.m_x = m_x - other.m_x;
    vec.m_y = m_y - other.m_y;

    return vec;
}

void Vector2D::operator-=(const Vector2D& other)
{
    m_x = m_x - other.m_x;
    m_y = m_y - other.m_y;
}

Vector2D Vector2D::operator*(const Vector2D& other)
{
    Vector2D vec;
    vec.m_x = m_x * other.m_x;
    vec.m_y = m_y * other.m_y;

    return vec;
}

Vector2D Vector2D::operator*(const double& scalar)
{
    Vector2D vec;
    vec.m_x = m_x * scalar;
    vec.m_y = m_y * scalar;

    return vec;
}

bool Vector2D::operator==(const Vector2D& other)
{
    return (m_x == other.m_x && m_y == other.m_y);
}

bool Vector2D::operator!=(const Vector2D& other)
{
    return (m_x != other.m_x || m_y != other.m_y);
}

Vector2D Vector2D::Normalize(Vector2D vec)
{
    return Vector2D(vec.GetX() / Vector2D::Magnitude(vec), vec.GetY() / Vector2D::Magnitude(vec));
}

double Vector2D::Distance(Vector2D left, Vector2D right)
{
    return Vector2D::Magnitude(right - left);
}

double Vector2D::Magnitude(Vector2D vec)
{
    return sqrt((vec.GetX() * vec.GetX()) + (vec.GetY() * vec.GetY()));
}
*/
