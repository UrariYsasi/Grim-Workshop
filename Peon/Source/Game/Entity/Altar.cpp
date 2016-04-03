#include "PCH.hpp"
#include "Altar.hpp"
#include "../Game.hpp"

Altar::Altar(Game* game, const glm::vec2& position) :
    Prop(game, position, ALTAR)
{
    m_origin = glm::vec2(16, 16);
    m_hitBox = grim::graphics::Rect(-16, -16, 32, 32);
}

Altar::~Altar()
{
}

void Altar::Update(float deltaTime)
{
}

void Altar::Render(grim::graphics::SpriteBatch& spriteBatch)
{
    Entity::Render(spriteBatch);
}
