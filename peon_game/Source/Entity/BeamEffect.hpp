#pragma once
#include "Entity.hpp"

class BeamEffect : public Entity
{
public:
    BeamEffect(Game* game, const glm::vec3& position);
    virtual ~BeamEffect();

    virtual void Update(float deltaTime);
    virtual void Render();

private:
    float m_lifetimeSeconds;
    grim::utility::Timer m_timer;
};
