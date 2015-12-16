#include "PCH.hpp"
#include "Game.hpp"
#include "Vector2D.hpp"

Game::Game() :
    m_window(nullptr),
    m_renderer(nullptr),
    m_deltaTime(0.0),
    m_isRunning(true),
    m_resources(0),
    m_peons(0)
{
}

Game::~Game()
{
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
    m_entityManager = std::make_unique<EntityManager>();

    // Load Textures
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

    // Load GameObjects
    m_bonfire = new Bonfire(this, Vector2D(304, 224));
    m_entityManager->RegisterEntity(m_bonfire);

    for (int i = 0; i < 6; i++)
    {
        Vector2D pos = Vector2D(rand() % (640 - 100), rand() % (480 - 100));
        while (Vector2D::Distance(pos, m_bonfire->GetPosition()) < 100)
        {
            pos = Vector2D(rand() % (640 - 100), rand() % (480 - 100));
        }
        Tree* t = new Tree(this, pos);
        m_entityManager->RegisterEntity(t);
    }

    for (int i = 0; i < 3; i++)
    {
        Vector2D pos = Vector2D(rand() % (640 - 100), rand() % (480 - 100));
        while (Vector2D::Distance(pos, m_bonfire->GetPosition()) < 100)
        {
            pos = Vector2D(rand() % (640 - 100), rand() % (480 - 100));
        }

        Stone* s = new Stone(this, pos);
        m_entityManager->RegisterEntity(s);
    }

    SpawnPeons(true);

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
    if (m_input->GetMouseButtonPress(SDL_BUTTON_LEFT))
    {
        LeftClick();
    }
    else if (m_input->GetMouseButtonPress(SDL_BUTTON_RIGHT))
    {
        RightClick();
    }

    if (m_input->GetMouseButtonRelease(SDL_BUTTON_LEFT))
    {
        LeftClickUp();
    }
    else if (m_input->GetMouseButtonRelease(SDL_BUTTON_RIGHT))
    {
        RightClickUp();
    }

    if (m_input->GetMouseButton(SDL_BUTTON_LEFT))
    {
        if (!m_selecting)
        {
            m_selecting = true;

            m_selectionRect.x = m_input->GetMousePosition().GetX();
            m_selectionRect.y = m_input->GetMousePosition().GetY();
        }

        if (m_selecting)
        {
            m_selectionRect.w = m_input->GetMousePosition().GetX() - m_selectionRect.x;
            m_selectionRect.h = m_input->GetMousePosition().GetY() - m_selectionRect.y;
        }
    }

    SpawnPeons(false);
    
    m_entityManager->Update();
}

void Game::Render()
{
    m_renderer->SetDrawColor(SDL_Color{ 255, 255, 255, 255 });
    m_renderer->Clear();

    for (int x = 0; x < (640 / 32); x++)
    {
        for (int y = 0; y < (480 / 32); y++)
        {
            RenderTexture("grass", x * 32, y * 32, 32, 32);
        }
    }

    m_entityManager->Render();

    for (std::vector<Peon*>::const_iterator it = m_selectedPeons.begin(); it != m_selectedPeons.end(); it++)
    {
        RenderTexture("selection", (*it)->GetPosition().GetX(), (*it)->GetPosition().GetY(), 32, 32);
    }

    if (m_selecting)
    {
        m_renderer->SetDrawColor(SDL_Color{ 0, 0, 0, 255 });
        SDL_RenderDrawRect(m_renderer->GetSDLRenderer(), &m_selectionRect);
    }

    // Draw GUI
    sstream.str("");
    sstream << m_resources;
    RenderTexture("log", -4, 40, 32, 32);
    RenderTexture("rock", 2, 45, 32, 32);
    RenderText("dos", 10, 75, sstream.str());

    sstream.str("");
    sstream << m_peons;
    RenderTexture("man", 0 - 16, 0 - 32, 64, 64);
    RenderText("dos", 8, 32, sstream.str());

    SDL_Rect srcRect = { 0, 0, 32, 32 };
    SDL_Rect destRect = { 256, 256, 16, 16 };
    SDL_RenderCopyEx(m_renderer->GetSDLRenderer(), m_textureMap["test"], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);

    m_renderer->Present();
}

void Game::LeftClick()
{
    m_selectedPeons.clear();
}

void Game::LeftClickUp()
{
    if (m_selecting)
    {
        std::vector<Peon*> peons = m_entityManager->GetEntitiesOfType<Peon>();
        for (std::vector<Peon*>::const_iterator it = peons.begin(); it != peons.end(); it++)
        {
            if (CheckCollision(m_selectionRect, (*it)->GetHitbox()))
            {
                m_selectedPeons.push_back(*it);
            }
        }

        m_selecting = false;
    }
}

void Game::RightClick()
{
    Entity* ent = nullptr;
    std::vector<Tree*> resources = m_entityManager->GetEntitiesOfType<Tree>();
    for (Tree* t : resources)
    {
        SDL_Rect mouseRect = { m_input->GetMousePosition().GetX() - 5, m_input->GetMousePosition().GetY() - 5, 10, 10 };
        if (CheckCollision(mouseRect, t->GetHitbox()))
        {
            ent = t;
        }
    }

    CommandPeons(ent);
    
}

void Game::RightClickUp()
{

}

bool Game::CheckCollision(SDL_Rect a, SDL_Rect b)
{
    int leftA = a.x;
    int rightA = a.x + a.w;
    int topA = a.y;
    int bottomA = a.y + a.h;

    int leftB = b.x;
    int rightB = b.x + b.w;
    int topB = b.y;
    int bottomB = b.y + b.h;

    if (rightA < leftA)
    {
        int temp = leftA;
        leftA = rightA;
        rightA = temp;
    }

    if (rightB < leftB)
    {
        int temp = leftB;
        leftB = rightB;
        rightB = temp;
    }

    if (bottomA < topA)
    {
        int temp = topA;
        topA = bottomA;
        bottomA = temp;
    }

    if (bottomB < topB)
    {
        int temp = topB;
        topB = bottomB;
        bottomB = temp;
    }


    if (rightA > leftB && leftA < rightB)
    {
        if (bottomA > topB && topA < bottomB)
        {
            return true;
        }
    }

    return false;
}

Bonfire* Game::FindBonfire(Peon* peon)
{
    return m_bonfire;
}

Tree* Game::FindTree(Peon* peon)
{
    Tree* tree = nullptr;
    return tree;
}

void Game::SpawnPeons(bool initial)
{
    for (int i = 0; i < m_peonsToSpawn; i++)
    {
        Peon* peon;
        Vector2D position(rand() % 640, -(rand() % 100));
        Vector2D dest(rand() % (640 - 100), rand() % (480 - 100));
        int width = 32;
        int height = 32;

        if (!initial)
        {
            peon = new Peon(this, position);
            peon->dest = dest;
            peon->m_state = Peon::WALKING;
        }
        else
        {
            peon = new Peon(this, dest);
            peon->m_state = Peon::IDLE;
        }

        m_entityManager->RegisterEntity(peon);
        m_peons++;
    }

    m_peonsToSpawn = 0;
}

void Game::SacrificePeon(Peon* peon)
{
    if (m_resources >= 100)
    {
        PlaySound("die");

        // Recycle this peon
        peon->Respawn();

        // Spawn a second one
        m_peonsToSpawn++;

        m_resources -= 100;
    }
    else
    {
        peon->m_state = Peon::IDLE;
    }

    m_selectedPeons.clear();
}

void Game::CommandPeons(Entity* target)
{
    for (std::vector<Peon*>::const_iterator it = m_selectedPeons.begin(); it != m_selectedPeons.end(); it++)
    {
        (*it)->m_isWandering = false;
        if (target == nullptr)
        {
            (*it)->dest = Vector2D(m_input->GetMousePosition().GetX() - 16, m_input->GetMousePosition().GetY() - 16);
            (*it)->m_targetResource = nullptr;
            (*it)->m_state = Peon::WALKING;
        }
        else
        {
            if ((*it)->m_targetResource != target)
            {
                (*it)->m_state = Peon::IDLE;
                (*it)->m_targetResource = target;
            }

            /*
            if (target->m_ID == "bonfire")
            {
                (*it)->m_state = Peon::SACRIFICE;
            }
            */
        }

    }
}

void Game::DepositResources(int amount)
{
    m_resources += amount;
}

int Game::GetResources() const
{
    return m_resources;
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

void Game::RenderTexture(const std::string& id, const int& x, const int& y, const int& width, const int& height)
{
    SDL_Rect srcRect = { 0, 0, 32, 32 };
    SDL_Rect destRect = { x, y, width, height };

    SDL_RenderCopyEx(m_renderer->GetSDLRenderer(), m_textureMap[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}

bool Game::LoadFont(const std::string& path, const std::string& id)
{
    TTF_Font* font = TTF_OpenFont(path.c_str(), 16);
    if (font == nullptr)
    {
        std::cerr << "Failed to load font! SDL_ttf error: " << TTF_GetError() << std::endl;
    }

    std::cout << "Font " << id << " loaded." << std::endl;
    m_fontMap[id] = font;
    return true;
}

void Game::RenderText(const std::string& fontID, const int& x, const int& y, const std::string& text, SDL_Color color)
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

void Game::PlaySound(const std::string& id)
{
    Mix_PlayChannel(-1, m_soundMap[id], 0);
}
