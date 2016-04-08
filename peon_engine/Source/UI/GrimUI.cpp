#include "PCH.hpp"
#include "GrimUI.hpp"

namespace grim
{

namespace ui
{

GrimUI::GrimUI()
{
}

GrimUI::~GrimUI()
{
    for (auto it = m_widgets.begin(); it != m_widgets.end(); it++)
    {
        if (*it != nullptr)
        {
            delete (*it);
        }
    }

    m_widgets.clear();
}

void GrimUI::Update(float deltaTime)
{
    for (auto it = m_widgets.begin(); it != m_widgets.end(); it++)
    {
        (*it)->Update(deltaTime);
    }
}

void GrimUI::Render()
{
    for (auto it = m_widgets.begin(); it != m_widgets.end(); it++)
    {
        (*it)->Render();
    }
}

void GrimUI::RegisterWidget(grim::ui::Widget* widget)
{
    m_widgets.push_back(widget);
}

}

}