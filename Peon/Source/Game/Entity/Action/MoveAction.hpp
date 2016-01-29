#pragma once
#include "Action.hpp"

class MoveAction : public Action
{
public:
    MoveAction(Monster* owner, const Vector2D& destination);
    virtual ~MoveAction();

    Vector2D GetDestination() const;
    void SetDestination(const Vector2D& destination);

    virtual void Update();

private:
    Vector2D m_destination;
};
