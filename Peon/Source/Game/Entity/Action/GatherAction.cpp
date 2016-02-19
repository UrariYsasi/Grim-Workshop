#include "PCH.hpp"
#include "GatherAction.hpp"
#include "../../Game.hpp"
#include "MoveAction.hpp"
#include "DepositAction.hpp"
#include "../Monster.hpp"
#include "../Resource.hpp"
#include "../../Item/Inventory.hpp"
#include "../../Map/Map.hpp"

GatherAction::GatherAction(Monster* owner, Resource* target) :
    Action(owner, "Gather"),
    m_target(target),
    m_gatherTime(3),
    m_ownerInventory(nullptr)
{
    m_ownerInventory = m_owner->GetInventory();

    if (m_target->IsFull())
    {
        FindNode();
    }
    else
    {
        // Add this peon to the target resource peon count
        m_target->AddPeon();
    }
}

GatherAction::~GatherAction()
{
}

void GatherAction::Update(double deltaTime)
{
    if (m_target == nullptr)
    {
        // The target is null, which isn't supposed to happen. Just complete the action.
        Complete();
        return;
    }

    if (m_target->IsDead())
    {
        // The target resource node is already dead. Find a new node.
        FindNode();
        return;
    }

    ItemType item = m_target->GetItem();

    // Check if we are in range of the resource
    Vector2D targetCenter = m_target->GetPositionCenter();
    Vector2D monsterCenter = m_owner->GetPositionCenter();
    double distance = Vector2D::Distance(monsterCenter, targetCenter);

    if (distance <= MIN_GATHER_DISTANCE)
    {
        // We are close enough. We can start gathering.
        if (!m_timer.IsStarted())
        {
            m_gatherTime = Random::Generate(5000, 10000);
            m_timer.Start();
        }
        else
        {
            if (m_timer.GetTime() > m_gatherTime)
            {
                m_target->Damage();
                m_timer.Stop();

                m_owner->GetGame()->PlaySound("woodcutting_00"); // TODO different sounds
                m_ownerInventory->GiveItem(item, (int)Random::Generate(1, 3));
                m_owner->PushAction(std::make_unique<DepositAction>(m_owner, item, -1));
            }
        }
    }
    else
    {
        // We aren't close enough. Move to the resource.
        m_owner->PushAction(std::make_unique<MoveAction>(m_owner, m_target->GetPosition()));
    }
}

void GatherAction::Complete()
{
    if (m_target != nullptr)
    {
        m_target->RemovePeon();
    }

    Action::Complete();
}

void GatherAction::FindNode()
{
    // TODO make this not bad
    int entityID = m_target->GetEntityID();
    Vector2D point = m_target->GetPosition();
    std::list<Entity*> ents = m_owner->GetGame()->GetMap()->FindEntitiesInRange(entityID, point, 100);

    ents.sort([point](Entity* a, Entity* b)
    {
        double distanceA = Vector2D::Distance(a->GetPosition(), point);
        double distanceB = Vector2D::Distance(b->GetPosition(), point);

        return distanceA < distanceB;
    });

    for (auto it = ents.begin(); it != ents.end(); it++)
    {
        Resource* resource = dynamic_cast<Resource*>((*it));
        if (resource != nullptr)
        {
            if (!resource->IsDead() && !resource->IsFull())
            {
                m_target = resource;
                return;
            }
        }
    }


    Complete();
}