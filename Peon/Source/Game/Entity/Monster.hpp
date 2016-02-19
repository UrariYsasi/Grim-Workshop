#pragma once
#include "Entity.hpp"
#include "../Item/Inventory.hpp"

class Action;

class Monster : public Entity
{
public:
    Monster(Game* game, Vector2D position, int entityID);
    virtual ~Monster();

    Inventory* GetInventory();
    int GetMoveSpeed();

    virtual void Update(double deltaTime);
    virtual void Render() = 0;

    /*
        Push an Action onto the Monster's action stack.

        This makes the Monster begin to perform the new action, as whichever
        Action is on the top of the action stack is used as the currently 
        active Action.
    */
    void PushAction(std::unique_ptr<Action> action);

    /*
        Clear the Monster's action stack.

        This is used when explicitly commanding monsters. It will complete all
        the Actions on the stack so that any new Actions can begin immediatly.
        This function is separate from CleanActionStack().
    */
    void ClearActionStack();

private:

    /*
        Clean the Monster's action stack by removing any completed Actions.

        This is called at the beginning of Update, to ensure that any Actions
        that were completed during the last frame are properly deleted.
    */
    void CleanActionStack();

protected:
    std::list< std::unique_ptr<Action> > m_actionStack;
    Inventory m_inventory;
    int m_moveSpeed;
};
