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
    m_parent(nullptr)
{
}

Widget::~Widget()
{
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

}

}