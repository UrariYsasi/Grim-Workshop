#include "PCH.hpp"
#include "Forge.hpp"
#include "../Game.hpp"

Forge::Forge(Game* game, const glm::vec2& position) :
    Prop(game, position, NONE)
{
}

Forge::~Forge()
{
}

void Forge::Update(double deltaTime)
{
}

void Forge::Render(grim::graphics::SpriteBatch& spriteBatch)
{
    Entity::Render(spriteBatch);
}