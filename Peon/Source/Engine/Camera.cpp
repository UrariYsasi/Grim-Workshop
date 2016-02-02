#include "PCH.hpp"
#include "Camera.hpp"
#include "Renderer.hpp"

Camera::Camera(Renderer* renderer, const Vector2D& position) :
    m_renderer(renderer),
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

void Camera::Activate()
{
    m_renderer->SetActiveCamera(this);
}

void Camera::Move(const Vector2D& movement)
{
    m_position += movement;
}