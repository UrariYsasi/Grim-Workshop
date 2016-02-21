#include "PCH.hpp"
#include "Orc.hpp"
#include "../Game.hpp"
#include "Action/MoveAction.hpp"
#include "Action/AttackAction.hpp"
#include "Peon.hpp"
#include "../../Engine/Renderer.hpp"
#include "../Map/Map.hpp"

Orc::Orc(Game* game, Vector2D position) :
    Monster(game, position, GOBLIN)
{
    m_origin = Vector2D(16, 16);
    m_hitBox = Rectangle(-4, 0, 8, 16);
}

Orc::~Orc()
{
}

void Orc::Update(double deltaTime)
{
    Map* map = m_game->GetMap();

    // LOOK FOR ORC ATTACK ACTION
    AttackAction* attackAction = dynamic_cast<AttackAction*>(FindAction(ATTACK_ACTION));
    if (attackAction != nullptr)
    {
        // IF ATTACK ACTION IS NOT ALREADY ATTACKING PEON
        if (!attackAction->IsAttackingPeon())
        {
            // ORC SEARCH FOR PUNY PEONS TO SMASH
            Rectangle searchRect(m_position.x - 128, m_position.y - 128, 256, 256);
            std::list<Peon*> peons = map->GetPeonsInRectangle(searchRect);
            if (peons.size() > 0)
            {
                // ORC SEE PEONS. SMASH DEM!
                ClearActionStack();
                Entity* peonEnt = dynamic_cast<Entity*>(peons.back());
                PushAction(std::make_unique<AttackAction>(this, peonEnt));
            }
        }
    }

    // ORC NOT IDLE. ORC ONLY SMASH.
    if (m_actionStack.size() == 0)
    {
        Entity* obeliskEnt = map->FindEntity(OBELISK);
        PushAction(std::make_unique<AttackAction>(this, obeliskEnt));
    }

    Monster::Update(deltaTime);
}

void Orc::Render()
{
    Renderer* renderer = m_game->GetRenderer();
    renderer->RenderSprite("orc", 0, 0, (int)(m_position.x + m_positionOffset.x - m_origin.x), (int)(m_position.y + m_positionOffset.y - m_origin.y), 32, 32);

    // ORC LIKE TO DEBUG
    if (m_actionStack.size() > 0)
    {
        renderer->RenderText("dos", (int)(m_position.x), (int)(m_position.y), m_actionStack.back()->GetName());
    }
    //Rectangle searchRect(m_position.x - 128, m_position.y - 128, 256, 256);
    //renderer->RenderOutlineRect(searchRect);

    Entity::Render();
}

