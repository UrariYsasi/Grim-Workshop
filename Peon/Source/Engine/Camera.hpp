#pragma once

class Renderer;

class Camera
{
public:
    Camera(Renderer* renderer, const Vector2D& position);
    ~Camera();

    void SetPosition(const Vector2D& position);
    Vector2D GetPosition() const;

    void Activate();
    void Move(const Vector2D& movement);
    Vector2D ConvertToWorld(const Vector2D& coord);
    Vector2D ConvertToScreen(const Vector2D& coord);

private:
    Renderer* m_renderer;
    Vector2D m_position;
};