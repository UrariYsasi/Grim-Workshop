#include "PCH.hpp"
#include "Orc.hpp"
#include "../Game.hpp"
#include "Action/MoveAction.hpp"
#include "Action/AttackAction.hpp"
#include "Peon.hpp"
#include "../World/World.hpp"

Orc::Orc(Game* game, const glm::vec2& position) :
    Monster(game, position, ORC)
{
    m_origin = glm::vec2(16, 16);
    m_hitBox = grim::graphics::Rect(-4, 0, 8, 16);
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

    World* map = m_game->GetWorld();

    // LOOK FOR ORC ATTACK ACTION
    AttackAction* attackAction = dynamic_cast<AttackAction*>(FindAction(ATTACK_ACTION));
    if (attackAction == nullptr)
    {
        // WE NEED ATTACK ACTION! ATTACK DE OBELISK!
        Entity* obeliskEnt = map->FindEntity(OBELISK);
        if (obeliskEnt != nullptr)
        {
            ClearActionStack();
            PushAction(std::make_unique<AttackAction>(this, obeliskEnt));
        }
    }
    else
    {
        // IF ATTACK ACTION IS NOT ALREADY ATTACKING PEON
        if (!attackAction->IsAttackingPeon())
        {
            // ORC SEARCH FOR PUNY PEONS TO SMASH
            grim::graphics::Rect searchRect(m_position.x - 128, m_position.y - 128, 256, 256);
            std::list<Entity*> peons = map->GetEntitiesInRect(PEON, searchRect);
            if (peons.size() > 0)
            {
                // ORC SEE PEONS. SMASH DEM!
                ClearActionStack();
                Entity* peonEnt = peons.back();
                PushAction(std::make_unique<AttackAction>(this, peonEnt));
            }
        }
    }
}

void Orc::Render(grim::graphics::SpriteBatch& spriteBatch)
{
    if (!IsDead())
    {
        spriteBatch.AddSprite(glm::vec3(m_position - m_origin + m_positionOffset, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(32.0, 32.0, 0), m_sprite.get());
    }

    // ORC LIKE TO DEBUG
    /*
    if (m_actionStack.size() > 0)
    {
        renderer->RenderText("dos", (int)(m_position.x), (int)(m_position.y), m_actionStack.back()->GetName());
    }
    */
    //Rect searchRect(m_position.x - 128, m_position.y - 128, 256, 256);
    //renderer->RenderOutlineRect(searchRect);

    Entity::Render(spriteBatch);
}

