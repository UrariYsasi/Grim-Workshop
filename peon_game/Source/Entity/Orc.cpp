#include "PCH.hpp"
#include "Orc.hpp"
#include "../Game.hpp"
#include "Action/MoveAction.hpp"
#include "Action/AttackAction.hpp"
#include "Peon.hpp"
#include "../World/World.hpp"

Orc::Orc(Game* game, const glm::vec3& position) :
    Monster(game, position, EntityID::MONSTER_ORC)
{
    m_origin.y = 16.0f;
    m_hitBox = grim::graphics::Rect(-3.0f, -16.0f, 7.0f, 16.0f);
    m_hp = 6;

    grim::graphics::Texture* texture = game->GetTexture("orc");
    grim::graphics::ShaderProgram* shaderProgram = game->GetShaderProgram("basic_shader"); 
    m_sprite = std::make_unique<grim::graphics::Sprite>(texture, shaderProgram, 32, 32, 0);
}

Orc::~Orc()
{
}

void Orc::Update(float deltaTime)
{
    Monster::Update(deltaTime);
}

void Orc::Render(grim::graphics::SpriteBatch& spriteBatch)
{
    spriteBatch.AddSprite(m_transform.position - m_origin + m_positionOffset, m_transform.rotation, m_transform.scale, m_sprite.get());
}

