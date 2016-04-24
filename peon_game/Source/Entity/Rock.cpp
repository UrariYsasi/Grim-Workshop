#include "PCH.hpp"
#include "Rock.hpp"
#include "../Game.hpp"

Rock::Rock(Game* game, const glm::vec3& position) :
    Resource(game, position, EntityID::RESOURCE_ROCK, ItemType::STONE)
{
    m_hitBox = grim::graphics::Rect(-16, -16, 32, 32);
    m_hp = 10;

    grim::graphics::Texture* texture = game->GetTexture("resource");
    grim::graphics::ShaderProgram* shaderProgram = game->GetShaderProgram("basic_shader");
    m_sprite = std::make_unique<grim::graphics::Sprite>(texture, shaderProgram, 32, 32, 2);
}

Rock::~Rock()
{
}

ItemType Rock::GetItem() const
{
    int rand = static_cast<uint16_t>(grim::utility::Random::Generate(0.0, 100.0));
    if (rand > 95)
    {
        return ItemType::IRON_ORE;
    }
    else if (rand > 80)
    {
        return ItemType::COAL;
    }

    return m_item;
}

void Rock::Update(float deltaTime)
{
}

void Rock::Render(grim::graphics::SpriteBatch& spriteBatch)
{
    spriteBatch.AddSprite(m_transform.position - m_origin + m_positionOffset, m_transform.rotation, m_transform.scale, m_sprite.get());

    Entity::Render(spriteBatch);
}