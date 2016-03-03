#include "PCH.hpp"
#include "Prop.hpp"

Prop::Prop(Game* game, const glm::vec2& position, int entityID) :
    Entity(game, position, entityID)
{
}

Prop::~Prop()
{
}
