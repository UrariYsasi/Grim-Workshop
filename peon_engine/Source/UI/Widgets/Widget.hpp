#pragma once

namespace grim
{

namespace ui
{

class Widget
{
public:
    Widget();
    virtual ~Widget();

    virtual void Update(float deltaTime);
    virtual void Render();
    virtual void OnClick(const glm::vec2& mousePosition);
    virtual void RegisterWidget(grim::ui::Widget* widget);

    void SetParent(grim::ui::Widget* widget);
    void SetPosition(const glm::vec2& position);
    void SetRotation(float rotation);
    void SetScale(const glm::vec2& scale);
    void SetWidth(uint32_t width);
    void SetHeight(uint32_t height);
    void SetVisible(bool visible);
    void SetOnClick(std::function<void()> callback);
    glm::vec2 GetPosition() const;
    float GetRotation() const;
    glm::vec2 GetScale() const;
    uint32_t GetWidth() const;
    uint32_t GetHeight() const;
    grim::graphics::Rect GetBounds() const;
    grim::graphics::Rect GetLocalBounds() const;
    bool IsVisible() const;

protected:
    glm::vec2 m_position;
    float m_rotation;
    glm::vec2 m_scale;
    grim::ui::Widget* m_parent;
    uint32_t m_width;
    uint32_t m_height;
    bool m_isVisible;
    std::list<grim::ui::Widget*> m_widgets;
    std::function<void()> m_callbackOnClick;
};

}

}