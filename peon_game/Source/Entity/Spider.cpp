#include "PCH.hpp"
#include "Spider.hpp"
#include "../Game.hpp"
#include "Action/IdleAction.hpp"
#include "Peon.hpp"
#include "../World/World.hpp"

Spider::Spider(Game* game, const glm::vec3& position) :
    Monster(game, position, EntityID::MONSTER_SPIDER_QUEEN)
{
    m_transform.scale = glm::vec3(0.5f, 0.5f, 1.0f);
    m_origin.y = 128.0f;
    m_hitBox = grim::graphics::Rect(-128, -128, 256, 128);
    m_hp = 6;
    m_faithWorth = 100;

    m_sprite = grim::graphics::Sprite(m_game->GetMaterial("sprite_spider_queen"));
}

Spider::~Spider()
{
}

void Spider::Update(float deltaTime)
{
    Monster::Update(deltaTime);
}

void Spider::Render()
{
    float scaleX = m_transform.scale.x;

    if (m_direction.x < 0)
    {
        scaleX = m_transform.scale.x;
    }
    else
    {
        scaleX = -m_transform.scale.x;
    }

    grim::graphics::Transform spiderTransform = m_transform;
    spiderTransform.position -= m_origin;
    spiderTransform.scale.x = scaleX;
    grim::graphics::RenderCommand spiderCommand(&m_sprite, spiderTransform);
    m_game->GetEngine()->GetRenderer()->Submit(spiderCommand);

    Entity::Render();
}
