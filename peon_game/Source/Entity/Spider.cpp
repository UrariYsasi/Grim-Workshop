#include "PCH.hpp"
#include "Spider.hpp"
#include "../Game.hpp"
#include "Action/IdleAction.hpp"
#include "Peon.hpp"
#include "../World/World.hpp"

Spider::Spider(Game* game, const glm::vec2& position) :
    Monster(game, position, EntityID::MONSTER_SPIDER_QUEEN)
{
    m_origin = glm::vec2(0, 128);
    m_hitBox = grim::graphics::Rect(-128, 0, 256, 128);
    m_hp = 6;
    m_faithWorth = 100;

    grim::graphics::Texture* texture = game->GetTexture("spider");
    grim::graphics::ShaderProgram* shaderProgram = game->GetShaderProgram("basic_shader"); 
    m_sprite = std::make_unique<grim::graphics::Sprite>(texture, shaderProgram, 512, 512, 0);
}

Spider::~Spider()
{
}

void Spider::Update(float deltaTime)
{
    Monster::Update(deltaTime);
}

void Spider::Render(grim::graphics::SpriteBatch& spriteBatch)
{
    float scaleX = (m_direction == Direction::LEFT) ? m_scale.x : -m_scale.x;

    spriteBatch.AddSprite(glm::vec3(m_position.x - m_origin.x, m_position.y - m_origin.y, 0.0f), glm::vec3(0.0f), glm::vec3(scaleX / 2.0f, m_scale.y / 2.0f, m_scale.z), m_sprite.get());

    Entity::Render(spriteBatch);
}
