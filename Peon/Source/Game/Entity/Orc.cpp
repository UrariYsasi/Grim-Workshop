#include "PCH.hpp"
#include "Orc.hpp"
#include "../Game.hpp"
#include "Action/MoveAction.hpp"
#include "Action/AttackAction.hpp"
#include "Peon.hpp"
#include "../../Engine/Renderer.hpp"
#include "../Map/Map.hpp"

Orc::Orc(Game* game, Vector2D position) :
    Monster(game, position, ORC)
{
    m_origin = Vector2D(16, 16);
    m_hitBox = Rectangle(-4, 0, 8, 16);
    m_hp = 6;
}

Orc::~Orc()
{
}

void Orc::Update(double deltaTime)
{
    Monster::Update(deltaTime);

    Map* map = m_game->GetMap();

    // LOOK FOR ORC ATTACK ACTION
    AttackAction* attackAction = dynamic_cast<AttackAction*>(FindAction(ATTACK_ACTION));
    if (attackAction == nullptr)
    {
        // WE NEED ATTACK ACTION! ATTACK DE OBELISK!
        Entity* obeliskEnt = map->FindEntity(OBELISK);
        if (obeliskEnt != nullptr)
        {
            ClearActionStack();
            PushAction(std::make_unique<AttackAction>(this, obeliskEnt));
        }
    }
    else
    {
        // IF ATTACK ACTION IS NOT ALREADY ATTACKING PEON
        if (!attackAction->IsAttackingPeon())
        {
            // ORC SEARCH FOR PUNY PEONS TO SMASH
            Rectangle searchRect(m_position.x - 128, m_position.y - 128, 256, 256);
            std::list<Entity*> peons = map->GetEntitiesInRectangle(PEON, searchRect);
            if (peons.size() > 0)
            {
                // ORC SEE PEONS. SMASH DEM!
                ClearActionStack();
                Entity* peonEnt = peons.back();
                PushAction(std::make_unique<AttackAction>(this, peonEnt));
            }
        }
    }
}

void Orc::Render()
{
    Renderer* renderer = m_game->GetRenderer();

    if (!IsDead())
    {
        renderer->RenderSprite("orc", 0, 0, (int)(m_position.x + m_positionOffset.x - m_origin.x), (int)(m_position.y + m_positionOffset.y - m_origin.y), 32, 32);
    }
    else
    {
        renderer->RenderSprite("orc", 1, 0, (int)(m_position.x + m_positionOffset.x - m_origin.x), (int)(m_position.y + m_positionOffset.y - m_origin.y), 32, 32);
    }

    // ORC LIKE TO DEBUG
    /*
    if (m_actionStack.size() > 0)
    {
        renderer->RenderText("dos", (int)(m_position.x), (int)(m_position.y), m_actionStack.back()->GetName());
    }
    */
    //Rectangle searchRect(m_position.x - 128, m_position.y - 128, 256, 256);
    //renderer->RenderOutlineRect(searchRect);

    Entity::Render();
}

