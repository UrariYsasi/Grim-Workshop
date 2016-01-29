#pragma once
// Tyren Review: Never include PCH in headers
#include "../../PCH.hpp"

#include "Entity.hpp"

// Tyren Review: Try to find a way to forward declare this?
#include "Action/Action.hpp"

// Tyren Review: ??? Why is this included
#include "Action/IdleAction.hpp"

// Tyren Review: Try to find a way to forward declare this?
#include "../Item/Inventory.hpp"

class Monster : public Entity
{
public:
    Monster(Game* game, Vector2D position);
    virtual ~Monster();

    Inventory* GetInventory();

    virtual void Update();
    virtual void Render() = 0;
    void PushAction(std::unique_ptr<Action> action);
    void ClearActions();

protected:
    std::list< std::unique_ptr<Action> > m_actionStack;
    std::unique_ptr<Inventory> m_inventory;
};
