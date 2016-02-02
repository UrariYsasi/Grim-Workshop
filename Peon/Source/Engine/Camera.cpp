#include "PCH.hpp"
#include "Camera.hpp"

Camera::Camera(const Vector2D& position) :
    m_position(position)
{
}

Camera::~Camera()
{
}

void Camera::SetPosition(const Vector2D& position)
{
    m_position = position;
}

Vector2D Camera::GetPosition() const
{
    return m_position;
}

void Camera::Move(const Vector2D& movement)
{
    m_position += movement;
}