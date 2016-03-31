#include "PCH.hpp"
#include "Obelisk.hpp"
#include "../Game.hpp"

Obelisk::Obelisk(Game* game, const glm::vec2& position) :
    Prop(game, position, OBELISK)
{
    m_origin = glm::vec2(0, 96);
    m_hitBox = grim::graphics::Rect(-32, -32, 64, 64);
    grim::graphics::Texture* texture = game->GetTexture("obelisk");
    grim::graphics::ShaderProgram* shaderProgram = game->GetShaderProgram("basic_shader");
    m_sprite = std::make_unique<grim::graphics::Sprite>(texture, shaderProgram, 64, 288, 0);
}

Obelisk::~Obelisk()
{
}

void Obelisk::Update(double deltaTime)
{
    if (IsDead())
    {
        grim::utility::Debug::Log("Obelisk is dead. Game over.");
    }
}

void Obelisk::Render(grim::graphics::SpriteBatch& spriteBatch)
{
    spriteBatch.AddSprite(glm::vec3(m_position - m_origin + m_positionOffset, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(64.0, 288.0, 0), m_sprite.get());

    Entity::Render(spriteBatch);
}
