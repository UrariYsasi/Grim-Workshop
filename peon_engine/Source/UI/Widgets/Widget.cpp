#include "PCH.hpp"
#include "Widget.hpp"

namespace grim
{

namespace ui
{

Widget::Widget(Engine* engine) :
    m_engine(engine),
    m_position(0.0f),
    m_zLayer(1.0f),
    m_rotation(0.0f),
    m_scale(1.0f),
    m_parent(nullptr),
    m_width(0),
    m_height(0),
    m_isVisible(true)
{
}

Widget::~Widget()
{
    for (Widget* widget : m_widgets)
    {
        if (widget != nullptr)
        {
            delete (widget);
        }
    }

    m_widgets.clear();
}

void Widget::Update(float deltaTime)
{
    for (Widget* widget : m_widgets)
    {
        widget->Update(deltaTime);
    }
}

void Widget::Render()
{
    for (Widget* widget : m_widgets)
    {
        if (!widget->IsVisible()) { continue; }
        widget->Render();
    }
}

void Widget::OnClick(const glm::vec2& mousePosition)
{
    for (Widget* widget : m_widgets)
    {
        if (!widget->IsVisible()) { continue; }
        grim::graphics::Rect bounds = widget->GetLocalBounds();

        if (bounds.ContainsPoint(mousePosition))
        {
            widget->OnClick(mousePosition);
            return;
        }
    }

    if (m_callbackOnClick != nullptr)
    {
        m_callbackOnClick();
    }
}

void Widget::RegisterWidget(grim::ui::Widget* widget)
{
    widget->SetParent(this);
    m_widgets.push_back(widget);
}

void Widget::SetParent(grim::ui::Widget* widget)
{
    m_parent = widget;
}

void Widget::SetPosition(const glm::vec2& position)
{
    m_position = position;
}

void Widget::SetRotation(float rotation)
{
    m_rotation = rotation;
}

void Widget::SetScale(const glm::vec2& scale)
{
    m_scale = scale;
}

void Widget::SetZLayer(const float zLayer)
{
    m_zLayer = zLayer;
}

void Widget::SetWidth(uint32_t width)
{
    m_width = width;
}

void Widget::SetHeight(uint32_t height)
{
    m_height = height;
}

void Widget::SetVisible(bool visible)
{
    m_isVisible = visible;
}

void Widget::SetOnClick(std::function<void()> callback)
{
    m_callbackOnClick = callback;
}

glm::vec2 Widget::GetPosition() const
{
    return m_position;
}

float Widget::GetRotation() const
{
    return m_rotation;
}

glm::vec2 Widget::GetScale() const
{
    return m_scale;
}

uint32_t Widget::GetWidth() const
{
    return m_width;
}

uint32_t Widget::GetHeight() const
{
    return m_height;
}

grim::graphics::Rect Widget::GetBounds() const
{
    grim::graphics::Rect bounds;
    bounds.x = m_position.x - ((m_width * m_scale.x) / 2.0);
    bounds.y = m_position.y - ((m_height * m_scale.y) / 2.0);
    bounds.width = (m_width * m_scale.x);
    bounds.height = (m_height * m_scale.y);

    return bounds;
}

grim::graphics::Rect Widget::GetLocalBounds() const
{
    grim::graphics::Rect bounds = GetBounds();
    bounds.x += m_parent->GetPosition().x;
    bounds.y += m_parent->GetPosition().y;

    return bounds;
}

bool Widget::IsVisible() const
{
    return m_isVisible;
}

}

}