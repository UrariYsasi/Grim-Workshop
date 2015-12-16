#pragma once
#include "PCH.hpp"
#include "Entity.hpp"
#include "Timer.hpp"
#include "Tree.hpp"
#include "Bonfire.hpp"

class Peon : public Entity
{
public:
    Peon(Game* game, const Vector2D& position);

    virtual void Update();
    virtual void Render();

    void MoveTo(Vector2D dest);
    void Respawn();

    void IdleState();
    void WalkingState();
    void GatheringState();
    void SacrificeState();

public:
    Vector2D dest;

    bool m_isWandering = false;
    double walkSpeed = 32;
    double runSpeed = 64;
    double speedVariation = 0;

    enum State { IDLE, WALKING, GATHERING, SACRIFICE };
    State m_state;

    Bonfire* m_bonfire;
    Entity* m_targetResource;
    std::string m_lastResource;

    int soundDelay;
    Timer m_gatherTimer;
    int waitTime;
    Timer m_idleTimer;
    int m_resources;

    double hopOffset;
    double hopIndex;
    double hopAmp = 6;
    double hopFreq;

private:
    typedef void (Peon::*stateFunction)();
    stateFunction m_stateHandler[5];
};