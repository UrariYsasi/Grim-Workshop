#pragma once
#include "Entity.hpp"
#include "../Item/Inventory.hpp"

class Action;

class Monster : public Entity
{
public:
    Monster(Game* game, Vector2D position);
    virtual ~Monster();

    Inventory* GetInventory();
    int GetMoveSpeed();

    virtual void Update(double deltaTime);
    virtual void Render() = 0;

    void PushAction(std::unique_ptr<Action> action);
    void ClearActions();

protected:
    std::list< std::unique_ptr<Action> > m_actionStack;
    Inventory m_inventory;
    int m_moveSpeed;
};
