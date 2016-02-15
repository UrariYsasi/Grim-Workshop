#include "PCH.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include "../Engine/Camera.hpp"
#include "../Engine/Input.hpp"
#include "../Engine/Renderer.hpp"
#include "../Engine/Rectangle.hpp"
#include "Map/Map.hpp"

Player::Player(Game* game) :
    m_game(game),
    m_cameraSpeed(CAMERA_SPEED_NORMAL),
    m_isBoxSelecting(false),
    m_boxSelection(0, 0, 0, 0)
{
}

Player::~Player()
{
}

void Player::Update(double deltaTime)
{
    if (m_gameInput == nullptr)
    {
        m_gameInput = m_game->GetInput();
    }

    if (m_gameCamera == nullptr)
    {
        m_gameCamera = m_game->GetMainCamera();
    }

    if (m_gameMap == nullptr)
    {
        m_gameMap = m_game->GetMap();
    }

    Vector2D cameraMovement(0, 0);

    if (m_gameInput->GetKey(SDLK_w) || m_gameInput->GetKey(SDLK_UP))
    {
        cameraMovement += Vector2D(0, -1);
    }

    if (m_gameInput->GetKey(SDLK_a) || m_gameInput->GetKey(SDLK_LEFT))
    {
        cameraMovement += Vector2D(-1, 0);
    }

    if (m_gameInput->GetKey(SDLK_s) || m_gameInput->GetKey(SDLK_DOWN))
    {
        cameraMovement += Vector2D(0, 1);
    }

    if (m_gameInput->GetKey(SDLK_d) || m_gameInput->GetKey(SDLK_RIGHT))
    {
        cameraMovement += Vector2D(1, 0);
    }

    if (m_gameInput->GetKey(SDLK_LSHIFT) || m_gameInput->GetKey(SDLK_RSHIFT))
    {
        m_cameraSpeed = CAMERA_SPEED_FAST;
    }
    else
    {
        m_cameraSpeed = CAMERA_SPEED_NORMAL;
    }

    cameraMovement *= m_cameraSpeed;
    cameraMovement *= deltaTime;

    m_gameCamera->Move(cameraMovement);
    
    Vector2D cameraPosition = m_gameCamera->GetPosition();
    if (cameraPosition.y < -1000)
    {
        cameraPosition.y = -1000;
    }
    else if (cameraPosition.y + 768 > 1000)
    {
        cameraPosition.y = 1000 - 768;
    }

    if (cameraPosition.x < -1000)
    {
        cameraPosition.x = -1000;
    }
    else if (cameraPosition.x + 1024 > 1000)
    {
        cameraPosition.x = 1000 - 1024;
    }

    m_gameCamera->SetPosition(cameraPosition);

    if (m_gameInput->GetMouseButtonPress(SDL_BUTTON_LEFT))
    {
        m_selectedPeons.clear();

        m_isBoxSelecting = true;

        Vector2D mousePositionScreen = m_gameInput->GetMousePosition();
        Vector2D mousePositionWorld = m_gameCamera->ConvertToWorld(mousePositionScreen);

        m_boxSelection.x = mousePositionWorld.x;
        m_boxSelection.y = mousePositionWorld.y;
    }

    if (m_isBoxSelecting)
    {
        Vector2D mousePositionScreen = m_gameInput->GetMousePosition();
        Vector2D mousePositionWorld = m_gameCamera->ConvertToWorld(mousePositionScreen);
        m_boxSelection.width = mousePositionWorld.x - m_boxSelection.x;
        m_boxSelection.height = mousePositionWorld.y - m_boxSelection.y;
    }

    if (m_gameInput->GetMouseButtonRelease(SDL_BUTTON_LEFT))
    {
        if (m_isBoxSelecting)
        {
            m_isBoxSelecting = false;
            m_selectedPeons = m_gameMap->GetPeonsInRectangle(m_boxSelection);
        }
    }

    if (m_gameInput->GetMouseButtonPress(SDL_BUTTON_RIGHT))
    {
        // If we right clicked on a Resource, command the peon to start working on it.
        /*
        Entity* ent = nullptr;
        for (auto it = m_entities.begin(); it != m_entities.end(); it++)
        {
        Vector2D mousePositionScreen = m_input->GetMousePosition();
        Vector2D mousePositionWorld = m_mainCamera->ConvertToWorld(mousePositionScreen);
        Rectangle mouseRect(mousePositionWorld.x - 2, mousePositionWorld.y - 2, 2, 2);
        if ((*it)->IsCollidingWithRect(mouseRect))
        {
        ent = (*it);
        }
        }

        IssueCommand(ent);
        */
    }
}

void Player::Render()
{
    if (m_gameRenderer == nullptr)
    {
        m_gameRenderer = m_game->GetRenderer();
    }

    if (m_isBoxSelecting)
    {
        m_gameRenderer->RenderOutlineRect(m_boxSelection, SDL_Color{ 0, 0, 0, 100 });
    }
}