/*
    Game.cpp
    Game

    Declan Hopkins
    8/31/2016
*/

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
    m_engine(this),
    m_bgMusic(nullptr),
    m_frameRateWidget(nullptr),
    m_peonCountWidget(nullptr),
    m_woodCountWidget(nullptr),
    m_faithCountWidget(nullptr),
    m_basicPeonLabel(nullptr)
{
}

Game::~Game()
{
}

grim::graphics::Camera* Game::GetMainCamera()
{
    return m_mainCamera.get();
}

World* Game::GetWorld()
{
    return m_map.get();
}

bool Game::Initialize()
{
    /*
        Initialize Engine
    */

    if (!m_engine.Initialize())
    {
        grim::utility::Debug::LogError("Engine initialization failed.");
        return false;
    }

    /*
        Load Textures
    */

    grim::utility::Debug::Log("Loading textures...");
    LoadTexture("Resources/Textures/peon.png", "peon");
    LoadTexture("Resources/Textures/item.png", "item");
    LoadTexture("Resources/Textures/orc.png", "orc");
    LoadTexture("Resources/Textures/resource.png", "resource");
    LoadTexture("Resources/Textures/terrain.png", "terrain", true, GL_CLAMP_TO_EDGE, GL_NEAREST);
    LoadTexture("Resources/Textures/structure.png", "structure");
    LoadTexture("Resources/Textures/obelisk.png", "obelisk");
    LoadTexture("Resources/Textures/doosk.png", "doosk");
    LoadTexture("Resources/Textures/puppy.png", "puppy");
    LoadTexture("Resources/Textures/kitten.png", "kitten");
    LoadTexture("Resources/Textures/grass.png", "grass");
    LoadTexture("Resources/Textures/tree.png", "tree");
    LoadTexture("Resources/Textures/gandalf.png", "gandalf");
    LoadTexture("Resources/Textures/spider.png", "spider", false, GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR);
    LoadTexture("Resources/Textures/spellbook.png", "spellbook", false, GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR);
    LoadTexture("Resources/Textures/button.png", "button", false, GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR);
    LoadTexture("Resources/Textures/header.png", "header", false, GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR);
    LoadTexture("Resources/Textures/beam.png", "beam", false, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR);

    /*
        Load Fonts
    */

    grim::utility::Debug::Log("Loading fonts...");
    LoadFont("Resources/Fonts/dos.ttf", "dos");
    LoadFont("Resources/Fonts/hack.ttf", "hack");
    LoadFont("Resources/Fonts/black_family.ttf", "black_family", 22);
    LoadFont("Resources/Fonts/black_family_incised.ttf", "black_family_incised", 32);

    /*
        Load Sounds
    */

    grim::utility::Debug::Log("Loading sounds...");
    m_engine.GetAudio()->LoadSound("Resources/Sounds/select_00.wav", "select_00");
    m_engine.GetAudio()->LoadSound("Resources/Sounds/select_01.wav", "select_01");
    m_engine.GetAudio()->LoadSound("Resources/Sounds/woodcutting_00.wav", "woodcutting_00");
    m_engine.GetAudio()->LoadSound("Resources/Sounds/mining_00.wav", "mining_00");
    m_engine.GetAudio()->LoadSound("Resources/Sounds/mining_01.wav", "mining_01");
    m_engine.GetAudio()->LoadSound("Resources/Sounds/mining_02.wav", "mining_02");
    m_engine.GetAudio()->LoadSound("Resources/Sounds/drop_00.wav", "drop_00");
    m_engine.GetAudio()->LoadSound("Resources/Sounds/drop_01.wav", "drop_01");
    m_engine.GetAudio()->LoadSound("Resources/Sounds/death_00.wav", "death_00");
    m_engine.GetAudio()->LoadSound("Resources/Sounds/punch_00.wav", "punch_00");
    m_engine.GetAudio()->LoadSound("Resources/Sounds/sacrifice_00.wav", "sacrifice_00");
    m_engine.GetAudio()->LoadSound("Resources/Sounds/sacrifice_01.wav", "sacrifice_01");
    m_engine.GetAudio()->LoadSound("Resources/Sounds/sacrifice_02.wav", "sacrifice_02");
    m_engine.GetAudio()->LoadSound("Resources/Sounds/sacrifice_03.wav", "sacrifice_03");
    m_engine.GetAudio()->LoadSound("Resources/Sounds/sacrifice_04.wav", "sacrifice_04");
    m_engine.GetAudio()->LoadSound("Resources/Sounds/damage.wav", "damage");
    m_engine.GetAudio()->LoadSound("Resources/Sounds/sword.wav", "sword");
    m_engine.GetAudio()->LoadSound("Resources/Sounds/book_open_00.wav", "book_open_00");
    m_engine.GetAudio()->LoadSound("Resources/Sounds/book_close_00.wav", "book_close_00");
    m_engine.GetAudio()->LoadSound("Resources/Sounds/spell_summon_00.wav", "spell_summon_00");
    m_engine.GetAudio()->LoadSound("Resources/Sounds/error_00.wav", "error_00");

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
        Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
        //Mix_PlayMusic(m_bgMusic, -1);
    }

    /*
        Load Shaders
    */

    // TODO REFACTOR THIS
    grim::utility::Debug::Log("Loading shaders...");
    LoadShader("Resources/Shaders/vertex.glsl", GL_VERTEX_SHADER, "vertex_textured");
    LoadShader("Resources/Shaders/fragment.glsl", GL_FRAGMENT_SHADER, "fragment_textured");
    CreateShaderProgram("vertex_textured", "fragment_textured", "basic_shader");
    m_shaderMap["vertex_textured"] = nullptr;
    m_shaderMap["fragment_textured"] = nullptr;

    LoadShader("Resources/Shaders/flat_vertex.glsl", GL_VERTEX_SHADER, "flat_vertex");
    LoadShader("Resources/Shaders/flat_fragment.glsl", GL_FRAGMENT_SHADER, "flat_fragment");
    CreateShaderProgram("flat_vertex", "flat_fragment", "shader_flat");
    m_shaderMap["flat_vertex"] = nullptr;
    m_shaderMap["flat_fragment"] = nullptr;

    /*
        Create ShaderPrograms
    */

    grim::utility::Debug::Log("Creating shader programs...");
    //CreateShaderProgram("vertex_textured", "fragment_textured", "basic_shader");

    /*
        Create Materials
    */

    grim::utility::Debug::Log("Creating materials...");
    CreateMaterial("sprite_terrain", GetTexture("terrain"), GetShaderProgram("basic_shader"));
    CreateMaterial("sprite_resource", GetTexture("resource"), GetShaderProgram("basic_shader"));
    CreateMaterial("sprite_peon", GetTexture("peon"), GetShaderProgram("basic_shader"));
    CreateMaterial("sprite_obelisk", GetTexture("obelisk"), GetShaderProgram("basic_shader"));
    CreateMaterial("sprite_spider_queen", GetTexture("spider"), GetShaderProgram("basic_shader"));
    CreateMaterial("sprite_item", GetTexture("item"), GetShaderProgram("basic_shader"));
    CreateMaterial("effect_beam", GetTexture("beam"), GetShaderProgram("basic_shader"));
    CreateMaterial("flat_black", GetTexture("beam"), GetShaderProgram("shader_flat"));
    CreateMaterial("sprite_ui_header", GetTexture("header"), GetShaderProgram("basic_shader"));
    CreateMaterial("sprite_ui_spellbook", GetTexture("spellbook"), GetShaderProgram("basic_shader"));
    CreateMaterial("effect_beam", GetTexture("beam"), GetShaderProgram("basic_shader"));

    GetMaterial("effect_beam")->color.a = 0.75f;

    // Sprites
    m_spriteMap[EntityID::STRUCTURE_STOCKPILE] = nullptr;
    m_spriteMap[EntityID::MONSTER_SPIDER_QUEEN] = nullptr;
    m_spriteMap[EntityID::PEON] = std::make_unique<grim::graphics::Sprite>(GetMaterial("sprite_peon"), 32, 32, 0);
    m_spriteMap[EntityID::EFFECT_BEAM] = std::make_unique<grim::graphics::Sprite>(GetMaterial("effect_beam"));

    // Setup the game
    m_mainCamera = std::make_unique<grim::graphics::Camera>(&m_engine, WINDOW_WIDTH, WINDOW_HEIGHT, -1.0f, 1.0f);
    m_uiCamera = std::make_unique<grim::graphics::Camera>(&m_engine, WINDOW_WIDTH, WINDOW_HEIGHT, -1.0f, 1.0f);
    m_map = std::make_unique<World>(this);
    m_player = std::make_unique<Player>(this);

    m_mainCamera->SetCenter(m_map->GetCenter());

    m_engine.GetRenderer()->SetLayerCamera(0, m_mainCamera.get());
    m_engine.GetRenderer()->SetLayerCamera(1, m_uiCamera.get());

    m_map->Generate();

    grim::graphics::Material textMaterial(nullptr, GetShaderProgram("basic_shader"));

    m_frameRateWidget = new grim::ui::TextView(&m_engine, "FPS: 55", GetFont("hack"), textMaterial);
    m_frameRateWidget->SetPosition(glm::vec2(5.0f, 5.0f));
    m_engine.GetUI()->RegisterWidget(m_frameRateWidget);

    m_headerSprite = std::make_unique<grim::graphics::Sprite>(GetMaterial("sprite_ui_header"));
    m_header = new grim::ui::SpriteView(&m_engine, m_headerSprite.get());
    m_header->SetPosition(glm::vec2(WINDOW_WIDTH / 2.0f, 40.0f));
    m_header->SetScale(glm::vec2(1.3f, 1.3f));
    m_header->SetZLayer(0.8f);
    m_engine.GetUI()->RegisterWidget(m_header);

    m_dateWidget = new grim::ui::TextView(&m_engine, " ", GetFont("hack"), textMaterial);
    m_dateWidget->SetPosition(glm::vec2((WINDOW_WIDTH / 2.0f) - 85.0f, 5.0f));
    m_engine.GetUI()->RegisterWidget(m_dateWidget);

    m_peonCountWidget = new grim::ui::TextView(&m_engine, " ", GetFont("hack"), textMaterial);
    m_peonCountWidget->SetPosition(glm::vec2(5.0f, 5.0f + 20.0f));
    m_engine.GetUI()->RegisterWidget(m_peonCountWidget);

    m_woodCountWidget = new grim::ui::TextView(&m_engine, " ", GetFont("hack"), textMaterial);
    m_woodCountWidget->SetPosition(glm::vec2(5.0f, 5.0f + 40.0f));
    m_engine.GetUI()->RegisterWidget(m_woodCountWidget);

    m_faithCountWidget = new grim::ui::TextView(&m_engine, " ", GetFont("hack"), textMaterial);
    m_faithCountWidget->SetPosition(glm::vec2(5.0f, 5.0f + 60.0f));
    m_engine.GetUI()->RegisterWidget(m_faithCountWidget);

    m_spellBookSprite = std::make_unique<grim::graphics::Sprite>(GetMaterial("sprite_ui_spellbook"));
    m_spellbook = new grim::ui::SpriteView(&m_engine, m_spellBookSprite.get());
    m_spellbook->SetPosition(glm::vec2(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f + 260.0f));
    m_spellbook->SetScale(glm::vec2(1.5f, 1.5f));
    m_spellbook->SetVisible(false);
    m_spellbook->SetZLayer(0.8f);
    m_engine.GetUI()->RegisterWidget(m_spellbook);

    m_basicPeonLabel = new grim::ui::TextView(&m_engine, "Peon", GetFont("black_family"), textMaterial);
    m_basicPeonLabel->SetPosition(glm::vec2(-240.0f, -140.0f));
    m_spellbook->RegisterWidget(m_basicPeonLabel);

    m_buttonSprite = std::make_unique<grim::graphics::Sprite>(GetMaterial("sprite_terrain"));

    m_peonButton = new grim::ui::ButtonView(&m_engine, GetEntitySprite(EntityID::PEON));
    m_peonButton->SetPosition(glm::vec2(-220.0f, -110.0f));
    m_peonButton->SetScale(glm::vec2(1.5f, 1.5f));
    m_peonButton->SetZLayer(0.9f);
    m_spellbook->RegisterWidget(m_peonButton);

    m_peonButton->SetOnClick([this]()
    {
        GetPlayer()->GetPlacement()->SetHeldEntity(EntityID::PEON);
        m_engine.GetAudio()->PlaySound("select_00");
    });

    return true;
}

void Game::Run()
{
    m_engine.Run();
}

void Game::Terminate()
{
    // TODO move this SDL stuff to the Engine
    // THIS IS ALL LEGACY AHHHHH
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

    m_engine.Terminate();
}

void Game::Update()
{
    /*
        Update Modules
    */

    m_engine.GetUI()->Update(0.016f);

    glm::vec2 mousePos = m_mainCamera->ConvertToWorld(m_engine.GetInput()->GetMousePosition());

    if (m_engine.GetInput()->GetKeyPress(SDLK_ESCAPE))
    {
        Terminate();
    }

    if (m_engine.GetInput()->GetKeyPress(SDLK_m))
    {
        Mix_PlayMusic(m_bgMusic, -1);
    }

    if (m_engine.GetInput()->GetKeyPress(SDLK_q))
    {
        m_spellbook->SetVisible(true);
        m_basicPeonLabel->SetVisible(true);
        m_engine.GetAudio()->PlaySound("book_open_00");
    }
    else if (m_engine.GetInput()->GetKeyRelease(SDLK_q))
    {
        m_spellbook->SetVisible(false);
        m_basicPeonLabel->SetVisible(false);
        m_engine.GetAudio()->PlaySound("book_close_00");
    }

    m_map->Update(0.016f);
    m_player->Update(0.016f);

    m_frameRateWidget->SetText("FPS: " + std::to_string(m_engine.m_frameRate));
    m_dateWidget->SetText(std::to_string(m_map->GetDay()) + " " + m_map->GetMonth() + ", Year " + std::to_string(m_map->GetYear()));
    m_peonCountWidget->SetText("Peons: " + std::to_string(m_player->GetPeonCount()));
    m_woodCountWidget->SetText("Wood: " + std::to_string(m_player->GetInventory()->CountItem(ItemType::WOOD)));
    m_woodCountWidget->SetText("Faith: " + std::to_string(m_player->GetFaith()));
}

void Game::Render()
{
    m_map->Render();
    m_player->Render();

    /*
        Render Services
    */

    if (!m_engine.GetInput()->GetKey(SDLK_SPACE))
    {
        m_engine.GetUI()->Render();
    }
}

bool Game::LoadTexture(const std::string& path, const std::string& ID, const bool& isOpaque, const GLenum& wrapMode, const GLenum& scaleMode)
{
    m_textureMap[ID] = std::make_unique<grim::graphics::Texture>(isOpaque, wrapMode, scaleMode);
    m_textureMap[ID]->LoadFromFile(path);
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
    m_shaderProgramMap[ID] = std::make_unique<grim::graphics::ShaderProgram>(&m_engine, GetShader(vertexShaderID), GetShader(fragmentShaderID));
    return true;
}

bool Game::CreateMaterial(const std::string& ID, grim::graphics::Texture* const texture, grim::graphics::ShaderProgram* const shaderProgram)
{
    m_materialMap[ID] = std::make_unique<grim::graphics::Material>(texture, shaderProgram);
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

grim::graphics::Material* Game::GetMaterial(const std::string& ID)
{
    return m_materialMap[ID].get();
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

grim::Engine* const Game::GetEngine()
{
    return &m_engine;
}
