#include "PCH.hpp"
#include "Widget.hpp"

namespace grim
{

namespace ui
{

Widget::Widget() :
    m_position(0.0f),
    m_rotation(0.0f),
    m_scale(1.0f),
    m_parent(nullptr),
    m_width(0),
    m_height(0)
{
}

Widget::~Widget()
{
}

void Widget::OnClick()
{
    grim::utility::Debug::Log("Clicked widget at position (%f, %f)", m_position.x, m_position.y);
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

void Widget::SetWidth(uint32_t width)
{
    m_width = width;
}

void Widget::SetHeight(uint32_t height)
{
    m_height = height;
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

}

}