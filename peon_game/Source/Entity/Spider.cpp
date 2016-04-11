#include "PCH.hpp"
#include "Spider.hpp"
#include "../Game.hpp"
#include "Action/IdleAction.hpp"
#include "Peon.hpp"
#include "../World/World.hpp"

Spider::Spider(Game* game, const glm::vec2& position) :
    Monster(game, position, ENT_MONSTER_SPIDER)
{
    m_scale = glm::vec3(256.0, 256.0, 1.0f);
    m_origin = glm::vec2(0, 0);
    m_hitBox = grim::graphics::Rect(-128, -128, 256, 256);
    m_hp = 6;

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

    if (IsDead())
    {
        grim::utility::Debug::Log("spider is dead!");
    }
}

void Spider::Render(grim::graphics::SpriteBatch& spriteBatch)
{
    float scaleX = (m_direction == Direction::LEFT) ? m_scale.x : -m_scale.x;
    spriteBatch.AddSprite(glm::vec3(m_position - m_origin, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(scaleX, m_scale.y, m_scale.z), m_sprite.get());

    Entity::Render(spriteBatch);
}

