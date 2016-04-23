#include "PCH.hpp"
#include "Forge.hpp"
#include "../Game.hpp"

Forge::Forge(Game* game, const glm::vec2& position) :
    Entity(game, position, EntityID::NONE)
{
}

Forge::~Forge()
{
}

void Forge::Update(float deltaTime)
{
}

void Forge::Render(grim::graphics::SpriteBatch& spriteBatch)
{
    Entity::Render(spriteBatch);
}