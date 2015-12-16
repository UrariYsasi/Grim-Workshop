#include "PCH.hpp"
#include "Peon.hpp"
#include "Game.hpp"

Peon::Peon(Game* game, const Vector2D& position) :
    Entity(game, position),
    m_state(IDLE),
    dest(0, 0),
    m_bonfire(nullptr),
    m_targetResource(nullptr),
    m_resources(0)
{
    m_bonfire = m_game->FindBonfire(this);

    speedVariation = rand() % 20 - 10;

    // Set up state machine
    m_stateHandler[IDLE] = &Peon::IdleState;
    m_stateHandler[WALKING] = &Peon::WalkingState;
    m_stateHandler[GATHERING] = &Peon::GatheringState;
    m_stateHandler[SACRIFICE] = &Peon::SacrificeState;
}

void Peon::Respawn()
{
    m_resources = 0;
    m_targetResource = nullptr;
    m_position = Vector2D(rand() % 600, -50);
    dest = Vector2D(256, 200);
    m_state = WALKING;
}

void Peon::Update()
{
    m_hitbox.x = m_position.GetX();
    m_hitbox.y = m_position.GetY();
    m_hitbox.w = 32;
    m_hitbox.h = 32;

    if (m_state == WALKING || m_state == SACRIFICE)
    {
        hopIndex += m_game->m_deltaTime;
        hopOffset = -(hopAmp * abs(sin(hopFreq * hopIndex)));
    }

    stateFunction stateFunc = m_stateHandler[m_state];
    if (stateFunc != nullptr)
    {
       (this->*stateFunc)();
    }
}

void Peon::Render()
{
    m_game->RenderSprite("peon", 0, 0, m_position.GetX(), m_position.GetY() + hopOffset, 32, 32);
    
    if (m_resources >= 5)
    {
        Tree* t = dynamic_cast<Tree*>(m_targetResource);
        if (t != nullptr)
        {
            // We are holding logs
            m_game->RenderSprite("peon", 1, 2, m_position.GetX(), m_position.GetY(), 32, 32);
        }
        else
        {
            // We are holding stone
            m_game->RenderSprite("peon", 0, 2, m_position.GetX(), m_position.GetY(), 32, 32);
        }
    }
}

void Peon::MoveTo(Vector2D dest)
{
    if (m_position != dest)
    {
        Vector2D start = m_position;
        double distance = Vector2D::Distance(start, dest);
        Vector2D direction = Vector2D::Normalize(dest - start);

        double speed = runSpeed;
        hopFreq = 15;
        if (m_isWandering)
        {
            hopFreq = 8;
            speed = walkSpeed;
        }
        speed += speedVariation;

        m_position += direction * (speed * m_game->m_deltaTime);
        if (Vector2D::Distance(start, m_position) > distance)
        {
            m_position = dest;
        }
    }
}

void Peon::IdleState()
{
    if (!m_idleTimer.IsStarted())
    {
        waitTime = rand() % 10000 + 1000;
        m_idleTimer.Start();
    }

    if (m_idleTimer.GetTime() > waitTime)
    {
        m_idleTimer.Stop();
        m_state = WALKING;

        double randX = rand() % 64 - 32;
        double randY = rand() % 64 - 32;
        dest = m_position + Vector2D(randX, randY);
        m_isWandering = true;
    }

    if (m_targetResource != nullptr)
    {
        dest = m_targetResource->GetPosition();
        m_state = WALKING;
    }
}

void Peon::WalkingState()
{
    // If we are gathering, interrupt it
    if (m_gatherTimer.IsStarted())
    {
        m_gatherTimer.Stop();
    }

    if (m_targetResource != nullptr)
    {
        m_isWandering = false;
    }

    // Walk to our destination.
    MoveTo(dest);

    // If we have reached our destination, begin the next action
    if (m_position == dest)
    {
        m_state = IDLE;

        if (m_targetResource != nullptr)
        {
            if (Vector2D::Distance(m_targetResource->GetPosition(), m_position) < 10)
            {
                m_state = GATHERING;
            }
        }

        if (m_bonfire != nullptr)
        {
            if (Vector2D::Distance(m_bonfire->GetPosition(), m_position) < 10)
            {
                if (m_resources > 0)
                {
                    m_game->DepositResources(m_resources);
                    m_resources = 0;
                    m_game->PlaySound("drop_00");
                    m_state = IDLE;
                }
            }
        }
    }
}

void Peon::GatheringState()
{
    if (!m_gatherTimer.IsStarted())
    {
        m_gatherTimer.Start();
        soundDelay = rand() % 1000 + 700;
    }

    if (m_gatherTimer.GetTime() > soundDelay)
    {
        m_gatherTimer.Stop();
        m_resources += 1;
        m_game->PlaySound("woodcutting_00");

        /*
        if (m_targetResource->m_ID == "tree")
        {
            m_lastResource = "tree";
            m_game->PlaySound("chop");
            m_resources += 1;
        }
        else if (m_targetResource->m_ID == "stone")
        {
            m_lastResource = "stone";
            m_game->PlaySound("mine");
            m_resources += 2;
        }
        */
    }

    if (m_resources >= 5)
    {
        if (m_bonfire != nullptr)
        {
            dest = m_bonfire->GetPosition();
            m_state = WALKING;
        }
    }
}

void Peon::SacrificeState()
{
    m_targetResource = nullptr;
    if (m_bonfire != nullptr)
    {
        dest = m_bonfire->GetPosition();

        MoveTo(dest);

        if (Vector2D::Distance(m_bonfire->GetPosition(), m_position) < 10)
        {
            m_game->SacrificePeon(this);
        }
    }
}
