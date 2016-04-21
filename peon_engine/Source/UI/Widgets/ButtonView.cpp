#include "PCH.hpp"
#include "ButtonView.hpp"

namespace grim
{

namespace ui
{

ButtonView::ButtonView(grim::graphics::Sprite* background) :
    m_background(background)
{
    m_width = m_background.GetWidth();
    m_height = m_background.GetHeight();
}

ButtonView::~ButtonView()
{
}

void ButtonView::Update(float deltaTime)
{
    Widget::Update(deltaTime);

    m_background.Update(deltaTime);
    m_background.SetParent(m_parent);
    m_background.SetPosition(m_position);
    m_background.SetRotation(m_rotation);
    m_background.SetScale(m_scale);
}

void ButtonView::Render()
{
    Widget::Render();

    m_background.Render();
}

void ButtonView::OnClick(const glm::vec2& mousePosition)
{
    Widget::OnClick(mousePosition);
}

}

}