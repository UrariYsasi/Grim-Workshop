#include "PCH.hpp"
#include "Peon.hpp"
#include "../Game.hpp"
#include "Action/MoveAction.hpp"
#include "Action/IdleAction.hpp"
#include "Action/AttackAction.hpp"
#include "Orc.hpp"
#include "../World/World.hpp"

Peon::Peon(Game* game, const glm::vec2& position) :
    Monster(game, position, PEON),
    m_isSelected(false),
    m_selectionSprite(nullptr)
{
    m_origin = glm::vec2(0, 0);
    m_hitBox = grim::graphics::Rect(-3.0f, 0.0f, 7.0f, 16.0f);

    grim::graphics::Texture* texture = game->GetTexture("peon");
    grim::graphics::ShaderProgram* shaderProgram = game->GetShaderProgram("basic_shader");
    m_sprite = std::make_unique<grim::graphics::Sprite>(texture, shaderProgram, 32, 32, 0);
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

    // If we don't have an attack action already
    AttackAction* attackAction = dynamic_cast<AttackAction*>(FindAction(ATTACK_ACTION));
    if (attackAction == nullptr)
    {
        // Search for some Orcs
        grim::graphics::Rect searchRect(m_position.x - 64, m_position.y - 64, 128, 128);
        std::list<Entity*> orcs = world->GetEntitiesInRect(ORC, searchRect);
        if (orcs.size() > 0)
        {
            // Found some orcs. Go attack them.
            ClearActionStack();
            Entity* orcEnt = orcs.back();
            PushAction(std::make_unique<AttackAction>(this, orcEnt));
        }
    }

    // If this Peon has no actions, add an IdleAction.
    if (m_actionStack.size() == 0)
    {
        std::unique_ptr<Action> action = std::make_unique<IdleAction>(this);
        m_actionStack.push_back(std::move(action));
    }
}

void Peon::Render(grim::graphics::SpriteBatch& spriteBatch)
{
    if (!IsDead())
    {
        if (m_isSelected)
        {
            spriteBatch.AddSprite(glm::vec3(m_position - m_origin + glm::vec2(0, 3.0), 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(32.0, 32.0, 0), m_selectionSprite.get());
        }

        spriteBatch.AddSprite(glm::vec3(m_position - m_origin + glm::vec2(0, 16.0), 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(32.0 + (m_positionOffset.y * 2.0), 32.0 + (m_positionOffset.y * 2.0), 0), m_shadowSprite.get());
        spriteBatch.AddSprite(glm::vec3(m_position - m_origin + m_positionOffset, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(32.0, 32.0, 0), m_sprite.get());
    }

    Entity::Render(spriteBatch);
}

void Peon::Select()
{
    m_isSelected = true;
}

void Peon::Deselect()
{
    m_isSelected = false;
}