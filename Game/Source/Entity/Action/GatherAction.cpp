#include "PCH.hpp"
#include "GatherAction.hpp"
#include "../../Game.hpp"
#include "MoveAction.hpp"
#include "DepositAction.hpp"
#include "PickUpAction.hpp"
#include "../Monster.hpp"
#include "../Resource.hpp"
#include "../../Item/Inventory.hpp"
#include "../../World/World.hpp"

GatherAction::GatherAction(Monster* owner, Resource* target) :
    Action(owner, GATHER_ACTION, "Gather"),
    m_ownerInventory(nullptr),
    m_target(target),
    m_gatherTime(3),
    m_totalGathers(0)
{
    m_ownerInventory = m_owner->GetInventory();

    // If the target resource is full or dead, abort.
    if (m_target->IsFull() || m_target->IsDead())
    {
        Abort();
        return;
    }

    // We are clear to begin the GatherAction. Add this peon to the target resource.
    m_target->AddPeon();
}

GatherAction::~GatherAction()
{
}

void GatherAction::Update(float deltaTime)
{
    if (m_target->IsDead())
    {
        Complete();
        return;
    }

    ItemType item = m_target->GetItem();

    // Check if we are in range of the resource
    glm::vec3 targetCenter = m_target->GetTransform().position;
    glm::vec3 monsterCenter = m_owner->GetTransform().position;
    double distance = glm::distance(monsterCenter, targetCenter);

    if (distance <= MIN_GATHER_DISTANCE)
    {
        // We are close enough. We can start gathering.
        if (!m_timer.IsStarted())
        {
            m_gatherTime = grim::utility::Random::Generate(1000, 4000);
            m_timer.Start();
        }
        else
        {
            if (m_timer.GetTimeInMilliseconds() > m_gatherTime)
            {
                m_timer.Stop();

                m_owner->GetGame()->GetEngine()->GetAudio()->PlaySound("woodcutting_00"); // TODO different sounds
                m_totalGathers++;
            }
        }

        if (m_totalGathers >= 3)
        {
            m_totalGathers = 0;
            m_target->Damage();
            m_ownerInventory->GiveItem(item, static_cast<uint16_t>(grim::utility::Random::Generate(1.0, 3.0)));
            Entity* itemDrop = m_owner->GetGame()->GetWorld()->Spawn(EntityID::ITEM_DROP, m_owner->GetTransform().position);
            m_owner->SetHeldEntity(itemDrop);
            m_owner->PushAction(std::make_unique<DepositAction>(m_owner));
        }
    }
    else
    {
        // We aren't close enough. Move to the resource.
        m_owner->PushAction(std::make_unique<MoveAction>(m_owner, m_target->GetTransform().position));
    }
}

void GatherAction::Complete()
{
    m_target->RemovePeon();

    Action::Complete();
}

void GatherAction::Abort()
{
    Action::Complete();
}