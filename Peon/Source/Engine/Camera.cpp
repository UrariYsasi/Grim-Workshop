#include "PCH.hpp"
#include "Camera.hpp"
#include "Renderer.hpp"

namespace grim
{

Camera::Camera(grim::Renderer* renderer) :
    m_renderer(renderer),
    m_position(0.0f),
    m_rotation(0.0f),
    m_viewMatrix(1.0f),
    m_projectionMatrix(1.0f)
{
    // Set the projection to orthographic
    m_projectionMatrix = glm::ortho(0.0f, 1024.0f, 768.0f, 0.0f, -1.0f, 1.0f);
}

Camera::~Camera()
{
}

void Camera::SetPosition(const glm::vec2& position)
{
    m_position = position;
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

void Camera::Activate()
{
    // Transform the Camera
    m_viewMatrix = glm::mat4(1.0);
    m_viewMatrix = glm::translate(m_viewMatrix, -glm::vec3(m_position, 0));
    m_viewMatrix = glm::rotate(m_viewMatrix, m_rotation.x, glm::vec3(1.0, 0.0, 0.0));
    m_viewMatrix = glm::rotate(m_viewMatrix, m_rotation.y, glm::vec3(0.0, 1.0, 0.0));
    m_viewMatrix = glm::rotate(m_viewMatrix, m_rotation.z, glm::vec3(0.0, 0.0, 1.0));

    // Set the renderers active Camera
    m_renderer->SetActiveCamera(this);
}

void Camera::Move(const glm::vec2& movement)
{
    m_position += movement;
}

glm::vec2 Camera::ConvertToWorld(const glm::vec2& coord)
{
    Debug::Log("Implement ConvertToWorld()");
    //return (coord + m_position);
    return glm::vec2(0);
}

glm::vec2 Camera::ConvertToScreen(const glm::vec2& coord)
{
    Debug::Log("Implement ConvertToScreen()");
   // return (coord - m_position);
    return glm::vec2(0);
}

}