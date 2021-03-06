#pragma once
#include "Action.hpp"

class Entity;

class MoveAction : public Action
{
public:
    MoveAction(Monster* owner, const glm::vec3& destination);
    virtual ~MoveAction();

    glm::vec3 GetDestination() const;

    virtual void Update(float deltaTime);

    /*
        Sets a target entity to follow.

        If this MoveAction has a follow target, it will continue to follow
        that target until it reaches it.
    */
    void SetFollowTarget(Entity* target);

    /*
        Set the minimum range for the MoveAction.

        This is so that the owner of the Action will move within a certain
        range of the target, instead of right on top of it.
    */
    void SetMinimumRange(int range);

private:
    glm::vec3 m_destination;
    Entity* m_followTarget;
    int m_range;

    double m_hopOffset;
    double m_hopIndex;
    double m_hopAmp;
    double m_hopFreq;
};
