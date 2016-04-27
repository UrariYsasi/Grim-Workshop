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

Peon::Peon(Game* game, const glm::vec3& position) :
    Monster(game, position, EntityID::PEON),
    m_isSelected(false),
    m_selectionSprite(),
    m_shadowSprite()
{
    m_game->GetPlayer()->AddPeon();

    m_origin.y = 16.0f;
    m_hitBox = grim::graphics::Rect(-3.0f, -16.0f, 7.0f, 16.0f);

    uint8_t col = static_cast<uint8_t>(std::round(grim::utility::Random::Generate(-0.4f, 4.4f)));
    m_sprite = grim::graphics::Sprite(m_game->GetMaterial("sprite_peon"), 32, 32, col);
    m_selectionSprite = grim::graphics::Sprite(m_game->GetMaterial("sprite_peon"), 32, 32, 57);
    m_shadowSprite = grim::graphics::Sprite(m_game->GetMaterial("sprite_peon"), 32, 32, 58);
}

Peon::~Peon()
{
}

void Peon::Update(float deltaTime)
{
    Monster::Update(deltaTime);

    World* world = m_game->GetWorld();

    // Check if we have moved into an unexplored Region
    glm::ivec2 coordinates = world->ConvertToRegionCoordinates(m_transform.position);
    if (!world->IsRegionExplored(coordinates))
    {
        world->ExploreRegion(coordinates);
    }
}

void Peon::Render()
{
    grim::graphics::Transform peonTransform = m_transform;
    peonTransform.position -= m_origin;
    peonTransform.position += m_positionOffset;
    grim::graphics::RenderCommand peonCommand(&m_sprite, peonTransform);

    grim::graphics::Transform shadowTransform = m_transform;
    shadowTransform.position.z -= 0.0001f;
    shadowTransform.position -= m_origin;
    shadowTransform.position += glm::vec3(0.0f, 16.0f, 0.0f);
    shadowTransform.scale = glm::vec3(1.0f + (m_positionOffset.y / 2.75f), 1.0f + (m_positionOffset.y / 2.75f), 0.0f);
    grim::graphics::RenderCommand shadowCommand(&m_shadowSprite, shadowTransform);

    if (m_isSelected)
    {
        grim::graphics::Transform selectionTransform = m_transform;
        selectionTransform.position.z -= 0.0002f;
        selectionTransform.position -= m_origin;
        selectionTransform.position += glm::vec3(0.0f, 3.0f, 0.0f);
        grim::graphics::RenderCommand selectionCommand(&m_selectionSprite, selectionTransform);
        m_game->GetRenderer()->Submit(selectionCommand);
    }

    m_game->GetRenderer()->Submit(shadowCommand);
    m_game->GetRenderer()->Submit(peonCommand);
}

void Peon::Select()
{
    m_isSelected = true;
}

void Peon::Deselect()
{
    m_isSelected = false;
}