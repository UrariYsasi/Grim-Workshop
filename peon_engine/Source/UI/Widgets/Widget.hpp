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
    virtual void OnClick();

    void SetParent(grim::ui::Widget* widget);
    void SetPosition(const glm::vec2& position);
    void SetRotation(float rotation);
    void SetScale(const glm::vec2& scale);
    void SetWidth(uint32_t width);
    void SetHeight(uint32_t height);
    glm::vec2 GetPosition() const;
    float GetRotation() const;
    glm::vec2 GetScale() const;
    uint32_t GetWidth() const;
    uint32_t GetHeight() const;

protected:
    glm::vec2 m_position;
    float m_rotation;
    glm::vec2 m_scale;
    grim::ui::Widget* m_parent;
    uint32_t m_width;
    uint32_t m_height;
};

}

}