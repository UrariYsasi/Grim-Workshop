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
    m_bgMusic(nullptr)
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
        LOG_ERROR() << "Engine initialization failed.";
        return false;
    }

    /*
        Load Textures
    */

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

    LoadFont("Resources/Fonts/dos.ttf", "dos");
    LoadFont("Resources/Fonts/hack.ttf", "hack");
    LoadFont("Resources/Fonts/black_family.ttf", "black_family", 22);
    LoadFont("Resources/Fonts/black_family_incised.ttf", "black_family_incised", 32);

    /*
        Load Sounds
    */

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

    /*
    //grim::utility::Debug::Log("Loading music...");
    if (//grim::utility::Debug::IsFlagEnabled(grim::utility::MIX_AUDIO))
    {
        m_bgMusic = Mix_LoadMUS("Resources/Music/jand_bg.mp3");
        if (!m_bgMusic)
        {
            //grim::utility::Debug::LogError("Music could not be loaded. SDL_mixer error: %s", Mix_GetError());
        }

        // Start music
        Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
        //Mix_PlayMusic(m_bgMusic, -1);
    }
    */

    /*
        Load Shaders
    */

    // TODO REFACTOR THIS
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

    //CreateShaderProgram("vertex_textured", "fragment_textured", "basic_shader");

    /*
        Create Materials
    */

    CreateMaterial("sprite_terrain", m_engine.GetAssetModule()->FindTexture("terrain"), GetShaderProgram("basic_shader"));

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
    //m_spriteMap[EntityID::PEON] = std::make_unique<grim::graphics::Sprite>(GetMaterial("sprite_peon"), 32, 32, 0);
    //m_spriteMap[EntityID::EFFECT_BEAM] = std::make_unique<grim::graphics::Sprite>(GetMaterial("effect_beam"));

    // Setup the game
    m_mainCamera = std::make_unique<grim::graphics::Camera>(&m_engine, WINDOW_WIDTH, WINDOW_HEIGHT, -1.0f, 1.0f);
    m_map = std::make_unique<World>(this);
    m_player = std::make_unique<Player>(this);

    m_mainCamera->SetCenter(m_map->GetCenter());

    m_engine.GetRenderer()->SetLayerCamera(0, m_mainCamera.get());

    //m_map->Generate();

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
    m_mainCamera.reset();

    m_engine.Terminate();
}

void Game::Update()
{
    m_map->Update(0.016f);
    //m_player->Update(0.016f);
}

void Game::Render()
{
    m_map->Render();
    //m_player->Render();
}

bool Game::LoadTexture(const std::string& path, const std::string& ID, const bool& isOpaque, const GLenum& wrapMode, const GLenum& scaleMode)
{
    //m_textureMap[ID] = std::make_unique<grim::assets::Texture>(isOpaque, wrapMode, scaleMode);
    //m_textureMap[ID]->LoadFromFile(path);
    return true;
}

bool Game::LoadFont(const std::string& path, const std::string& id, const int& size)
{
    TTF_Font* font = TTF_OpenFont(path.c_str(), size);
    if (font == nullptr)
    {
        LOG_ERROR() << "Failed to load font";
        ////grim::utility::Debug::LogError("Failed to load font %s! SDL_ttf error: %s", path.c_str(), TTF_GetError());
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

bool Game::CreateMaterial(const std::string& ID, grim::assets::Texture* const texture, grim::graphics::ShaderProgram* const shaderProgram)
{
    m_materialMap[ID] = std::make_unique<grim::assets::Material>(texture, shaderProgram);
    return true;
}

grim::assets::Texture* Game::GetTexture(const std::string& ID)
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

grim::assets::Material* Game::GetMaterial(const std::string& ID)
{
    return m_materialMap[ID].get();
}

std::string Game::ReadFile(const std::string& path)
{
    std::ifstream input(path);
    if (!input.is_open())
    {
        LOG_ERROR() << "Failed to open file";
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
