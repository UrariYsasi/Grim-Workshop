#include "PCH.hpp"
#include "Prop.hpp"

Prop::Prop(Game* game, Vector2D position, int entityID) :
    Entity(game, position, entityID)
{
}

Prop::~Prop()
{
}
