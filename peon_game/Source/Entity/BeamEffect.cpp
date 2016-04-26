#include "PCH.hpp"
#include "BeamEffect.hpp"
#include "../Game.hpp"

BeamEffect::BeamEffect(Game* game, const glm::vec3& position) :
    Entity(game, position, EntityID::EFFECT_BEAM),
    m_lifetimeSeconds(0.3f)
{
    m_transform.scale = glm::vec3(0.5f, 0.5f, 1.0f);
    m_sprite = std::make_unique<grim::graphics::Sprite>(m_game->GetMaterial("effect_beam"));
    m_sprite->SetMeshHeight(m_sprite->GetHeight() * 20.0f);
    m_origin.y = (m_sprite->GetMeshHeight() * m_transform.scale.y) / 2.0f;

    m_game->GetAudio()->PlaySound("spell_summon_00");

    m_timer.Start();
}

BeamEffect::~BeamEffect()
{
}

void BeamEffect::Update(float deltaTime)
{
    m_transform.scale.x -= 0.02f;

    if (m_timer.GetTimeInSeconds() >= m_lifetimeSeconds)
    {
        Delete();
    }
}

void BeamEffect::Render()
{
    //spriteBatch.AddSprite(m_transform.position - m_origin + m_positionOffset, m_transform.rotation, m_transform.scale, m_sprite.get());

    Entity::Render();
}