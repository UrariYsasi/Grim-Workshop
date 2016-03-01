#pragma once

namespace grim
{

class Renderer;

class Camera
{
public:
    Camera(grim::Renderer* renderer);
    ~Camera();

    void SetPosition(const glm::vec3& position);
    glm::vec3 GetPosition() const;
    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;
    
    void Activate();
    void Move(const glm::vec3& movement);
    Vector2D ConvertToWorld(const Vector2D& coord);
    Vector2D ConvertToScreen(const Vector2D& coord);

private:
    grim::Renderer* m_renderer;
    glm::vec3 m_position;
    glm::vec3 m_rotation;

    /*
        The view matrix of the Camera.
    */
    glm::mat4 m_viewMatrix;

    /*
        The projection matrix of the Camera.
    */
    glm::mat4 m_projectionMatrix;
};

}