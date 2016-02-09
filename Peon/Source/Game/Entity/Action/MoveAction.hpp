#pragma once
#include "Action.hpp"

class MoveAction : public Action
{
public:
    MoveAction(Monster* owner, const Vector2D& destination);
    virtual ~MoveAction();

    Vector2D GetDestination() const;

    virtual void Update(double deltaTime);

private:
    const int MOVE_SPEED = 64;

    Vector2D m_destination;

    double m_hopOffset;
    double m_hopIndex;
    double m_hopAmp;
    double m_hopFreq;
};
