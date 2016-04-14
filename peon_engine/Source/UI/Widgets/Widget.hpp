#pragma once

namespace grim
{

namespace ui
{

class Widget
{
public:
    Widget();
    ~Widget();

    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;

    void SetParent(grim::ui::Widget* widget);
    void SetPosition(const glm::vec2& position);
    void SetRotation(float rotation);
    void SetScale(const glm::vec2& scale);
    glm::vec2 GetPosition() const;
    float GetRotation() const;
    glm::vec2 GetScale() const;

protected:
    glm::vec2 m_position;
    float m_rotation;
    glm::vec2 m_scale;
    grim::ui::Widget* m_parent;
};

}

}