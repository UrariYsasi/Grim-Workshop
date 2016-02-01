#include "PCH.hpp"
#include "Peon.hpp"
#include "../Game.hpp"
#include "Action\MoveAction.hpp"

Peon::Peon(Game* game, Vector2D position) :
    Monster(game, position)
{
}

Peon::~Peon()
{
}

void Peon::Update(double deltaTime)
{
    Monster::Update(deltaTime);
}

void Peon::Render()
{
    m_game->RenderSprite("peon", 0, 0, (int)m_position.x, (int)m_position.y, 32, 32);

    // Debug stuff
    std::stringstream ss;
    if (m_actionStack.size() != 0)
    {
        ss << m_actionStack.back()->GetName();
        m_game->RenderText("dos", (int)m_position.x + 32, (int)m_position.y, ss.str());
        ss.str(" ");

        ss << m_actionStack.size();
        m_game->RenderText("dos", (int)m_position.x + 32, (int)m_position.y + 16, ss.str());
        ss.str(" ");
    }
}

