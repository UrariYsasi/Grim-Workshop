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
}

bool GrimUI::Initialize()
{
    // Initialize SDL_ttf
    if (TTF_Init() != SUCCESS)
    {
        grim::utility::Debug::Log("SDL_ttf could not initialize! SDL_ttf error: %s", TTF_GetError());
        return false;
    }

    grim::utility::Debug::LogError("UI module GrimUI initialized.");
    return true;
}

void GrimUI::Terminate()
{
    for (Widget* widget : m_widgets)
    {
        if (widget != nullptr)
        {
            delete (widget);
        }
    }

    m_widgets.clear();

    TTF_Quit();

    grim::utility::Debug::LogError("UI module GrimUI terminated.");
}

void GrimUI::Update(float deltaTime)
{
    bool isMouseClicked = m_engine->GetInput()->GetMouseButtonPress(SDL_BUTTON_LEFT);
    glm::vec2 mousePosition = m_engine->GetInput()->GetMousePosition();

    for (auto it = m_widgets.rbegin(); it != m_widgets.rend(); it++)
    {
        Widget* widget = (*it);

        if (widget->IsVisible())
        {
            grim::graphics::Rect bounds = widget->GetBounds();
            if (bounds.ContainsPoint(mousePosition))
            {
                if (isMouseClicked)
                {
                    widget->OnClick(mousePosition);
                    m_engine->GetInput()->InvalidateMouseButtonPress(SDL_BUTTON_LEFT);
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
        if ((*it)->IsVisible())
        {
            (*it)->Render();
        }
    }
}

void GrimUI::RegisterWidget(grim::ui::Widget* widget)
{
    m_widgets.push_back(widget);
}

}

}