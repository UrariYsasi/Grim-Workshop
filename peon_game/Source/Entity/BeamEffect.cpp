#include "PCH.hpp"
#include "BeamEffect.hpp"
#include "../Game.hpp"

BeamEffect::BeamEffect(Game* game, const glm::vec3& position) :
    Entity(game, position, EntityID::EFFECT_BEAM),
    m_lifetimeSeconds(0.3f)
{
    m_transform.scale = glm::vec3(0.5f, 0.5f, 1.0f);
    grim::graphics::Texture* texture = m_game->GetTexture("beam");
    grim::graphics::ShaderProgram* shaderProgram = m_game->GetShaderProgram("basic_shader");
    m_sprite = std::make_unique<grim::graphics::Sprite>(texture, shaderProgram, 64, 128, 0);
    m_sprite->geometryHeight = m_sprite->height * 20;
    m_origin.y = (m_sprite->geometryHeight * m_transform.scale.y) / 2.0f;
    m_sprite->color.a = 0.75f;

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

void BeamEffect::Render(grim::graphics::SpriteBatch& spriteBatch)
{
    spriteBatch.AddSprite(m_transform.position - m_origin + m_positionOffset, m_transform.rotation, m_transform.scale, m_sprite.get());

    Entity::Render(spriteBatch);
}