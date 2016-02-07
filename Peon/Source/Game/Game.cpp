#include "PCH.hpp"
#include "Game.hpp"
#include "../Engine/Window.hpp"
#include "../Engine/Renderer.hpp"
#include "../Engine/Input.hpp"
#include "../Engine/Camera.hpp"
#include "Entity/Peon.hpp"
#include "Entity/Tree.hpp"
#include "Entity/Rock.hpp"
#include "Entity/Stockpile.hpp"
#include "Entity/Forge.hpp"
#include "Entity/Action/MoveAction.hpp"
#include "Entity/Action/GatherAction.hpp"
#include "Entity/Action/SmeltAction.hpp"
#include "Terrain/GrassTile.hpp"

Game::Game() :
    m_peonCount(0),
    m_frameCount(0),
    m_frameRate(0),
    m_gameStartTime(0),
    m_isRunning(false),
    m_isBoxSelecting(false),
    m_boxSelection(0, 0, 0, 0)
{
}

Game::~Game()
{
    // Entity deletion
    while (!m_entities.empty())
    {
        delete m_entities.front();
        m_entities.pop_front();
    }

    // Texture deletion
    for (auto texIt = m_textureMap.begin(); texIt != m_textureMap.end(); texIt++)
    {
        SDL_DestroyTexture(texIt->second);
    }

    // Font deletion
    for (auto fontIt = m_fontMap.begin(); fontIt != m_fontMap.end(); fontIt++)
    {
        TTF_CloseFont(fontIt->second);
    }

    // Sound deletion
    for (auto soundIt = m_soundMap.begin(); soundIt != m_soundMap.end(); soundIt++)
    {
        Mix_FreeChunk(soundIt->second);
    }

    SDL_Quit();
    Mix_Quit();
    TTF_Quit();
}

Renderer* Game::GetRenderer()
{
    return m_renderer.get();
}

int Game::Initialize()
{
    //Debug::Disable();

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        Debug::LogError("SDL could not initialize! SDL error: %s", SDL_GetError());
        return FAILURE;
    }

    // Initialize SDL_image
    if (IMG_Init(IMG_INIT_PNG) < 0)
    {
        Debug::LogError("SDL_image could not initialize! SDL_image error: %s", IMG_GetError());
        return FAILURE;
    }

    //Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        Debug::LogError("SDL_mixer could not initialize! SDL_mixer error: %s", Mix_GetError());
        return FAILURE;
    }

    //Initialize SDL_ttf
    if (TTF_Init() < 0)
    {
        Debug::Log("SDL_ttf could not initialize! SDL_ttf error: %s", TTF_GetError());
        return FAILURE;
    }

    m_window = std::make_unique<Window>(1024, 768, "Peon");
    if (m_window->Initialize() == FAILURE)
    {
        return FAILURE;
    }

    m_renderer = std::make_unique<Renderer>(this, m_window.get());
    m_input = std::make_unique<Input>(this);
    m_mainCamera = std::make_unique<Camera>(m_renderer.get(), Vector2D(-512, -384));
    m_GUICamera = std::make_unique<Camera>(m_renderer.get(), Vector2D(0, 0));

    // Load Textures
    LoadTexture("Resources/Textures/peon.png", "peon");
    LoadTexture("Resources/Textures/resource.png", "resource");
    LoadTexture("Resources/Textures/terrain.png", "terrain");
    LoadTexture("Resources/Textures/structure.png", "structure");

    // legacy textures
    LoadTexture("Resources/Textures/man.png", "man");
    LoadTexture("Resources/Textures/man_2.png", "man2");
    LoadTexture("Resources/Textures/man_3.png", "man3");
    LoadTexture("Resources/Textures/man_4.png", "man4");
    LoadTexture("Resources/Textures/tree.png", "tree");
    LoadTexture("Resources/Textures/log.png", "log");
    LoadTexture("Resources/Textures/stone.png", "stone");
    LoadTexture("Resources/Textures/rock.png", "rock");
    LoadTexture("Resources/Textures/selection.png", "selection");
    LoadTexture("Resources/Textures/bonfire_0.png", "bonfire_0");
    LoadTexture("Resources/Textures/bonfire_1.png", "bonfire_1");
    LoadTexture("Resources/Textures/bonfire_2.png", "bonfire_2");
    LoadTexture("Resources/Textures/bonfire_3.png", "bonfire_3");
    LoadTexture("Resources/Textures/bonfire_4.png", "bonfire_4");
    LoadTexture("Resources/Textures/fire.png", "fire");
    LoadTexture("Resources/Textures/grass.png", "grass");

    // Load fonts
    LoadFont("Resources/Fonts/dos.ttf", "dos");

    // Load Sounds
    LoadSound("Resources/Sounds/woodcutting_00.wav", "woodcutting_00");
    LoadSound("Resources/Sounds/woodcutting_01.wav", "woodcutting_01");
    LoadSound("Resources/Sounds/woodcutting_02.wav", "woodcutting_02");
    LoadSound("Resources/Sounds/mining_00.wav", "mining_00");
    LoadSound("Resources/Sounds/mining_01.wav", "mining_01");
    LoadSound("Resources/Sounds/mining_02.wav", "mining_02");
    LoadSound("Resources/Sounds/drop_00.wav", "drop_00");
    LoadSound("Resources/Sounds/drop_01.wav", "drop_01");
    LoadSound("Resources/Sounds/death_00.wav", "death_00");

    // Setup the game
    GenerateMap();

    SpawnPeon();
    SpawnPeon();
    SpawnPeon();

    return SUCCESS;
}

void Game::Run()
{
    if (m_isRunning)
    {
        Debug::LogError("Game::Run() cannot be called, Game is already running!");
        return;
    }
    else
    {
        m_isRunning = true;
        m_gameStartTime = SDL_GetTicks();
    }

    double frameStartTime = 0.0;
    double frameEndTime = 0.0;
    while (m_isRunning)
    {
        frameStartTime = SDL_GetTicks();
        double deltaTime = (frameStartTime - frameEndTime) / 1000;
        frameEndTime = frameStartTime;

        m_input->Update();
        Update(deltaTime);
        Render();

        m_frameCount++;
        m_frameRate = (m_frameCount / (SDL_GetTicks() - m_gameStartTime)) * 1000;
    }
}

void Game::Terminate()
{
    m_isRunning = false;
}

void Game::Update(double deltaTime)
{
    CleanEntities();

    // Debugging
    if (m_input->GetKeyPress(SDLK_p))
    {
        SpawnPeon();
    }

    if (m_input->GetKeyPress(SDLK_o))
    {
        if (Debug::IsEnabled())
        {
            Debug::Disable();
        }
        else
        {
            Debug::Enable();
        }
    }

    // Camera movement
    Vector2D cameraMovement(0, 0);

    if (m_input->GetKey(SDLK_w) || m_input->GetKey(SDLK_UP))
    {
        cameraMovement += Vector2D(0, -1);
    }

    if (m_input->GetKey(SDLK_a) || m_input->GetKey(SDLK_LEFT))
    {
        cameraMovement += Vector2D(-1, 0);
    }

    if (m_input->GetKey(SDLK_s) || m_input->GetKey(SDLK_DOWN))
    {
        cameraMovement += Vector2D(0, 1);
    }

    if (m_input->GetKey(SDLK_d) || m_input->GetKey(SDLK_RIGHT))
    {
        cameraMovement += Vector2D(1, 0);
    }

    cameraMovement *= 1024;
    cameraMovement *= deltaTime;

    m_mainCamera->Move(cameraMovement);

    // Peon selection
    if (m_input->GetMouseButtonPress(SDL_BUTTON_LEFT))
    {
        m_selectedPeons.clear();

        Vector2D mousePositionScreen = m_input->GetMousePosition();
        Vector2D mousePositionWorld = m_mainCamera->ConvertToWorld(mousePositionScreen);

        m_isBoxSelecting = true;
        m_boxSelection.x = mousePositionWorld.x;
        m_boxSelection.y = mousePositionWorld.y;
    }

    if (m_isBoxSelecting)
    {
        Vector2D mousePositionScreen = m_input->GetMousePosition();
        Vector2D mousePositionWorld = m_mainCamera->ConvertToWorld(mousePositionScreen);
        m_boxSelection.width = mousePositionWorld.x - m_boxSelection.x;
        m_boxSelection.height = mousePositionWorld.y - m_boxSelection.y;
    }

    if (m_input->GetMouseButtonRelease(SDL_BUTTON_LEFT))
    {
        if (m_isBoxSelecting)
        {
            for (auto it = m_entities.begin(); it != m_entities.end(); it++)
            {
                Peon* peon = dynamic_cast<Peon*>(*it);
                if (peon != nullptr)
                {
                    if (peon->IsCollidingWithRect(m_boxSelection))
                    {
                        m_selectedPeons.push_back(peon);
                    }
                }
            }

            m_isBoxSelecting = false;
        }
    }

    // Peon commanding with right click
    if (m_input->GetMouseButtonPress(SDL_BUTTON_RIGHT))
    {
        // If we right clicked on a Resource, command the peon to start working on it.
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
    }

    // Game closing
    if (m_input->GetKeyPress(SDLK_ESCAPE))
    {
        Terminate();
    }

    // Update entities
    for (auto it = m_entities.begin(); it != m_entities.end(); it++)
    {
        (*it)->Update(deltaTime);
    }
}

void Game::Render()
{
    m_renderer->SetDrawColor(SDL_Color{ 255, 255, 255, 255 });
    m_renderer->Clear();

    // Render Game
    m_mainCamera->Activate();

    // Render terrain
    for (auto it = m_terrain.begin(); it != m_terrain.end(); it++)
    {
        (*it)->Render();
    }

    // Render entities
    for (auto it = m_entities.begin(); it != m_entities.end(); it++)
    {
        (*it)->Render();
    }

    for (auto it = m_selectedPeons.begin(); it != m_selectedPeons.end(); it++)
    {
        m_renderer->RenderTexture("selection", static_cast<int>((*it)->GetPosition().x), static_cast<int>((*it)->GetPosition().y), 32, 32);
    }

    if (m_isBoxSelecting)
    {
        m_renderer->RenderOutlineRect(m_boxSelection);
    }

    // Render GUI
    m_GUICamera->Activate();

    Rectangle bottomBar(0, m_window->GetSize().y - 16, m_window->GetSize().x, 16);
    m_renderer->RenderFillRect(bottomBar, SDL_Color{ 128, 128, 128, 128 });
    Inventory* stock = FindStockpile()->GetInventory();

    std::stringstream ss;
    ss << "Wood: " << stock->CountItem(ItemType::WOOD) << "         ";
    ss << "Stone: " << stock->CountItem(ItemType::STONE) << "         ";
    ss << "Coal: " << stock->CountItem(ItemType::COAL) << "         ";
    ss << "Iron Ore: " << stock->CountItem(ItemType::IRON_ORE) << "         ";
    ss << "Iron Bar: " << stock->CountItem(ItemType::IRON_BAR) << "         ";
    m_renderer->RenderText("dos", 5, (int)m_window->GetSize().y - 16, ss.str());
    ss.str(" ");

    // Debug stuff
    if (Debug::IsEnabled())
    {
        Rectangle container(5, 5, 340, 125);
        m_renderer->RenderFillRect(container, SDL_Color{ 128, 128, 128, 128 });

        ss << "Framerate: " << (int)m_frameRate;
        m_renderer->RenderText("dos", 10, 10, ss.str());
        ss.str(" ");

        ss << "Peon Count: " << m_peonCount;
        m_renderer->RenderText("dos", 10, 25, ss.str());
        ss.str(" ");

        Vector2D mouseScreenPosition = m_input->GetMousePosition();
        ss << "Mouse Position(Screen): " << "(" << (int)mouseScreenPosition.x << "," << (int)mouseScreenPosition.y << ")";
        m_renderer->RenderText("dos", 10, 40, ss.str());
        ss.str(" ");

        Vector2D mouseWorldPosition = m_mainCamera->ConvertToWorld(mouseScreenPosition);
        ss << "Mouse Position(World): " << "(" << (int)mouseWorldPosition.x << "," << (int)mouseWorldPosition.y << ")";
        m_renderer->RenderText("dos", 10, 55, ss.str());
        ss.str(" ");

        Vector2D cameraPosition = m_mainCamera->GetPosition();
        ss << "Camera Position: " << "(" << (int)cameraPosition.x << "," << (int)cameraPosition.y << ")";
        m_renderer->RenderText("dos", 10, 70, ss.str());
        ss.str(" ");

        ss << "P - Spawn peon";
        m_renderer->RenderText("dos", 10, 95, ss.str());
        ss.str(" ");

        ss << "O - Toggle debug";
        m_renderer->RenderText("dos", 10, 110, ss.str());
        ss.str(" ");
    }

    m_renderer->Present();
}

/*
    Delete all entities that have been marked for deletion in the previous frame.
*/
void Game::CleanEntities()
{
    for (auto it = m_entities.begin(); it != m_entities.end(); it++)
    {
        if ((*it)->IsDeleted())
        {
            delete (*it);
            m_entities.erase(it++);
        }
    }
}

void Game::SpawnPeon()
{
    Vector2D position(rand() % 600, rand() % 400);
    Peon* peon = new Peon(this, position);
    m_entities.push_back(peon);
    m_peonCount++;
}

void Game::IssueCommand(Entity* ent)
{
    // Loop through all selected peons
    for (auto it = m_selectedPeons.begin(); it != m_selectedPeons.end(); it++)
    {
        Peon* peon = (*it);

        if (ent != nullptr)
        {
            // If we commanded them to a resource, they will begin working on that resource
            Resource* resource = dynamic_cast<Resource*>(ent);
            if (resource != nullptr)
            {
                peon->ClearActions();
                peon->PushAction(std::make_unique<GatherAction>(peon, resource));
            }

            Forge* forge = dynamic_cast<Forge*>(ent);
            if (forge != nullptr)
            {
                peon->ClearActions();
                peon->PushAction(std::make_unique<SmeltAction>(peon, forge));
            }
        }
        else
        {
            // If we commanded them to empty space, they will just walk to the clicked position
            peon->ClearActions();
            Vector2D position = m_mainCamera->ConvertToWorld(m_input->GetMousePosition());
            peon->PushAction(std::make_unique<MoveAction>(peon, position));
        }
    }
}

/*
    Generate the terrain and the props on top of it.
*/
void Game::GenerateMap()
{
    // Generate terrain
    for (int x = -(MAP_SIZE / 2); x < (MAP_SIZE / 2); x++)
    {
        for (int y = -(MAP_SIZE / 2); y < (MAP_SIZE / 2); y++)
        {
            std::unique_ptr<GrassTile> tile = std::make_unique<GrassTile>(this, Vector2D(x * 32, y * 32));
            m_terrain.push_back(std::move(tile));
        }
    }

    // Generate props
    for (int i = 0; i < 20; i++)
    {
        Vector2D position((int)Random::Generate(-(MAP_SIZE / 2), (MAP_SIZE / 2)), (int)Random::Generate(-(MAP_SIZE / 2), (MAP_SIZE / 2)));
        Tree* tree = new Tree(this, position * 32);
        m_entities.push_back(tree);
    }

    for (int i = 0; i < 10; i++)
    {
        Vector2D position((int)Random::Generate(-(MAP_SIZE / 2), (MAP_SIZE / 2)), (int)Random::Generate(-(MAP_SIZE / 2), (MAP_SIZE / 2)));
        Rock* rock = new Rock(this, position * 32);
        m_entities.push_back(rock);
    }

    Stockpile* stockpile = new Stockpile(this, Vector2D(0, 0));
    m_entities.push_back(stockpile);

    Forge* forge = new Forge(this, Vector2D(128, 0));
    m_entities.push_back(forge);
}

/*
    Search for a Stockpile.
    TODO: Refactor this into a template of some sort?
*/
Stockpile* Game::FindStockpile()
{
    for (auto it = m_entities.begin(); it != m_entities.end(); it++)
    {
        Stockpile* stockpile = dynamic_cast<Stockpile*>(*it);
        if (stockpile != nullptr)
        {
            return stockpile;
        }
    }

    return nullptr;
}

bool Game::LoadTexture(const std::string& path, const std::string& id)
{
    // Tyren Review: You should wrap the SDL_????? classes instead of holding onto them.
    // Like you did with the Renderer and Window. Later, if you decided to support a different
    // Rendering platform you could change the underlying classes and it might just work!
    SDL_Surface* tempSurface = IMG_Load(path.c_str());
    if (tempSurface == nullptr)
    {
        Debug::LogError("Failed to load image %s! SDL_image error: %s", path.c_str(), IMG_GetError());
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer->GetSDLRenderer(), tempSurface);
    SDL_FreeSurface(tempSurface);
    if (texture == nullptr)
    {
        Debug::LogError("Failed to create texture from %s, SDL error: %s", path.c_str(), SDL_GetError());
        return false;
    }

    m_textureMap[id] = texture;
    Debug::Log("Texture %s loaded.", id.c_str());
    return true;
}

bool Game::LoadFont(const std::string& path, const std::string& id, const int& size)
{
    TTF_Font* font = TTF_OpenFont(path.c_str(), size);
    if (font == nullptr)
    {
        Debug::LogError("Failed to load font %s! SDL_ttf error:", path.c_str(), TTF_GetError());
    }

    m_fontMap[id] = font;
    Debug::Log("Font %s loaded.", id.c_str());
    return true;
}

bool Game::LoadSound(const std::string& path, const std::string& id)
{
    Mix_Chunk* sound = Mix_LoadWAV(path.c_str());
    if (sound == nullptr)
    {
        Debug::LogError("Failed to load WAV from %s! SDL_mixer error: ", path.c_str(), Mix_GetError());
        return false;
    }

    m_soundMap[id] = sound;
    Debug::Log("Sound %s loaded.", id.c_str());
    return true;
}

SDL_Texture* Game::GetTexture(const std::string& id)
{
    return m_textureMap[id];
}

TTF_Font* Game::GetFont(const std::string& id)
{
    return m_fontMap[id];
}

void Game::PlaySound(const std::string& id)
{
    if (m_soundMap[id] == nullptr)
    {
        Debug::LogError("Sound %s can't be played, as it doesn't exist!", id.c_str());
    }

    Mix_PlayChannel(-1, m_soundMap[id], 0);
}