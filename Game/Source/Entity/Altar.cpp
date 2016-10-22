#include "PCH.hpp"
#include "Altar.hpp"
#include "../Game.hpp"

Altar::Altar(Game* game, const glm::vec3& position) :
    Entity(game, position, EntityID::STRUCTURE_ALTAR)
{
    m_origin.y = 16.0f;
    m_hitBox = grim::graphics::Rect(-16, -16, 32, 32);
}

Altar::~Altar()
{
}

void Altar::Update(float deltaTime)
{
}

void Altar::Render()
{
    Entity::Render();
}
