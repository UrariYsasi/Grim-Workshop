#include "PCH.hpp"
#include "Game.hpp"
#include "../Engine/Window.hpp"
#include "../Engine/Renderer.hpp"
#include "../Engine/Input.hpp"
#include "../Engine/Camera.hpp"
#include "../Engine/ShaderProgram.hpp"
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
    m_isRunning(false),
    m_frameCount(0),
    m_frameRate(0),
    m_gameStartTime(0),
    m_bgMusic(nullptr)
{
}

Game::~Game()
{
    if (Debug::IsFlagEnabled(MIX_AUDIO))
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

    for (auto texIt = m_textureMap.begin(); texIt != m_textureMap.end(); texIt++)
    {
        SDL_DestroyTexture(texIt->second);
    }

    m_soundMap.clear();
    m_fontMap.clear();
    m_textureMap.clear();

    m_player.reset();
    m_map.reset();
    m_GUICamera.reset();
    m_mainCamera.reset();
    m_input.reset();
    m_renderer.reset();
    m_window.reset();

    TTF_Quit();

    if (Debug::IsFlagEnabled(MIX_AUDIO))
    {
        Mix_CloseAudio(); // Close one audio channel (We only have one...)
        Mix_Quit();
    }

    IMG_Quit();
    SDL_Quit();
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

World* Game::GetWorld()
{
    return m_map.get();
}

int Game::Initialize()
{
    Debug::EnableFlag(LOGGING | CHEAT);

    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        Debug::LogError("SDL could not initialize! SDL error: %s", SDL_GetError());
        return FAILURE;
    }
    
    // Tell SDL we want a forward compatible OpenGL 3.2 Context
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    // Initialize SDL_image
    if (IMG_Init(IMG_INIT_PNG) < 0)
    {
        Debug::LogError("SDL_image could not initialize! SDL_image error: %s", IMG_GetError());
        return FAILURE;
    }

    //Initialize SDL_mixer
    if (Debug::IsFlagEnabled(MIX_AUDIO))
    {
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            Debug::LogError("SDL_mixer could not initialize! SDL_mixer error: %s", Mix_GetError());
            return FAILURE;
        }

        // Set default volume
        Mix_Volume(-1, MIX_MAX_VOLUME);
        Mix_VolumeMusic(MIX_MAX_VOLUME / 3);
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

    m_map = std::make_unique<World>(this);
    m_player = std::make_unique<Player>(this);

    // Load Textures
    Debug::Log("Loading textures...");
    LoadTexture("Resources/Textures/peon.png", "peon");
    LoadTexture("Resources/Textures/orc.png", "orc");
    LoadTexture("Resources/Textures/resource.png", "resource");
    LoadTexture("Resources/Textures/terrain.png", "terrain");
    LoadTexture("Resources/Textures/structure.png", "structure");
    LoadTexture("Resources/Textures/obelisk.png", "obelisk");
    LoadTexture("Resources/Textures/tree.png", "tree");

    // Load fonts
    Debug::Log("Loading fonts...");
    LoadFont("Resources/Fonts/dos.ttf", "dos");

    // Load Sounds
    Debug::Log("Loading sounds...");
    LoadSound("Resources/Sounds/woodcutting_00.wav", "woodcutting_00");
    LoadSound("Resources/Sounds/woodcutting_01.wav", "woodcutting_01");
    LoadSound("Resources/Sounds/woodcutting_02.wav", "woodcutting_02");
    LoadSound("Resources/Sounds/mining_00.wav", "mining_00");
    LoadSound("Resources/Sounds/mining_01.wav", "mining_01");
    LoadSound("Resources/Sounds/mining_02.wav", "mining_02");
    LoadSound("Resources/Sounds/drop_00.wav", "drop_00");
    LoadSound("Resources/Sounds/drop_01.wav", "drop_01");
    LoadSound("Resources/Sounds/death_00.wav", "death_00");
    LoadSound("Resources/Sounds/punch_00.wav", "punch_00");
    LoadSound("Resources/Sounds/sacrifice_00.wav", "sacrifice_00");
    LoadSound("Resources/Sounds/sacrifice_01.wav", "sacrifice_01");
    LoadSound("Resources/Sounds/sacrifice_02.wav", "sacrifice_02");
    LoadSound("Resources/Sounds/sacrifice_03.wav", "sacrifice_03");
    LoadSound("Resources/Sounds/sacrifice_04.wav", "sacrifice_04");
    LoadSound("Resources/Sounds/damage.wav", "damage");
    LoadSound("Resources/Sounds/sword.wav", "sword");

    // Load Shaders
    Debug::Log("Loading shaders...");
    LoadShaderProgram("vertex.glsl", "fragment.glsl", "basic_shader");
    program = GetShaderProgram("basic_shader");

    if (Debug::IsFlagEnabled(MIX_AUDIO))
    {
        // Load Music
        m_bgMusic = Mix_LoadMUS("Resources/Music/jand_bg.mp3");
        if (!m_bgMusic)
        {
            Debug::LogError("Music could not be loaded. SDL_mixer error: %s", Mix_GetError());
        }

        // Start music
        //Mix_PlayMusic(m_bgMusic, -1);
    }

    // Setup the game
    m_map->Generate();

    // OPENGL TESTING

    // Create a VAO
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    // Create a VBO
    glGenBuffers(1, &vboID);

    // Create an EBO
    glGenBuffers(1, &eboID);

    GLfloat vertices[] = {
        -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
         0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
         0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
        -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
    };

    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
    };

    // Bind the vertex data to the VBO
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind the element data to the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    GLint positionAttribute = glGetAttribLocation(program->GetID(), "inPosition");
    GLint colorAttribute = glGetAttribLocation(program->GetID(), "inColor");
    GLint stAttribute = glGetAttribLocation(program->GetID(), "inTexCoord");

    glEnableVertexAttribArray(positionAttribute);
    glEnableVertexAttribArray(colorAttribute);
    glEnableVertexAttribArray(stAttribute);
    glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
    glVertexAttribPointer(colorAttribute, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glVertexAttribPointer(stAttribute, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));

    program->Use();
    
    int width = 0;
    int height = 0;
    unsigned char* image;

    // Create texture
    glGenTextures(1, &kittenTexID);

    // Bind the texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, kittenTexID);

    // Upload some data to the texture
    image = SOIL_load_image("Resources/Textures/gandalf.png", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);
    
    glUniform1i(glGetUniformLocation(program->GetID(), "texKitten"), 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    startTime = std::chrono::high_resolution_clock::now();

    glEnable(GL_DEPTH_TEST);

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

        m_window->SwapWindow();
    }
}

void Game::Terminate()
{
    m_isRunning = false;
}

void Game::Update(double deltaTime)
{
    if (m_input->GetKeyPress(SDLK_ESCAPE))
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
            m_map->SpawnPeon(1, m_mainCamera->ConvertToWorld(m_input->GetMousePosition()));
        }

        if (m_input->GetKeyPress(SDLK_u))
        {
            m_map->SpawnOrc();
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
    glClearColor(.3f, .3f, .3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLuint uniColor = glGetUniformLocation(program->GetID(), "overrideColor");
    GLuint uniTime = glGetUniformLocation(program->GetID(), "time");
    auto timeNow = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration_cast<std::chrono::duration<float>>(timeNow - startTime).count();
    glUniform1f(uniTime, time);

    GLuint uniModel = glGetUniformLocation(program->GetID(), "model");
    glm::mat4 model(1.0);

    /*
    model = glm::rotate(
        model,
        time * glm::radians(45.0f),
        glm::vec3(0.0f, 0.0f, 1.0f)
        );
    */

    //float factor = abs(sin(60.0 + time * 1.0));
    //model = glm::scale(model, glm::vec3(factor, factor, 1.1f));
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

    glm::mat4 view(1.0);
    view = glm::rotate(view, time * glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));
    /*
        view = glm::lookAt(
        glm::vec3(2.5f, 2.5f, 2.5f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f)
        );
    */
    GLint uniView = glGetUniformLocation(program->GetID(), "view");
    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

    glm::mat4 proj(1.0);
    proj = glm::perspective(glm::radians(90.0f), 1024.0f / 768.0f, 0.1f, 100.0f);
    GLint uniProj = glGetUniformLocation(program->GetID(), "proj");
    glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

    //GLint uniColor = glGetUniformLocation(shaderProgramID, "triangleColor");
    //glUniform3f(uniColor, 1.0f, 0.0f, 0.0f);

    //glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    //glDrawArrays(GL_TRIANGLES, 0, 36);

    /*
    glEnable(GL_STENCIL_TEST);

    // Draw floor
    glStencilFunc(GL_ALWAYS, 1, 0xFF); // Set any stencil to 1
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glStencilMask(0xFF); // Write to stencil buffer
    glDepthMask(GL_FALSE); // Don't write to depth buffer
    glClear(GL_STENCIL_BUFFER_BIT); // Clear the stencil buffer
    //glDrawArrays(GL_TRIANGLES, 36, 6);

    // Draw cube reflection
    glStencilFunc(GL_EQUAL, 1, 0xFF); // Pass test if stencil value is 1
    glStencilMask(0x00); // Don't write anything to stencil buffer
    glDepthMask(GL_TRUE); // Write to depth buffer
    model = glm::scale(
        glm::translate(model, glm::vec3(0, 0, -1)),
        glm::vec3(1, 1, -1)
        );
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

    glUniform3f(uniColor, 0.3f, 0.3f, 0.3f);
    //glDrawArrays(GL_TRIANGLES, 0, 36);
    glUniform3f(uniColor, 1.0f, 1.0f, 1.0f);

    glDisable(GL_STENCIL_TEST);
    */

    /*
    m_renderer->SetDrawColor(SDL_Color{ 0, 0, 0, 255 });
    m_renderer->Clear();

    m_mainCamera->Activate();

    m_map->Render();
    m_player->Render();

    // Render GUI
    m_GUICamera->Activate();

    Rect bottomBar(0, m_window->GetSize().y - 16, m_window->GetSize().x, 16);
    m_renderer->RenderFillRect(bottomBar, SDL_Color{ 128, 128, 128, 128 });
    Stockpile* stockpile = dynamic_cast<Stockpile*>(m_map->FindEntity(STOCKPILE));
    Inventory* stock = stockpile->GetInventory();
    Vector2D windowSize = m_window->GetSize();

    std::stringstream ss;
    ss << m_map->GetMonth() << " " << m_map->GetDay() << ", Year " << m_map->GetYear();
    m_renderer->RenderText("dos", (int)(windowSize.x / 2) - 100, (int)10, ss.str());
    ss.str(" ");

    ss << "Wood: " << stock->CountItem(ItemType::WOOD) << "         ";
    ss << "Stone: " << stock->CountItem(ItemType::STONE) << "         ";
    ss << "Coal: " << stock->CountItem(ItemType::COAL) << "         ";
    ss << "Iron Ore: " << stock->CountItem(ItemType::IRON_ORE) << "         ";
    ss << "Iron Bar: " << stock->CountItem(ItemType::IRON_BAR) << "         ";
    m_renderer->RenderText("dos", 5, (int)m_window->GetSize().y - 16, ss.str());
    ss.str(" ");

    // Debug stuff
    if (Debug::IsFlagEnabled(SHOW_MENU))
    {
        Rect container(5, 5, 340, 180);
        m_renderer->RenderFillRect(container, SDL_Color{ 128, 128, 128, 128 });

        ss << "Framerate: " << (int)m_frameRate;
        m_renderer->RenderText("dos", 10, 10, ss.str());
        ss.str(" ");

        ss << "Peon Count: " << "UNKNOWN";
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

        ss << "U - Spawn goblin";
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
    */
}

bool Game::LoadTexture(const std::string& path, const std::string& id)
{
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
    return true;
}

bool Game::LoadFont(const std::string& path, const std::string& id, const int& size)
{
    TTF_Font* font = TTF_OpenFont(path.c_str(), size);
    if (font == nullptr)
    {
        Debug::LogError("Failed to load font %s! SDL_ttf error: %s", path.c_str(), TTF_GetError());
    }

    m_fontMap[id] = font;
    return true;
}

bool Game::LoadSound(const std::string& path, const std::string& id)
{
    if (Debug::IsFlagEnabled(MIX_AUDIO))
    {
        Mix_Chunk* sound = Mix_LoadWAV(path.c_str());
        if (sound == nullptr)
        {
            Debug::LogError("Failed to load WAV from %s! SDL_mixer error: %s", path.c_str(), Mix_GetError());
            return false;
        }

        m_soundMap[id] = sound;
        return true;
    }

    return false;
}

bool Game::LoadShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const std::string& ID)
{
    std::string vertexShaderSource = ReadFile("Resources/Shaders/vertex.glsl");
    std::string fragmentShaderSource = ReadFile("Resources/Shaders/fragment.glsl");

    if (vertexShaderSource != "*FAILURE*" && fragmentShaderSource != "*FAILURE*")
    {
        m_shaderProgramMap[ID] = std::make_unique<ShaderProgram>(vertexShaderSource, fragmentShaderSource);
        return true;
    }

    return false;
}

SDL_Texture* Game::GetTexture(const std::string& id)
{
    return m_textureMap[id];
}

TTF_Font* Game::GetFont(const std::string& id)
{
    return m_fontMap[id];
}

ShaderProgram* Game::GetShaderProgram(const std::string& ID)
{
    return m_shaderProgramMap[ID].get();
}

void Game::PlaySound(const std::string& id)
{
    if (Debug::IsFlagEnabled(MIX_AUDIO))
    {
        if (m_soundMap[id] == nullptr)
        {
            Debug::LogError("Sound %s can't be played, as it doesn't exist!", id.c_str());
        }

        Mix_PlayChannel(-1, m_soundMap[id], 0);
    }
}

std::string Game::ReadFile(const std::string& path)
{
    std::ifstream input(path);
    if (!input.is_open()) {
        Debug::LogError("Failed to open file %s", path);
        return "*FAILURE*";
    }

    std::ostringstream ss;  
    ss << input.rdbuf();
    
    return ss.str();
}