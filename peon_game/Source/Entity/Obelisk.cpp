#include "PCH.hpp"
#include "Obelisk.hpp"
#include "../Game.hpp"

Obelisk::Obelisk(Game* game, const glm::vec3& position) :
    Entity(game, position, EntityID::STRUCTURE_OBELISK)
{
    m_hitBox = grim::graphics::Rect(-32, -32, 64, 64);
    m_sprite = grim::graphics::Sprite(m_game->GetMaterial("sprite_obelisk"));
    m_origin.y = 144;
}

Obelisk::~Obelisk()
{
}

void Obelisk::Update(float deltaTime)
{
    if (IsDead())
    {
        grim::utility::Debug::Log("Obelisk is dead. Game over.");
    }
}

void Obelisk::Render()
{
    grim::graphics::Transform obeliskTransform = m_transform;
    obeliskTransform.position -= m_origin;
    grim::graphics::RenderCommand obeliskCommand(&m_sprite, obeliskTransform);
    m_game->GetEngine()->GetRenderer()->Submit(obeliskCommand);

    Entity::Render();
}

void Obelisk::ConsumeEntity(Entity* ent)
{
    ent->Consume(this);
}