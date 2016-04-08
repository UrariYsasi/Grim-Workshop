#include "PCH.hpp"
#include "Camera.hpp"

namespace grim
{

namespace graphics
{

// TODO take Engine* instead
// Need to refactor Renderer first
Camera::Camera(grim::graphics::IRenderer* renderer, float width, float height, float zNear, float zFar) :
    m_renderer(renderer),
    m_position(0.0f),
    m_rotation(0.0f),
    m_viewMatrix(1.0f),
    m_width(width),
    m_height(height),
    m_zNear(zNear),
    m_zFar(zFar),
    m_projectionMatrix(glm::ortho(0.0f, m_width, m_height, 0.0f, zNear, zFar))
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

void Camera::Activate()
{
    // Transform the Camera
    m_viewMatrix = glm::mat4(1.0);
    m_viewMatrix = glm::translate(m_viewMatrix, -glm::vec3(m_position, 0.0f));
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
    return (coord + m_position);
}

glm::vec2 Camera::ConvertToScreen(const glm::vec2& coord)
{
    return (coord - m_position);
}

}

}