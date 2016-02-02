#pragma once

class Camera
{
public:
    Camera(const Vector2D& position);
    ~Camera();

    void SetPosition(const Vector2D& position);
    Vector2D GetPosition() const;

    void Move(const Vector2D& movement);

private:
    Vector2D m_position;
};