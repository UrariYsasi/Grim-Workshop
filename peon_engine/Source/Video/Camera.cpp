#include "PCH.hpp"
#include "Camera.hpp"
#include "../Engine.hpp"

namespace grim
{

namespace graphics
{

Camera::Camera(grim::Engine* engine, uint32_t width, uint32_t height, float zNear, float zFar) :
    m_engine(engine),
    m_position(0.0f),
    m_rotation(0.0f),
    m_viewMatrix(1.0f),
    m_width(width),
    m_height(height),
    m_zNear(zNear),
    m_zFar(zFar),
    m_projectionMatrix(glm::ortho(0.0f, static_cast<float>(m_width), static_cast<float>(m_height), 0.0f, zNear, zFar))
{
}

Camera::~Camera()
{
}

void Camera::SetPosition(const glm::vec2& position)
{
    m_position = position;
}

void Camera::SetCenter(const glm::vec2& position)
{
    m_position = position - glm::vec2(m_width / 2.0f, m_height / 2.0f);
}

glm::vec2 Camera::GetPosition() const
{
    return m_position;
}

glm::mat4 Camera::GetViewMatrix() const
{
    return m_viewMatrix;
}

glm::mat4 Camera::GetProjectionMatrix() const
{
    return m_projectionMatrix;
}

float Camera::GetWidth() const
{
    return m_width;
}

float Camera::GetHeight() const
{
    return m_height;
}

void Camera::Activate()
{
    // Transform the Camera
    m_viewMatrix = glm::mat4(1.0);
    m_viewMatrix = glm::translate(m_viewMatrix, -glm::vec3(m_position, 0.0f));
    m_viewMatrix = glm::rotate(m_viewMatrix, m_rotation.x, glm::vec3(1.0, 0.0, 0.0));
    m_viewMatrix = glm::rotate(m_viewMatrix, m_rotation.y, glm::vec3(0.0, 1.0, 0.0));
    m_viewMatrix = glm::rotate(m_viewMatrix, m_rotation.z, glm::vec3(0.0, 0.0, 1.0));

    // Set the renderers active Camera
    m_engine->GetRenderer()->SetActiveCamera(this);
}

void Camera::Move(const glm::vec2& movement)
{
    m_position += movement;
}

glm::vec2 Camera::ConvertToWorld(const glm::vec2& coord)
{
    return (coord + m_position);
}

glm::vec2 Camera::ConvertToScreen(const glm::vec2& coord)
{
    return (coord - m_position);
}

}

}