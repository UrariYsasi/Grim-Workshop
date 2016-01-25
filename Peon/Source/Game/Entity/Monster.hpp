#pragma once
#include "../../PCH.hpp"
#include "Entity.hpp"
#include "Action/Action.hpp"
#include "Action/IdleAction.hpp"

class Monster : public Entity
{
public:
    Monster(Game* game, Vector2D position);
    virtual ~Monster();

    virtual void Update();
    virtual void Render() = 0;
    void PushAction(std::unique_ptr<Action> action);

protected:
    std::stack< std::unique_ptr<Action> > m_actionStack;
};
