#include "PCH.hpp"
#include "PlacementModule.hpp"
#include "Player.hpp"
#include "World\World.hpp"
#include "Game.hpp"

PlacementModule::PlacementModule(Player* owner) :
    m_owner(owner),
    m_input(nullptr),
    m_camera(nullptr),
    m_isPlacing(false),
    m_heldEntityID(NONE)
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
        m_heldEntityID = STRUCTURE_STOCKPILE;
        m_heldEntitySprite = m_game->GetEntitySprite(STRUCTURE_STOCKPILE);
        m_game->PlaySound("select_00");
    }

    if (m_isPlacing)
    {
        if (m_input->GetMouseButtonPress(SDL_BUTTON_LEFT))
        {
            glm::vec2 mousePosition = m_camera->ConvertToWorld(m_input->GetMousePosition());
            m_world->Spawn(m_heldEntityID, mousePosition);
            m_game->PlaySound("drop_00");
        }
    }
}

void PlacementModule::Render()
{
    if (m_isPlacing)
    {
        if (m_heldEntityID != NONE)
        {
            glm::vec2 mousePosition = m_camera->ConvertToWorld(m_input->GetMousePosition());
            m_heldEntitySprite->color.a = 0.5f;

            m_spriteBatch.Begin();
            m_spriteBatch.AddSprite(glm::vec3(mousePosition.x, mousePosition.y, 0.0f), glm::vec3(0.0f), glm::vec3(32.0f, 32.0f, 0.0f), m_heldEntitySprite);
            m_spriteBatch.End();
        }
    }
}