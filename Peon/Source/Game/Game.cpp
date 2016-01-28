#include "../PCH.hpp"
#include "Game.hpp"
#include "../Engine/Vector2D.hpp"
#include "Entity/Tree.hpp"
#include "Entity/Stockpile.hpp"
#include "Entity/Action/MoveAction.hpp"
#include "Entity/Action/GatherAction.hpp"

Game::Game() :
    m_deltaTime(0.0),
    m_peonCount(0),
    m_isRunning(true),
    m_resources(0)
{
}

Game::~Game()
{
    // Delete entities
    while(!m_entities.empty())
    {
        delete m_entities.front();
        m_entities.pop_front();
    }

    std::map<std::string, SDL_Texture*>::const_iterator texIt;
    for (texIt = m_textureMap.begin(); texIt != m_textureMap.end(); texIt++)
    {
        SDL_DestroyTexture(texIt->second);
    }

    std::map<std::string, TTF_Font*>::const_iterator fontIt;
    for (fontIt = m_fontMap.begin(); fontIt != m_fontMap.end(); fontIt++)
    {
        TTF_CloseFont(fontIt->second);
    }

    std::map<std::string, Mix_Chunk*>::const_iterator soundIt;
    for (soundIt = m_soundMap.begin(); soundIt != m_soundMap.end(); soundIt++)
    {
        Mix_FreeChunk(soundIt->second);
    }

    SDL_Quit();
    Mix_Quit();
    TTF_Quit();
}

void Game::Initialize()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL error: " << SDL_GetError() << std::endl;
    }

    // Initialize SDL_image
    if (IMG_Init(IMG_INIT_PNG) < 0)
    {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
    }

    //Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }

    //Initialize SDL_ttf
    if (TTF_Init() < 0)
    {
        std::cerr << "SDL_ttf could not be initialized! SDL_ttf error: " << TTF_GetError() << std::endl;
    }

    m_window = std::make_unique<Window>(640, 480, "Peon");
    m_renderer = std::make_unique<Renderer>(m_window.get());
    m_input = std::make_unique<Input>(this);

    // Load Textures
    LoadTexture("Resources/Textures/peon.png", "peon");
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
    Tree* tree = new Tree(this, Vector2D(200, 200));
    m_entities.push_back(tree);

    Tree* tree2 = new Tree(this, Vector2D(400, 150));
    m_entities.push_back(tree2);

    Tree* tree3 = new Tree(this, Vector2D(300, 400));
    m_entities.push_back(tree3);

    Stockpile* stockpile = new Stockpile(this, Vector2D(304, 224));
    m_entities.push_back(stockpile);

    SpawnPeon();
    SpawnPeon();
    SpawnPeon();

    // Game loop
    double frameStartTime = 0.0;
    double frameEndTime = 0.0;
    while (m_isRunning)
    {
        frameStartTime = SDL_GetTicks();
        m_deltaTime = (frameStartTime - frameEndTime) / 1000;
        frameEndTime = frameStartTime;

        m_input->Update();
        Update();
        Render();
    }
}

void Game::Terminate()
{
    m_isRunning = false;
}

void Game::Update()
{
    CleanEntities();

    if(m_input->GetKeyPress(SDLK_w))
    {
        SpawnPeon();
    }

    if(m_input->GetKeyPress(SDLK_s))
    {
        m_entities.back()->Delete();
    }

    // Debugging
    if (m_input->GetKey(SDLK_p))
    {
        SpawnPeon();
    }

    // Peon selection
    if(m_input->GetMouseButtonPress(SDL_BUTTON_LEFT))
    {
        m_selectedPeons.clear();
    }

    if(m_input->GetMouseButtonRelease(SDL_BUTTON_LEFT))
    {
        // If we are currently box selecting
        if(m_input->IsBoxSelecting())
        {
            // Select all the peons that are within the selection box
            for(std::list<Entity*>::const_iterator it = m_entities.begin(); it != m_entities.end(); it++)
            {
                Peon* peon = dynamic_cast<Peon*>(*it);
                if(peon != nullptr)
                {
                    SDL_Rect selectionRect = m_input->GetBoxSelection();
                    if(peon->IsCollidingWithRect(selectionRect))
                    {
                        m_selectedPeons.push_back(peon);
                    }
                }
            }
        }

        // We can end the selection box now.
        m_input->EndBoxSelection();
    }

    // Peon commanding with right click
    if(m_input->GetMouseButtonPress(SDL_BUTTON_RIGHT))
    {
        // If we right clicked on a Resource, command the peon to start working on it.
        Entity* ent = nullptr;
        for(std::list<Entity*>::const_iterator it = m_entities.begin(); it != m_entities.end(); it++)
        {
            SDL_Rect mouseRect = { static_cast<int>(m_input->GetMousePosition().GetX()) - 5,  static_cast<int>(m_input->GetMousePosition().GetY()) - 5, 10, 10 };
            if((*it)->IsCollidingWithRect(mouseRect))
            {
                ent = (*it);
            }
        }

        IssueCommand(ent);
    }

    // Update entities
    for(std::list<Entity*>::const_iterator it = m_entities.begin(); it != m_entities.end(); it++)
    {
        (*it)->Update();
    }
}

void Game::Render()
{
    m_renderer->SetDrawColor(SDL_Color{ 255, 255, 255, 255 });
    m_renderer->Clear();

    // Render entities
    for(std::list<Entity*>::const_iterator it = m_entities.begin(); it != m_entities.end(); it++)
    {
        (*it)->Render();
    }

    // Render GUI
    for(std::list<Peon*>::const_iterator it = m_selectedPeons.begin(); it != m_selectedPeons.end(); it++)
    {
        //SDL_Rect outlineRect = { static_cast<int>((*it)->GetPosition().GetX()), static_cast<int>((*it)->GetPosition().GetY()), 32, 32};
        //RenderRect(outlineRect);

        RenderTexture("selection", static_cast<int>((*it)->GetPosition().GetX()), static_cast<int>((*it)->GetPosition().GetY()), 32, 32);
    }

    if(m_input->IsBoxSelecting())
    {
        SDL_Rect selectionRect = m_input->GetBoxSelection();
        RenderRect(selectionRect);
    }

    // Debug stuff
    std::stringstream ss;
    ss << "Peons: " << m_peonCount;
    RenderText("dos", 10, 10, ss.str());
    ss.str(" ");

    m_renderer->Present();
}

/*
    Delete all entities that have been marked for deletion in the previous frame.
*/
void Game::CleanEntities()
{
    for(std::list<Entity*>::const_iterator it = m_entities.begin(); it != m_entities.end(); it++)
    {
        if((*it)->IsDeleted())
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
    for(std::list<Peon*>::const_iterator it = m_selectedPeons.begin(); it != m_selectedPeons.end(); it++)
    {
        Peon* peon = (*it);

        if(ent != nullptr)
        {
            // If we commanded them to a resource, they will begin working on that resource
            Resource* resource = dynamic_cast<Resource*>(ent);
            if(resource != nullptr)
            {
                peon->ClearActions();
                peon->PushAction(std::make_unique<GatherAction>(peon, resource));
            }
        }
        else
        {
            // If we commanded them to empty space, they will just walk to the clicked position
            peon->ClearActions();
            peon->PushAction(std::make_unique<MoveAction>(peon, m_input->GetMousePosition()));
        }
    }
}

void Game::AddResources(const int& resources)
{
    m_resources += resources;
}

/*
    Search for a Stockpile.
    TODO: Refactor this into a template of some sort?
*/
Stockpile* Game::FindStockpile()
{
    for (std::list<Entity*>::const_iterator it = m_entities.begin(); it != m_entities.end(); it++)
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
    SDL_Surface* tempSurface = IMG_Load(path.c_str());
    if (tempSurface == nullptr)
    {
        std::cerr << "Unable to load image " << path << "! SDL_image error: " << IMG_GetError() << std::endl;
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer->GetSDLRenderer(), tempSurface);
    SDL_FreeSurface(tempSurface);
    if (texture == nullptr)
    {
        std::cerr << "Unable to create texture from " << path << "! SDL error: " << SDL_GetError() << std::endl;
        return false;
    }

    std::cout << "Texture " << id << " loaded." << std::endl;
    m_textureMap[id] = texture;
    return true;
}

bool Game::LoadFont(const std::string& path, const std::string& id, const int& size)
{
    TTF_Font* font = TTF_OpenFont(path.c_str(), size);
    if (font == nullptr)
    {
        std::cerr << "Failed to load font! SDL_ttf error: " << TTF_GetError() << std::endl;
    }

    std::cout << "Font " << id << " loaded." << std::endl;
    m_fontMap[id] = font;
    return true;
}

bool Game::LoadSound(const std::string& path, const std::string& id)
{
    Mix_Chunk* sound = Mix_LoadWAV(path.c_str());
    if (sound == nullptr)
    {
        std::cerr << "Failed to load WAV from " << path << "! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }

    std::cout << "Sound " << id << " loaded." << std::endl;
    m_soundMap[id] = sound;
    return true;
}

void Game::RenderTexture(const std::string& id, const int& x, const int& y, const int& width, const int& height)
{
    SDL_Rect srcRect = { 0, 0, 32, 32 };
    SDL_Rect destRect = { x, y, width, height };

    SDL_RenderCopyEx(m_renderer->GetSDLRenderer(), m_textureMap[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}

void Game::RenderSprite(const std::string& id, const int& col, const int& row, const int& x, const int& y, const int& width, const int& height)
{
    SDL_Rect srcRect = { col * width, row * height, width, height };
    SDL_Rect destRect = { x, y, width, height };

    SDL_RenderCopyEx(m_renderer->GetSDLRenderer(), m_textureMap[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}

void Game::RenderText(const std::string& fontID, const int& x, const int& y, const std::string& text, const SDL_Color& color)
{
    SDL_Surface* surface = TTF_RenderText_Solid(m_fontMap[fontID], text.c_str(), color);
    if (surface == nullptr)
    {
        std::cerr << "Failed to render font to surface! SDL_ttf error: " << TTF_GetError() << std::endl;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer->GetSDLRenderer(), surface);
    int width;
    int height;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    if (texture == nullptr)
    {
        std::cout << "Failed to create texture from surface! SDL error: " << SDL_GetError() << std::endl;
    }

    SDL_Rect srcRect = { 0, 0, width, height };
    SDL_Rect destRect = { x, y, width, height };

    SDL_RenderCopyEx(m_renderer->GetSDLRenderer(), texture, &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void Game::RenderRect(const SDL_Rect& rect, const SDL_Color& color)
{
    m_renderer->SetDrawColor(SDL_Color{ 0, 0, 0, 255 });
    SDL_RenderDrawRect(m_renderer->GetSDLRenderer(), &rect);
}

void Game::PlaySound(const std::string& id)
{
    Mix_PlayChannel(-1, m_soundMap[id], 0);
}
