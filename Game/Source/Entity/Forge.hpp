#pragma once
#include "Entity.hpp"

class Forge : public Entity
{
public:
    Forge(Game* game, const glm::vec3& position);
    virtual ~Forge();

    virtual void Update(float deltaTime);
    virtual void Render();
};
