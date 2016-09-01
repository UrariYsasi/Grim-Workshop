#include "PCH.hpp"
#include "PlacementModule.hpp"
#include "Player.hpp"
#include "World/World.hpp"
#include "Game.hpp"

PlacementModule::PlacementModule(Player* owner) :
    m_owner(owner),
    m_game(nullptr),
    m_input(nullptr),
    m_camera(nullptr),
    m_isPlacing(false),
    m_heldEntityID(EntityID::NONE)
{
}

PlacementModule::~PlacementModule()
{
}

void PlacementModule::Update(float deltaTime)
{
    if (m_game == nullptr)
    {
        m_game = m_owner->GetGame();
    }

    if (m_input == nullptr)
    {
        m_input = m_owner->GetInput();
    }

    if (m_camera == nullptr)
    {
        m_camera = m_owner->GetCamera();
    }

    if (m_world == nullptr)
    {
        m_world = m_owner->GetWorld();
    }

    if (m_input->GetKeyPress(SDLK_1))
    {
        m_isPlacing = !m_isPlacing;
        m_heldEntityID = EntityID::MONSTER_SPIDER_QUEEN;
        m_heldEntitySprite = m_game->GetEntitySprite(m_heldEntityID);
        m_game->GetEngine()->GetAudio()->PlaySound("select_00");
    }

    /*
    if (m_input->GetKeyPress(SDLK_2))
    {
        m_isPlacing = !m_isPlacing;
        m_heldEntityID = ENT_BEAM_EFFECT;
        m_heldEntitySprite = m_game->GetEntitySprite(m_heldEntityID);
        m_game->GetAudio()->PlaySound("select_00");
    }
    */

    if (m_isPlacing)
    {
        if (m_input->GetMouseButtonPress(SDL_BUTTON_LEFT))
        {
            if (m_owner->GetFaith() >= 20)
            {
                glm::vec2 mousePosition = m_camera->ConvertToWorld(m_input->GetMousePosition());
                glm::vec3 position(mousePosition, 0.0f);
                m_world->Spawn(EntityID::EFFECT_BEAM, position + glm::vec3(0.0f, 5.0f, 0.0f));
                m_world->Spawn(m_heldEntityID, position);
                m_owner->RemoveFaith(20);
            }
            else
            {
                m_game->GetEngine()->GetAudio()->PlaySound("error_00");
            }
        }

        if (m_input->GetMouseButtonPress(SDL_BUTTON_RIGHT))
        {
            m_isPlacing = false;
        }
    }
}

void PlacementModule::Render()
{
    if (m_isPlacing)
    {
        if (m_heldEntityID != EntityID::NONE)
        {
            glm::vec2 mousePosition = m_camera->ConvertToWorld(m_input->GetMousePosition());
            //m_heldEntitySprite->color.a = 0.5f;

            //m_spriteBatch.Begin();
            //m_spriteBatch.AddSprite(glm::vec3(mousePosition.x, mousePosition.y - 16.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f), m_heldEntitySprite);
            //m_spriteBatch.End();

            //m_heldEntitySprite->color.a = 1.0f;
        }
    }
}

void PlacementModule::SetHeldEntity(EntityID ID)
{
    m_isPlacing = true;
    m_heldEntityID = ID;
    m_heldEntitySprite = m_game->GetEntitySprite(ID);
}

bool PlacementModule::IsPlacing() const
{
    return m_isPlacing;
}