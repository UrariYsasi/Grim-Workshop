#include "PCH.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include "World/World.hpp"
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
    m_gameWorld(nullptr),
    m_cameraSpeed(CAMERA_SPEED_NORMAL),
    m_isBoxSelecting(false),
    m_boxSelection(0, 0, 0, 0),
    m_boxSelectionMesh(nullptr)
{
    m_gameInput = m_game->GetInput();
    m_gameCamera = m_game->GetMainCamera();
    m_gameWorld = m_game->GetWorld();

    // Create the box selection mesh
    GLuint elements[] = {
        0, 1, 3, 2
    };

    m_boxSelectionMesh = std::make_unique<grim::graphics::Mesh>(m_game->GetShaderProgram("basic_shader"), nullptr);
    m_boxSelectionMesh->UploadElementData(elements, sizeof(elements));
    m_boxSelectionMesh->SetRenderMode(GL_LINE_LOOP);
}

Player::~Player()
{
    m_boxSelectionMesh.reset();
}

void Player::Update(double deltaTime)
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

    if (m_gameInput->GetKey(SDLK_w) || m_gameInput->GetKey(SDLK_UP))
    {
        cameraMovement += glm::vec2(0.0f, -1.0f);
    }

    if (m_gameInput->GetKey(SDLK_a) || m_gameInput->GetKey(SDLK_LEFT))
    {
        cameraMovement += glm::vec2(-1.0f, 0.0f);
    }

    if (m_gameInput->GetKey(SDLK_s) || m_gameInput->GetKey(SDLK_DOWN))
    {
        cameraMovement += glm::vec2(0.0f, 1.0f);
    }

    if (m_gameInput->GetKey(SDLK_d) || m_gameInput->GetKey(SDLK_RIGHT))
    {
        cameraMovement += glm::vec2(1.0f, 0.0f);
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

    glm::vec2 mousePositionScreen = m_gameInput->GetMousePosition();
    glm::vec2 mousePositionWorld = m_gameCamera->ConvertToWorld(mousePositionScreen);

    if (m_gameInput->GetMouseButtonPress(SDL_BUTTON_LEFT))
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

    if (m_gameInput->GetMouseButtonRelease(SDL_BUTTON_LEFT))
    {
        if (m_isBoxSelecting)
        {
            m_isBoxSelecting = false;

            if (std::abs(m_boxSelection.width) >= 5 || std::abs(m_boxSelection.height) >= 5)
            {
                m_selectedPeons = m_gameWorld->GetEntitiesInRect(PEON, m_boxSelection);
            }
            else
            {
                Peon* peon = dynamic_cast<Peon*>(m_gameWorld->GetEntityAtPoint(mousePositionWorld, PEON));
                if (peon != nullptr)
                {
                    if (!peon->IsDead())
                    {
                        m_selectedPeons.push_back(peon);
                    }
                }
            }

            for (auto it : m_selectedPeons)
            {
                Peon* peon = dynamic_cast<Peon*>(it);
                peon->Select();
            }
        }
    }

    if (m_gameInput->GetMouseButtonPress(SDL_BUTTON_RIGHT))
    {
        IssueCommand(mousePositionWorld);
    }
}

void Player::Render()
{
    if (m_isBoxSelecting)
    {
        if (std::abs(m_boxSelection.width) >= 5 || std::abs(m_boxSelection.height) >= 5)
        {
            GLfloat vertices[] = {
                // Top left
                m_boxSelection.x, m_boxSelection.y, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                // Top right
                m_boxSelection.x + m_boxSelection.width, m_boxSelection.y, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  
                // Bottom left
                m_boxSelection.x, m_boxSelection.y + m_boxSelection.height, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  
                // Bottom right
                m_boxSelection.x + m_boxSelection.width, m_boxSelection.y + m_boxSelection.height, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
            };

            m_boxSelectionMesh->UploadVertexData(vertices, sizeof(vertices));
            m_boxSelectionMesh->Render(glm::vec3(0.0), glm::vec3(0.0), glm::vec3(1, 1, 0));
        }
    }

    /*
    for (auto peon : m_selectedPeons)
    {
        glm::vec2 position = peon->GetPosition() - peon->GetOrigin();
        position.y += 7;
        //Rect outline(position.x - 8, position.y, 16, 22);
        //m_gameRenderer->RenderOutlineRect(outline, SDL_Color{ 0, 0, 0, 100 });
        m_gameRenderer->RenderSprite("peon", 1, 7, (int)position.x, (int)position.y, 32, 32);
    }
    */
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
                peon->PushAction(std::make_unique<MoveAction>(peon, position));
            }
        }
    }
}