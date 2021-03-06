#include "PCH.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include "World/World.hpp"
#include "Terrain/TerrainTile.hpp"
#include "Entity/Peon.hpp"
#include "Entity/Orc.hpp"
#include "Entity/Spider.hpp"
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
    m_gameWorld(nullptr),
    m_cameraSpeed(CAMERA_SPEED_NORMAL),
    m_isBoxSelecting(false),
    m_boxSelection(0, 0, 0, 0),
    m_boxSelectionMesh(grim::graphics::PrimitiveType::LINE_LOOP),
    m_faith(100),
    m_placementModule(this)
{
    m_gameInput = m_game->GetEngine()->GetInputModule();
    m_gameCamera = m_game->GetMainCamera();
    m_gameWorld = m_game->GetWorld();
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
    // Deselect any dead peons
    for (auto it = m_selectedPeons.begin(); it != m_selectedPeons.end(); it++)
    {
        if ((*it)->IsDead())
        {
            Peon* peon = dynamic_cast<Peon*>(*it);
            peon->Deselect();
            m_selectedPeons.erase(it++);
        }
    }

    glm::vec2 cameraMovement(0);

    /*
    if (m_gameInput->IsKeyHeld(SDLK_w) || m_gameInput->IsKeyHeld(SDLK_UP))
    {
        cameraMovement += glm::vec2(0.0f, -1.0f);
    }

    if (m_gameInput->IsKeyHeld(SDLK_a) || m_gameInput->IsKeyHeld(SDLK_LEFT))
    {
        cameraMovement += glm::vec2(-1.0f, 0.0f);
    }

    if (m_gameInput->IsKeyHeld(SDLK_s) || m_gameInput->IsKeyHeld(SDLK_DOWN))
    {
        cameraMovement += glm::vec2(0.0f, 1.0f);
    }

    if (m_gameInput->IsKeyHeld(SDLK_d) || m_gameInput->IsKeyHeld(SDLK_RIGHT))
    {
        cameraMovement += glm::vec2(1.0f, 0.0f);
    }

    if (m_gameInput->IsKeyHeld(SDLK_LSHIFT) || m_gameInput->IsKeyHeld(SDLK_RSHIFT))
    {
        m_cameraSpeed = CAMERA_SPEED_FAST;
    }
    else if (m_gameInput->IsKeyHeld(SDLK_LCTRL))
    {
        m_cameraSpeed = CAMERA_SPEED_SLOW;
    }
    else
    {
        m_cameraSpeed = CAMERA_SPEED_NORMAL;
    }
    */

    cameraMovement *= m_cameraSpeed;
    cameraMovement *= deltaTime;

    m_gameCamera->Move(cameraMovement);

    /*
    glm::vec2 worldSize = m_gameWorld->GetSize();
    glm::vec2 cameraPosition = m_gameCamera->GetPosition();
    if (cameraPosition.x < 0.0f)
    {
        cameraPosition.x = 0.0f;
    }
    else if ((cameraPosition.x + 1024.0f) > worldSize.x)
    {
        cameraPosition.x = worldSize.x - 1024.0f;
    }

    if (cameraPosition.y < 0.0f)
    {
        cameraPosition.y = 0.0f;
    }
    else if ((cameraPosition.y + 768.0f) > worldSize.y)
    {
        cameraPosition.y = worldSize.y - 768.0f;
    }

    m_gameCamera->SetPosition(cameraPosition);
    */

    /*
    glm::vec2 mousePositionScreen = m_gameInput->GetMousePosition();
    glm::vec2 mousePositionWorld = m_gameCamera->ConvertToWorld(mousePositionScreen);

    if ((m_gameInput->GetMouseButtonPress(SDL_BUTTON_LEFT)) && (!m_placementModule.IsPlacing()))
    {
        for (auto it : m_selectedPeons)
        {
            Peon* peon = dynamic_cast<Peon*>(it);
            peon->Deselect();
        }

        m_selectedPeons.clear();

        m_isBoxSelecting = true;

        m_boxSelection.x = mousePositionWorld.x;
        m_boxSelection.y = mousePositionWorld.y;
    }

    if (m_isBoxSelecting)
    {
        m_boxSelection.width = mousePositionWorld.x - m_boxSelection.x;
        m_boxSelection.height = mousePositionWorld.y - m_boxSelection.y;
    }

    if ((m_gameInput->GetMouseButtonRelease(SDL_BUTTON_LEFT)) && (!m_placementModule.IsPlacing()))
    {
        if (m_isBoxSelecting)
        {
            m_isBoxSelecting = false;

            if ((std::abs(m_boxSelection.width) >= 5) || (std::abs(m_boxSelection.height) >= 5))
            {
                m_selectedPeons = m_gameWorld->GetEntitiesInRect(EntityID::PEON, m_boxSelection);
            }
            else
            {
                Peon* peon = dynamic_cast<Peon*>(m_gameWorld->GetEntityAtPoint(mousePositionWorld, EntityID::PEON));
                if ((peon != nullptr) && (!peon->IsDead()))
                {
                    m_selectedPeons.push_back(peon);
                }
            }

            for (auto it : m_selectedPeons)
            {
                Peon* peon = dynamic_cast<Peon*>(it);
                peon->Select();
            }
        }

        if (m_selectedPeons.size() > 0)
        {
            m_game->GetEngine()->GetAudio()->PlaySound("select_01");
        }
    }

    if ((m_gameInput->GetMouseButtonPress(SDL_BUTTON_RIGHT)) && (!m_placementModule.IsPlacing()))
    {
        IssueCommand(mousePositionWorld);
    }
    */

    /*
        Update Modules
    */
    m_placementModule.Update(deltaTime);
}

void Player::Render()
{
    m_boxSelectionMesh.ClearData();

    if (m_isBoxSelecting)
    {
        if (std::abs(m_boxSelection.width) >= 5 || std::abs(m_boxSelection.height) >= 5)
        {
            grim::graphics::Vertex topLeft(glm::vec3(m_boxSelection.x, m_boxSelection.y, 1.0f));
            grim::graphics::Vertex topRight(glm::vec3(m_boxSelection.x + m_boxSelection.width, m_boxSelection.y, 1.0f));
            grim::graphics::Vertex bottomLeft(glm::vec3(m_boxSelection.x, m_boxSelection.y + m_boxSelection.height, 1.0f));
            grim::graphics::Vertex bottomRight(glm::vec3(m_boxSelection.x + m_boxSelection.width, m_boxSelection.y + m_boxSelection.height, 1.0f));

            m_boxSelectionMesh.AddVertex(topLeft);
            m_boxSelectionMesh.AddVertex(topRight);
            m_boxSelectionMesh.AddVertex(bottomLeft);
            m_boxSelectionMesh.AddVertex(bottomRight);

            m_boxSelectionMesh.AddIndex(0);
            m_boxSelectionMesh.AddIndex(1);
            m_boxSelectionMesh.AddIndex(3);
            m_boxSelectionMesh.AddIndex(2);

            grim::graphics::Transform boxSelectionTransform;
            grim::graphics::RenderCommand command(&m_boxSelectionMesh, m_game->GetMaterial("flat_black"), boxSelectionTransform);
            m_game->GetEngine()->GetRenderer()->Submit(command);
        }
    }

    /*
        Render Modules
    */

    m_placementModule.Render();
}

Game* Player::GetGame()
{
    return m_game;
}

grim::ui::IInputModule* Player::GetInput()
{
    return m_gameInput;
}

grim::graphics::Camera* Player::GetCamera()
{
    return m_gameCamera;
}

World* Player::GetWorld()
{
    return m_gameWorld;
}

void Player::IssueCommand(glm::vec2 position)
{
    for (auto it : m_selectedPeons)
    {
        Peon* peon = dynamic_cast<Peon*>(it);

        Entity* ent = m_gameWorld->GetEntityAtPoint(position);
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

            Spider* spider = dynamic_cast<Spider*>(ent);
            if (spider != nullptr)
            {
                if (spider->IsDead())
                {
                    peon->ClearActionStack();
                    peon->PushAction(std::make_unique<PickUpAction>(peon, spider));
                    continue;
                }
                else
                {
                    peon->ClearActionStack();
                    peon->PushAction(std::make_unique<AttackAction>(peon, spider));
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
            if (m_gameWorld->IsPassable(position))
            {
                double radius = 32;
                double angle = grim::utility::Random::Generate(0.0, 1.0) * M_PI * 2.0;
                double distance = grim::utility::Random::Generate(0.0, 1.0) * radius;
                glm::vec2 offset = glm::vec2(distance * cos(angle), distance * sin(angle));
                if (m_gameWorld->IsPassable(position + offset))
                {
                    position += offset;
                }

                peon->ClearActionStack();
                peon->PushAction(std::make_unique<MoveAction>(peon, glm::vec3(position, 0.0f)));
            }
        }
    }
}

Inventory* Player::GetInventory()
{
    return &m_inventory;
}

void Player::AddPeon(uint32_t quantity)
{
    m_peonCount += quantity;
}

void Player::RemovePeon(uint32_t quantity)
{
    m_peonCount -= quantity;
}

uint32_t Player::GetPeonCount() const
{
    return m_peonCount;
}

void Player::AddFaith(uint32_t quantity)
{
    m_faith += quantity;
}

void Player::RemoveFaith(uint32_t quantity)
{
    m_faith -= quantity;
}

uint32_t Player::GetFaith() const
{
    return m_faith;
}

PlacementModule* Player::GetPlacement()
{
    return &m_placementModule;
}