#include "PCH.hpp"
#include "Rock.hpp"
#include "../Game.hpp"

Rock::Rock(Game* game, const glm::vec2& position) :
    Resource(game, position, ROCK, ItemType::STONE)
{
    m_origin = glm::vec2(0, 0);
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
    if (!IsDead())
    {
        spriteBatch.AddSprite(glm::vec3(m_position - m_origin + m_positionOffset, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(32.0, 32.0, 0), m_sprite.get());
    }

    Entity::Render(spriteBatch);
}