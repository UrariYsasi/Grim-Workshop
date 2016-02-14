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
#include "Map/Map.hpp"
#include "Player.hpp"

Game::Game() :
    m_peonCount(0),
    m_frameCount(0),
    m_frameRate(0),
    m_gameStartTime(0),
    m_isRunning(false)
{
}

Game::~Game()
{
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

Input* Game::GetInput()
{
    return m_input.get();
}

Camera* Game::GetMainCamera()
{
    return m_mainCamera.get();
}

int Game::Initialize()
{
    // Enable Debugging
    Debug::EnableFlag(LOGGING);
    Debug::EnableFlag(SHOW_MENU);
    Debug::EnableFlag(CHEAT);

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

    m_map = std::make_unique<Map>(this);
    m_player = std::make_unique<Player>(this);

    // Load Textures
    LoadTexture("Resources/Textures/peon.png", "peon");
    LoadTexture("Resources/Textures/resource.png", "resource");
    LoadTexture("Resources/Textures/terrain.png", "terrain");
    LoadTexture("Resources/Textures/structure.png", "structure");
    LoadTexture("Resources/Textures/obelisk.png", "obelisk");

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
    m_map->Generate();

    return SUCCESS;
}

void Game::Run()
{
    if (m_isRunning)
    {
        Debug::LogError("Game::Run() cannot be called, Game is already running!");
        return;
    }

    m_isRunning = true;
    m_gameStartTime = SDL_GetTicks();

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
    if (m_input->GetKey(SDLK_ESCAPE))
    {
        Terminate();
    }

    if (m_input->GetKeyPress(SDLK_i))
    {
        Debug::ToggleFlag(SHOW_MENU);
    }

    if (Debug::IsFlagEnabled(CHEAT))
    {
        if (m_input->GetKeyPress(SDLK_y))
        {
            m_map->SpawnPeon();
        }

        if (m_input->GetKeyPress(SDLK_p))
        {
            Debug::ToggleFlag(RENDER_HITBOXES);
        }

        if (m_input->GetKeyPress(SDLK_k))
        {
            Debug::ToggleFlag(RENDER_TILE_OUTLINES);
        }

        if (m_input->GetKeyPress(SDLK_l))
        {
            Debug::ToggleFlag(RENDER_ORIGINS);
        }
    }

    m_map->Update(deltaTime);
    m_player->Update(deltaTime);
}

void Game::Render()
{
    m_renderer->SetDrawColor(SDL_Color{ 0, 0, 0, 255 });
    m_renderer->Clear();

    m_mainCamera->Activate();

    m_map->Render();
    m_player->Render();

    /*
    for (auto it = m_selectedPeons.begin(); it != m_selectedPeons.end(); it++)
    {
        Vector2D position = (*it)->GetPosition();
        Rectangle box(position.x - 8, position.y - 4, 16, 20);
        m_renderer->RenderOutlineRect(box);
        //m_renderer->RenderTexture("selection", static_cast<int>((*it)->GetPosition().x), static_cast<int>((*it)->GetPosition().y), 32, 32);
    }
    */

    // Render GUI
    m_GUICamera->Activate();

    Rectangle bottomBar(0, m_window->GetSize().y - 16, m_window->GetSize().x, 16);
    m_renderer->RenderFillRect(bottomBar, SDL_Color{ 128, 128, 128, 128 });
    Inventory* stock = FindStockpile()->GetInventory();

    std::stringstream ss;
    ss << "Wood: " << 0 << "         ";
    ss << "Stone: " << 0 << "         ";
    ss << "Coal: " << 0 << "         ";
    ss << "Iron Ore: " << 0 << "         ";
    ss << "Iron Bar: " << 0 << "         ";
    m_renderer->RenderText("dos", 5, (int)m_window->GetSize().y - 16, ss.str());
    ss.str(" ");

    // Debug stuff
    if (Debug::IsFlagEnabled(SHOW_MENU))
    {
        Rectangle container(5, 5, 340, 180);
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

        ss << "I - Toggle debug menu";
        m_renderer->RenderText("dos", 10, 95, ss.str());
        ss.str(" ");

        ss << "Y - Spawn peon";
        m_renderer->RenderText("dos", 10, 110, ss.str());
        ss.str(" ");

        ss << "U - Spawn tree";
        m_renderer->RenderText("dos", 10, 125, ss.str());
        ss.str(" ");

        ss << "P - Render hit boxes";
        m_renderer->RenderText("dos", 10, 140, ss.str());
        ss.str(" ");

        ss << "K - Render tile outlines";
        m_renderer->RenderText("dos", 10, 155, ss.str());
        ss.str(" ");

        ss << "L - Render origins";
        m_renderer->RenderText("dos", 10, 170, ss.str());
        ss.str(" ");
    }

    m_renderer->Present();
}

void Game::IssueCommand(Entity* ent)
{
    // Loop through all selected peons
    /*
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
    */
}

/*
    Search for a Stockpile.
    TODO: Refactor this into a template of some sort?
*/
Stockpile* Game::FindStockpile()
{
    /*
    for (auto it = m_entities.begin(); it != m_entities.end(); it++)
    {
        Stockpile* stockpile = dynamic_cast<Stockpile*>(*it);
        if (stockpile != nullptr)
        {
            return stockpile;
        }
    }
    */

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