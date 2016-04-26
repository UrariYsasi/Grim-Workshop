#pragma once
#include "Entity.hpp"

class Obelisk : public Entity
{
public:
    Obelisk(Game* game, const glm::vec3& position);
    virtual ~Obelisk();

    virtual void Update(float deltaTime);
    virtual void Render();

    void ConsumeEntity(Entity* ent);
};
