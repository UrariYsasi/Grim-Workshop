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

void Peon::Update()
{
    Monster::Update();

    // TODO
    // This needs a refactor. See comment in Peon.hpp
    Action* action = m_actionStack.back().get();
    MoveAction* moveAction = dynamic_cast<MoveAction*>(action);
    if (moveAction != nullptr)
    {
        m_hopAmplitude = 2;
        m_hopFrequency = 30;
        m_hopIndex += m_game->m_deltaTime;
        m_hopOffset = -(m_hopAmplitude * sin(m_hopFrequency * m_hopIndex));
    }
}

void Peon::Render()
{
    m_game->RenderSprite("peon", 0, 0, m_position.GetX(), m_position.GetY() + m_hopOffset, 32, 32);

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
