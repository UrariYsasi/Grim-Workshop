#include "PCH.hpp"
#include "Game.hpp"
#include "Entity/Peon.hpp"
#include "Entity/Tree.hpp"
#include "Entity/Rock.hpp"
#include "Entity/Stockpile.hpp"
#include "Entity/Forge.hpp"
#include "Entity/Action/MoveAction.hpp"
#include "Entity/Action/GatherAction.hpp"
#include "Entity/Action/SmeltAction.hpp"
#include "Terrain/TerrainTile.hpp"
#include "World/World.hpp"
#include "Player.hpp"

Game::Game() :
    Engine(),
    m_bgMusic(nullptr),
    m_frameRateWidget(nullptr),
    m_peonCountWidget(nullptr),
    m_woodCountWidget(nullptr),
    m_faithCountWidget(nullptr)
{
}

Game::~Game()
{
    Mix_FreeMusic(m_bgMusic);

    for (auto fontIt = m_fontMap.begin(); fontIt != m_fontMap.end(); fontIt++)
    {
        TTF_CloseFont(fontIt->second);
    }

    m_fontMap.clear();
    m_textureMap.clear();
    m_shaderMap.clear();
    m_shaderProgramMap.clear();

    m_player.reset();
    m_map.reset();
    m_uiCamera.reset();
    m_mainCamera.reset();
}

grim::graphics::Camera* Game::GetMainCamera()
{
    return m_mainCamera.get();
}

World* Game::GetWorld()
{
    return m_map.get();
}

uint8_t Game::Initialize()
{
    /*
        Initialize Engine
    */

    if (Engine::Initialize() != SUCCESS)
    {
        grim::utility::Debug::LogError("Engine initialization failed.");
        return FAILURE;
    }

    /*
        Load Textures
    */

    grim::utility::Debug::Log("Loading textures...");
    LoadTexture("Resources/Textures/peon.png", "peon");
    LoadTexture("Resources/Textures/item.png", "item");
    LoadTexture("Resources/Textures/orc.png", "orc");
    LoadTexture("Resources/Textures/resource.png", "resource");
    LoadTexture("Resources/Textures/terrain.png", "terrain");
    LoadTexture("Resources/Textures/structure.png", "structure");
    LoadTexture("Resources/Textures/obelisk.png", "obelisk");
    LoadTexture("Resources/Textures/doosk.png", "doosk");
    LoadTexture("Resources/Textures/puppy.png", "puppy");
    LoadTexture("Resources/Textures/kitten.png", "kitten");
    LoadTexture("Resources/Textures/grass.png", "grass");
    LoadTexture("Resources/Textures/tree.png", "tree");
    LoadTexture("Resources/Textures/gandalf.png", "gandalf");
    LoadTexture("Resources/Textures/spider.png", "spider", GL_LINEAR_MIPMAP_LINEAR);

    /*
        Load Fonts
    */

    grim::utility::Debug::Log("Loading fonts...");
    LoadFont("Resources/Fonts/dos.ttf", "dos");
    LoadFont("Resources/Fonts/hack.ttf", "hack");

    /*
        Load Sounds
    */

    grim::utility::Debug::Log("Loading sounds...");
    GetAudio()->LoadSound("Resources/Sounds/select_00.wav", "select_00");
    GetAudio()->LoadSound("Resources/Sounds/select_01.wav", "select_01");
    GetAudio()->LoadSound("Resources/Sounds/woodcutting_00.wav", "woodcutting_00");
    GetAudio()->LoadSound("Resources/Sounds/mining_00.wav", "mining_00");
    GetAudio()->LoadSound("Resources/Sounds/mining_01.wav", "mining_01");
    GetAudio()->LoadSound("Resources/Sounds/mining_02.wav", "mining_02");
    GetAudio()->LoadSound("Resources/Sounds/drop_00.wav", "drop_00");
    GetAudio()->LoadSound("Resources/Sounds/drop_01.wav", "drop_01");
    GetAudio()->LoadSound("Resources/Sounds/death_00.wav", "death_00");
    GetAudio()->LoadSound("Resources/Sounds/punch_00.wav", "punch_00");
    GetAudio()->LoadSound("Resources/Sounds/sacrifice_00.wav", "sacrifice_00");
    GetAudio()->LoadSound("Resources/Sounds/sacrifice_01.wav", "sacrifice_01");
    GetAudio()->LoadSound("Resources/Sounds/sacrifice_02.wav", "sacrifice_02");
    GetAudio()->LoadSound("Resources/Sounds/sacrifice_03.wav", "sacrifice_03");
    GetAudio()->LoadSound("Resources/Sounds/sacrifice_04.wav", "sacrifice_04");
    GetAudio()->LoadSound("Resources/Sounds/damage.wav", "damage");
    GetAudio()->LoadSound("Resources/Sounds/sword.wav", "sword");

    /*
        Load Music
    */

    grim::utility::Debug::Log("Loading music...");
    if (grim::utility::Debug::IsFlagEnabled(grim::utility::MIX_AUDIO))
    {
        m_bgMusic = Mix_LoadMUS("Resources/Music/jand_bg.mp3");
        if (!m_bgMusic)
        {
            grim::utility::Debug::LogError("Music could not be loaded. SDL_mixer error: %s", Mix_GetError());
        }

        // Start music
        //Mix_PlayMusic(m_bgMusic, -1);
    }

    /*
        Load Shaders
    */

    grim::utility::Debug::Log("Loading shaders...");
    LoadShader("Resources/Shaders/vertex.glsl", GL_VERTEX_SHADER, "vertex_textured");
    LoadShader("Resources/Shaders/fragment.glsl", GL_FRAGMENT_SHADER, "fragment_textured");

    /*
        Create ShaderPrograms
    */

    grim::utility::Debug::Log("Creating shader programs...");
    CreateShaderProgram("vertex_textured", "fragment_textured", "basic_shader");

    // Sprites
    m_spriteMap[STRUCTURE_STOCKPILE] = std::make_unique<grim::graphics::Sprite>(GetTexture("structure"), GetShaderProgram("basic_shader"), 32, 32, 8);
    m_spriteMap[ENT_MONSTER_SPIDER] = std::make_unique<grim::graphics::Sprite>(GetTexture("spider"), GetShaderProgram("basic_shader"), 512, 512, 0);

    // Setup the game
    m_mainCamera = std::make_unique<grim::graphics::Camera>(GetRenderer(), WINDOW_WIDTH, WINDOW_HEIGHT, -1.0f, 1.0f);
    m_uiCamera = std::make_unique<grim::graphics::Camera>(GetRenderer(), WINDOW_WIDTH, WINDOW_HEIGHT, -1.0f, 1.0f);
    m_map = std::make_unique<World>(this);
    m_player = std::make_unique<Player>(this);

    m_mainCamera->SetCenter(m_map->GetCenter());

    m_map->Generate();

    m_frameRateWidget = new grim::ui::Text(" ", GetFont("hack"), GetShaderProgram("basic_shader"));
    m_frameRateWidget->SetPosition(glm::vec2(5.0f, 5.0f));
    GetUI()->RegisterWidget(m_frameRateWidget);

    m_dateWidget = new grim::ui::Text(" ", GetFont("hack"), GetShaderProgram("basic_shader"));
    m_dateWidget->SetPosition(glm::vec2((WINDOW_WIDTH / 2.0f) - 80.0f, 5.0f));
    GetUI()->RegisterWidget(m_dateWidget);

    m_peonCountWidget = new grim::ui::Text(" ", GetFont("hack"), GetShaderProgram("basic_shader"));
    m_peonCountWidget->SetPosition(glm::vec2(5.0f, 5.0f + 20.0f));
    GetUI()->RegisterWidget(m_peonCountWidget);

    m_woodCountWidget = new grim::ui::Text(" ", GetFont("hack"), GetShaderProgram("basic_shader"));
    m_woodCountWidget->SetPosition(glm::vec2(5.0f, 5.0f + 40.0f));
    GetUI()->RegisterWidget(m_woodCountWidget);

    m_faithCountWidget = new grim::ui::Text(" ", GetFont("hack"), GetShaderProgram("basic_shader"));
    m_faithCountWidget->SetPosition(glm::vec2(5.0f, 5.0f + 60.0f));
    GetUI()->RegisterWidget(m_faithCountWidget);

    return SUCCESS;
}

void Game::Run()
{
    Engine::Run();
}

void Game::Terminate()
{
    Engine::Terminate();
}

void Game::Update(float deltaTime)
{
    glm::vec2 mousePos = m_mainCamera->ConvertToWorld(GetInput()->GetMousePosition());

    if (GetInput()->GetKeyPress(SDLK_ESCAPE))
    {
        Terminate();
    }

    if (GetInput()->GetKeyPress(SDLK_y))
    {
        m_map->SpawnPeon(1, mousePos);
    }

    if (GetInput()->GetKeyPress(SDLK_u))
    {
        m_map->SpawnOrc();
    }

    if (GetInput()->GetKeyPress(SDLK_m))
    {
        Mix_PlayMusic(m_bgMusic, -1);
    }

    m_map->Update(deltaTime);
    m_player->Update(deltaTime);

    m_frameRateWidget->SetText("FPS: " + std::to_string(m_frameRate));
    m_dateWidget->SetText(std::to_string(m_map->GetDay()) + " " + m_map->GetMonth() + ", Year " + std::to_string(m_map->GetYear()));
    m_peonCountWidget->SetText("Peons: " + std::to_string(m_player->GetPeonCount()));
    m_woodCountWidget->SetText("Wood: " + std::to_string(m_player->GetInventory()->CountItem(ItemType::WOOD)));
    m_woodCountWidget->SetText("Faith: " + std::to_string(m_player->GetFaith()));

    /*
        Update Services
    */

    GetUI()->Update(deltaTime);
}

void Game::Render()
{
    GetRenderer()->Clear();

    m_mainCamera->Activate();
    m_map->Render();
    m_player->Render();

    /*
        Render Services
    */

    m_uiCamera->Activate();
    GetUI()->Render();
}

bool Game::LoadTexture(const std::string& path, const std::string& ID, const GLenum& scaleMode)
{
    m_textureMap[ID] = std::make_unique<grim::graphics::Texture>(path, GL_CLAMP_TO_EDGE, scaleMode);
    return true;
}

bool Game::LoadFont(const std::string& path, const std::string& id, const int& size)
{
    TTF_Font* font = TTF_OpenFont(path.c_str(), size);
    if (font == nullptr)
    {
        grim::utility::Debug::LogError("Failed to load font %s! SDL_ttf error: %s", path.c_str(), TTF_GetError());
    }

    m_fontMap[id] = font;
    return true;
}

bool Game::LoadShader(const std::string& path, const GLenum& shaderType, const std::string& ID)
{
    std::string shaderSource = ReadFile(path);

    if (shaderSource != "*FAILURE*")
    {
        m_shaderMap[ID] = std::make_unique<grim::graphics::Shader>(shaderSource, shaderType, ID);
        return true;
    }

    return false;
}

bool Game::CreateShaderProgram(const std::string& vertexShaderID, const std::string& fragmentShaderID, const std::string& ID)
{
    m_shaderProgramMap[ID] = std::make_unique<grim::graphics::ShaderProgram>(GetRenderer(), GetShader(vertexShaderID), GetShader(fragmentShaderID));
    return true;
}

grim::graphics::Texture* Game::GetTexture(const std::string& ID)
{
    return m_textureMap[ID].get();
}

TTF_Font* Game::GetFont(const std::string& id)
{
    return m_fontMap[id];
}

grim::graphics::Shader* Game::GetShader(const std::string& ID)
{
    return m_shaderMap[ID].get();
}

grim::graphics::ShaderProgram* Game::GetShaderProgram(const std::string& ID)
{
    return m_shaderProgramMap[ID].get();
}

std::string Game::ReadFile(const std::string& path)
{
    std::ifstream input(path);
    if (!input.is_open())
    {
        grim::utility::Debug::LogError("Failed to open file %s", path);
        return "*FAILURE*";
    }

    std::ostringstream ss;  
    ss << input.rdbuf();
    
    return ss.str();
}

grim::graphics::Sprite* Game::GetEntitySprite(const EntityID& id)
{
    return m_spriteMap[id].get();
}

Player* Game::GetPlayer()
{
    return m_player.get();
}