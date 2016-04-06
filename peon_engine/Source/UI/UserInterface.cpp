#include "PCH.hpp"
#include "UserInterface.hpp"
#include "Widgets\Widget.hpp"

namespace grim
{

namespace ui
{

UserInterface::UserInterface()
{
}

UserInterface::~UserInterface()
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

void UserInterface::Update(float deltaTime)
{
    for (auto it = m_widgets.begin(); it != m_widgets.end(); it++)
    {
        (*it)->Update(deltaTime);
    }
}

void UserInterface::Render()
{
    for (auto it = m_widgets.begin(); it != m_widgets.end(); it++)
    {
        (*it)->Render();
    }
}

void UserInterface::RegisterWidget(grim::ui::Widget* widget)
{
    m_widgets.push_back(widget);
}

}

}