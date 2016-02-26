#include "PCH.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include "../Engine/Camera.hpp"
#include "../Engine/Input.hpp"
#include "../Engine/Renderer.hpp"
#include "../Engine/Rectangle.hpp"
#include "Map/Map.hpp"
#include "Terrain/TerrainTile.hpp"
#include "Entity/Peon.hpp"
#include "Entity/Orc.hpp"
#include "Entity/Tree.hpp"
#include "Entity/Altar.hpp"
#include "Entity/Action/MoveAction.hpp"
#include "Entity/Action/GatherAction.hpp"
#include "Entity/Action/AttackAction.hpp"
#include "Entity/Action/PickUpAction.hpp"
#include "Entity/Action/SacrificeAction.hpp"

Player::Player(Game* game) :
    m_game(game),
    m_gameInput(nullptr),
    m_gameCamera(nullptr),
    m_gameRenderer(nullptr),
    m_gameMap(nullptr),
    m_cameraSpeed(CAMERA_SPEED_NORMAL),
    m_isBoxSelecting(false),
    m_boxSelection(0, 0, 0, 0)
{
    m_gameInput = m_game->GetInput();
    m_gameCamera = m_game->GetMainCamera();
    m_gameMap = m_game->GetMap();
}

Player::~Player()
{
}

void Player::Update(double deltaTime)
{
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
    else if (m_gameInput->GetKey(SDLK_LCTRL))
    {
        m_cameraSpeed = CAMERA_SPEED_SLOW;
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

            if (std::abs(m_boxSelection.width) >= 5 || std::abs(m_boxSelection.height) >= 5)
            {
                m_selectedPeons = m_gameMap->GetEntitiesInRectangle(PEON, m_boxSelection);
            }
            else
            {
                Vector2D mousePositionWorld = m_gameCamera->ConvertToWorld(m_gameInput->GetMousePosition());
                Entity* peon = m_gameMap->GetEntityAtPoint(mousePositionWorld, PEON);
                if (peon != nullptr)
                {
                    m_selectedPeons.push_back(peon);
                }
            }
        }
    }

    if (m_gameInput->GetMouseButtonPress(SDL_BUTTON_RIGHT))
    {
        IssueCommand(m_gameInput->GetMousePosition());
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
        if (std::abs(m_boxSelection.width) >= 5 || std::abs(m_boxSelection.height) >= 5)
        {
            m_gameRenderer->RenderOutlineRect(m_boxSelection, SDL_Color{ 0, 0, 0, 100 });
        }
    }

    for (auto peon : m_selectedPeons)
    {
        Vector2D position = peon->GetPosition() - peon->GetOrigin();
        position.y += 7;
        //Rectangle outline(position.x - 8, position.y, 16, 22);
        //m_gameRenderer->RenderOutlineRect(outline, SDL_Color{ 0, 0, 0, 100 });
        m_gameRenderer->RenderSprite("peon", 1, 7, (int)position.x, (int)position.y, 32, 32);
    }
}

void Player::IssueCommand(Vector2D position)
{
    for (auto it : m_selectedPeons)
    {
        Peon* peon = dynamic_cast<Peon*>(it);
        Vector2D worldPosition = m_gameCamera->ConvertToWorld(position);

        Entity* ent = m_gameMap->GetEntityAtPoint(worldPosition);
        if (ent != nullptr)
        {
            Resource* resource = dynamic_cast<Resource*>(ent);
            if (resource != nullptr)
            {
                if (!resource->IsFull() && !resource->IsDead())
                {
                    peon->ClearActionStack();
                    peon->PushAction(std::make_unique<GatherAction>(peon, resource));
                    continue;
                }
            } 

            Orc* orc = dynamic_cast<Orc*>(ent);
            if (orc != nullptr)
            {
                if (orc->IsDead())
                {
                    peon->ClearActionStack();
                    peon->PushAction(std::make_unique<PickUpAction>(peon, orc));
                    continue;
                }
                else
                {
                    peon->ClearActionStack();
                    peon->PushAction(std::make_unique<AttackAction>(peon, orc));
                    continue;
                }
            }

            Altar* altar = dynamic_cast<Altar*>(ent);
            if (altar != nullptr)
            {
                if (peon->GetHeldEntity() != nullptr)
                {
                    peon->ClearActionStack();
                    peon->PushAction(std::make_unique<SacrificeAction>(peon, altar));
                    continue;
                }
            }
        }
        else
        {
            // TODO move this into MoveAction
            if (m_gameMap->IsPassable(worldPosition))
            {
                double radius = 32;
                double angle = Random::Generate(0, 1) * M_PI * 2;
                double distance = Random::Generate(0, 1) * radius;
                Vector2D offset = Vector2D(distance * cos(angle), distance * sin(angle));
                if (m_gameMap->IsPassable(worldPosition + offset))
                {
                    worldPosition += offset;
                }

                peon->ClearActionStack();
                peon->PushAction(std::make_unique<MoveAction>(peon, worldPosition));
            }
        }
    }
}