#include "PCH.hpp"
#include "Obelisk.hpp"
#include "../Game.hpp"
#include "../../Engine/Renderer.hpp"

Obelisk::Obelisk(Game* game, const glm::vec2& position) :
    Prop(game, position, OBELISK)
{
    m_origin = glm::vec2(0, 96);
    m_hitBox = Rect(-36, -30, 73, 80);
    grim::Texture* texture = game->GetTexture("obelisk");
    grim::ShaderProgram* shaderProgram = game->GetShaderProgram("basic_shader");
    m_sprite = std::make_unique<grim::Sprite>(texture, shaderProgram, 96, 288, 0);
}

Obelisk::~Obelisk()
{
}

void Obelisk::Update(double deltaTime)
{
    if (IsDead())
    {
        Debug::Log("Obelisk is dead. Game over.");
    }
}

void Obelisk::Render()
{
    m_sprite->Render(glm::vec3(m_position - m_origin + m_positionOffset, 0.0f), glm::vec3(0), glm::vec3(96, 288, 0));

    Entity::Render();
}
