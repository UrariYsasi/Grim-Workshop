#include "PCH.hpp"
#include "BeamEffect.hpp"
#include "../Game.hpp"

BeamEffect::BeamEffect(Game* game, const glm::vec2& position) :
    Entity(game, position, ENT_BEAM_EFFECT)
{
    m_scale = glm::vec3(0.5f, 0.5f, 1.0f);
    grim::graphics::Texture* texture = m_game->GetTexture("beam");
    grim::graphics::ShaderProgram* shaderProgram = m_game->GetShaderProgram("basic_shader");
    m_sprite = std::make_unique<grim::graphics::Sprite>(texture, shaderProgram, 64, 128, 0);
    m_sprite->geometryHeight = m_sprite->height * 20;
    m_origin = glm::vec2(0.0f, m_sprite->geometryHeight * m_scale.y / 2.0f);
}

BeamEffect::~BeamEffect()
{
}

void BeamEffect::Update(float deltaTime)
{
}

void BeamEffect::Render(grim::graphics::SpriteBatch& spriteBatch)
{
    spriteBatch.AddSprite(glm::vec3(m_position - m_origin + m_positionOffset, 0.0f), glm::vec3(0.0f), m_scale, m_sprite.get());

    Entity::Render(spriteBatch);
}