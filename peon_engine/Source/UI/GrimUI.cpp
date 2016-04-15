#include "PCH.hpp"
#include "GrimUI.hpp"

namespace grim
{

namespace ui
{

GrimUI::GrimUI(grim::Engine* engine) :
    m_engine(engine)
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
    bool isMouseClicked = m_engine->GetInput()->GetMouseButtonPress(SDL_BUTTON_LEFT);
    glm::vec2 mousePosition = m_engine->GetInput()->GetMousePosition();

    for (auto it = m_widgets.begin(); it != m_widgets.end(); it++)
    {
        Widget* widget = (*it);

        if (isMouseClicked)
        {
            if ((mousePosition.x > (widget->GetPosition().x - widget->GetWidth() / 2)) && (mousePosition.x < (widget->GetPosition().x + widget->GetWidth() / 2)))
            {
                if ((mousePosition.y > (widget->GetPosition().y - widget->GetHeight() / 2)) && (mousePosition.y < (widget->GetPosition().y + widget->GetHeight() / 2)))
                {
                    widget->OnClick();
                }
            }
        }

        widget->Update(deltaTime);
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