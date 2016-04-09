#include "PCH.hpp"
#include "Widget.hpp"

namespace grim
{

namespace ui
{

Widget::Widget() :
    m_position(0.0f)
{
}

Widget::~Widget()
{
}

void Widget::SetPosition(const glm::vec2& position)
{
    m_position = position;
}

glm::vec2 Widget::GetPosition() const
{
    return m_position;
}

}

}