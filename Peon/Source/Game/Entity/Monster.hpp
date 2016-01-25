#pragma once
#include "../../PCH.hpp"
#include "Entity.hpp"
#include "Action/Action.hpp"
#include "Action/IdleAction.hpp"

class Monster : public Entity
{
public:
    enum State { NONE, IDLE, WALKING, WORKING, ENUM_SIZE };

    Monster(Game* game, Vector2D position);
    virtual ~Monster();

    Vector2D GetDestination() const;
    void SetDestination(const Vector2D& destination);

    virtual void Update();
    virtual void Render() = 0;
    void StartNavigation(const Vector2D& destination);
    void PushAction(std::unique_ptr<Action> action);

    // State machine functions
    void WalkingState();

protected:
    // State machine variables
    State m_state; // The monsters current state
    typedef void (Monster::*stateFunction)();
    stateFunction m_stateHandler[State::ENUM_SIZE];
    std::stack< std::unique_ptr<Action> > m_actionStack;

    Vector2D m_destination; // The destination, used for walking
    double m_moveSpeed; // The movement speed of the monster
};
