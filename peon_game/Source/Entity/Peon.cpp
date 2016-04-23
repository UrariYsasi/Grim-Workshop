#include "PCH.hpp"
#include "Peon.hpp"
#include "../Game.hpp"
#include "Action/MoveAction.hpp"
#include "Action/IdleAction.hpp"
#include "Action/AttackAction.hpp"
#include "Orc.hpp"
#include "../World/World.hpp"
#include "../World/Region.hpp"
#include "../Player.hpp"

Peon::Peon(Game* game, const glm::vec2& position) :
    Monster(game, position, EntityID::PEON),
    m_isSelected(false),
    m_selectionSprite(nullptr)
{
    m_game->GetPlayer()->AddPeon();

    m_origin = glm::vec2(0, 16);
    m_hitBox = grim::graphics::Rect(-3.0f, -16.0f, 7.0f, 16.0f);

    grim::graphics::Texture* texture = m_game->GetTexture("peon");
    grim::graphics::ShaderProgram* shaderProgram = game->GetShaderProgram("basic_shader");
    uint8_t col = static_cast<uint8_t>(std::round(grim::utility::Random::Generate(-0.4f, 4.4f)));
    m_sprite = std::make_unique<grim::graphics::Sprite>(texture, shaderProgram, 32, 32, col);
    m_selectionSprite = std::make_unique<grim::graphics::Sprite>(texture, shaderProgram, 32, 32, 57);
    m_shadowSprite = std::make_unique<grim::graphics::Sprite>(texture, shaderProgram, 32, 32, 58, grim::graphics::Color(1, 1, 1, .5));
}

Peon::~Peon()
{
}

void Peon::Update(float deltaTime)
{
    Monster::Update(deltaTime);

    World* world = m_game->GetWorld();

    // Check if we have moved into an unexplored Region
    glm::ivec2 coordinates = world->ConvertToRegionCoordinates(m_position);
    if (!world->IsRegionExplored(coordinates))
    {
        world->ExploreRegion(coordinates);
    }
}

void Peon::Render(grim::graphics::SpriteBatch& spriteBatch)
{
    if (m_isSelected)
    {
        spriteBatch.AddSprite(glm::vec3(m_position - m_origin + glm::vec2(0.0f, 3.0f), 0.0f), glm::vec3(0.0f), glm::vec3(1.0f), m_selectionSprite.get());
    }

    spriteBatch.AddSprite(glm::vec3(m_position - m_origin + glm::vec2(0.0f, 16.0f), 0.0f), glm::vec3(0.0f), glm::vec3(1.0f + (m_positionOffset.y / 2.75f), 1.0f + (m_positionOffset.y / 2.75f), 0.0f), m_shadowSprite.get());
    spriteBatch.AddSprite(glm::vec3(m_position - m_origin + m_positionOffset, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f), m_sprite.get());
}

void Peon::Select()
{
    m_isSelected = true;
}

void Peon::Deselect()
{
    m_isSelected = false;
}