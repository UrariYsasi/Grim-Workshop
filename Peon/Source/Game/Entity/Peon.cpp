#include "../../PCH.hpp"
#include "Peon.hpp"
#include "../Game.hpp"

Peon::Peon(Game* game, Vector2D position) :
    Monster(game, position)
{
}

Peon::~Peon()
{
}

void Peon::Update()
{
    Monster::Update();
}

void Peon::Render()
{
    m_game->RenderSprite("peon", 0, 0, m_position.GetX(), m_position.GetY(), 32, 32);

    // Debug stuff
    std::stringstream ss;
    if (m_actionStack.size() != 0)
    {

        ss << m_actionStack.back()->GetName();
        m_game->RenderText("dos", m_position.GetX() + 32, m_position.GetY(), ss.str());
        ss.str(" ");

        ss << m_actionStack.size();
        m_game->RenderText("dos", m_position.GetX() + 32, m_position.GetY() + 16, ss.str());
        ss.str(" ");
    }
}
