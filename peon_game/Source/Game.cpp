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
    m_bgMusic(nullptr)
{
}

Game::~Game()
{
    if (grim::utility::Debug::IsFlagEnabled(grim::utility::MIX_AUDIO))
    {
        Mix_FreeMusic(m_bgMusic);

        for (auto soundIt = m_soundMap.begin(); soundIt != m_soundMap.end(); soundIt++)
        {
            Mix_FreeChunk(soundIt->second);
        }
    }

    for (auto fontIt = m_fontMap.begin(); fontIt != m_fontMap.end(); fontIt++)
    {
        TTF_CloseFont(fontIt->second);
    }

    m_soundMap.clear();
    m_fontMap.clear();
    m_textureMap.clear();
    m_shaderMap.clear();
    m_shaderProgramMap.clear();

    m_player.reset();
    m_map.reset();
    m_uiCamera.reset();
    m_mainCamera.reset();
}

grim::graphics::Renderer* Game::GetRenderer()
{
    return m_renderer.get();
}

grim::ui::Input* Game::GetInput()
{
    return m_input.get();
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
    LoadTexture("peon.png", "peon");
    LoadTexture("item.png", "item");
    LoadTexture("orc.png", "orc");
    LoadTexture("resource.png", "resource");
    LoadTexture("terrain.png", "terrain");
    LoadTexture("structure.png", "structure");
    LoadTexture("obelisk.png", "obelisk");
    LoadTexture("doosk.png", "doosk");
    LoadTexture("puppy.png", "puppy");
    LoadTexture("kitten.png", "kitten");
    LoadTexture("grass.png", "grass");
    LoadTexture("tree.png", "tree");
    LoadTexture("gandalf.png", "gandalf");

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
        Mix_PlayMusic(m_bgMusic, -1);
    }

    /*
        Load Shaders
    */

    grim::utility::Debug::Log("Loading shaders...");
    LoadShader("vertex.glsl", GL_VERTEX_SHADER, "vertex_textured");
    LoadShader("fragment.glsl", GL_FRAGMENT_SHADER, "fragment_textured");

    /*
        Create ShaderPrograms
    */

    grim::utility::Debug::Log("Creating shader programs...");
    CreateShaderProgram("vertex_textured", "fragment_textured", "basic_shader");

    // Sprites
    m_spriteMap[STRUCTURE_STOCKPILE] = std::make_unique<grim::graphics::Sprite>(GetTexture("structure"), GetShaderProgram("basic_shader"), 32, 32, 8);

    // Setup the game
    m_mainCamera = std::make_unique<grim::graphics::Camera>(m_renderer.get());
    m_uiCamera = std::make_unique<grim::graphics::Camera>(m_renderer.get());
    m_map = std::make_unique<World>(this);
    m_player = std::make_unique<Player>(this);

    m_mainCamera->SetCenter(m_map->GetCenter());

    m_map->Generate();

    m_text = new grim::ui::Text(" ", GetFont("hack"), GetShaderProgram("basic_shader"));
    m_ui->RegisterWidget(m_text);

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
    glm::vec2 mousePos = m_mainCamera->ConvertToWorld(m_input->GetMousePosition());

    if (m_input->GetKeyPress(SDLK_ESCAPE))
    {
        Terminate();
    }

    if (m_input->GetKeyPress(SDLK_y))
    {
        m_map->SpawnPeon(1, m_mainCamera->ConvertToWorld(m_input->GetMousePosition()));
    }

    if (m_input->GetKeyPress(SDLK_u))
    {
        m_map->SpawnOrc();
    }

    if (m_input->GetKeyPress(SDLK_m))
    {
        Mix_PlayMusic(m_bgMusic, -1);
    }

    m_map->Update(deltaTime);
    m_player->Update(deltaTime);

    m_text->SetText(std::to_string(m_frameRate));

    /*
        Update Services
    */

    m_ui->Update(deltaTime);
}

void Game::Render()
{
    m_renderer->Clear();

    m_mainCamera->Activate();
    m_map->Render();
    m_player->Render();

    /*
        Render Services
    */

    m_uiCamera->Activate();
    m_ui->Render();
}

bool Game::LoadTexture(const std::string& textureFileName, const std::string& ID)
{
    m_textureMap[ID] = std::make_unique<grim::graphics::Texture>(textureFileName);
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

bool Game::LoadShader(const std::string& shaderFileName, const GLenum& shaderType, const std::string& ID)
{
    std::string shaderSource = ReadFile("Resources/Shaders/" + shaderFileName);

    if (shaderSource != "*FAILURE*")
    {
        m_shaderMap[ID] = std::make_unique<grim::graphics::Shader>(shaderSource, shaderType, ID);
        return true;
    }

    return false;
}

bool Game::CreateShaderProgram(const std::string& vertexShaderID, const std::string& fragmentShaderID, const std::string& ID)
{
    m_shaderProgramMap[ID] = std::make_unique<grim::graphics::ShaderProgram>(m_renderer.get(), GetShader(vertexShaderID), GetShader(fragmentShaderID));
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
    if (!input.is_open()) {
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