#pragma once

namespace grim
{

class Engine;

namespace graphics
{

class Camera
{
public:
    Camera(grim::Engine* engine, float width, float height, float zNear, float zFar);
    ~Camera();

    void SetPosition(const glm::vec2& position);
    void SetCenter(const glm::vec2& position);

    glm::vec2 GetPosition() const;
    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;
    float GetWidth() const;
    float GetHeight() const;

    void Activate();
    void Move(const glm::vec2& movement);
    glm::vec2 ConvertToWorld(const glm::vec2& coord);
    glm::vec2 ConvertToScreen(const glm::vec2& coord);

private:
    grim::Engine* m_engine;
    glm::vec2 m_position;
    glm::vec3 m_rotation;

    float m_width;
    float m_height;
    float m_zNear;
    float m_zFar;
    glm::mat4 m_viewMatrix;
    glm::mat4 m_projectionMatrix;
};

}

}