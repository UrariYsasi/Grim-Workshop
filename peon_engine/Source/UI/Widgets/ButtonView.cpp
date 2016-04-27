#include "PCH.hpp"
#include "ButtonView.hpp"

namespace grim
{

class Engine;

namespace ui
{

ButtonView::ButtonView(Engine* const engine, grim::graphics::Sprite* background) :
    Widget(engine),
    m_background(engine, background)
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