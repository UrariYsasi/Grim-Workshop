#pragma once

class Window;
class Renderer;
class Input;
class Entity;
class Peon;
class Stockpile;
class TerrainTile;
class Camera;
class World;
class Player;
class ShaderProgram;

class Game
{
public:
    Game();
    ~Game();

    Renderer* GetRenderer();
    Input* GetInput();
    Camera* GetMainCamera();
    World* GetWorld();

    int Initialize();
    void Run();
    void Terminate();

    SDL_Texture* GetTexture(const std::string& id);
    TTF_Font* GetFont(const std::string& id);
    grim::Shader* GetShader(const std::string& ID);
    ShaderProgram* GetShaderProgram(const std::string& ID);

    void PlaySound(const std::string& id);

private:
    void Update(double deltaTime);
    void Render();

    bool LoadTexture(const std::string& path, const std::string& id);
    bool LoadFont(const std::string& path, const std::string& id, const int& size = 16);
    bool LoadSound(const std::string& path, const std::string& id);
    bool LoadShader(const std::string& shaderFileName, const GLenum& shaderType, const std::string& ID);
    bool CreateShaderProgram(const std::string& vertexShaderID, const std::string& fragmentShaderID, const std::string& ID);

    /*
        Read a file and output its contents in string form.
    */
    std::string ReadFile(const std::string& path);

private:
    bool m_isRunning;
    std::unique_ptr<Window> m_window;
    std::unique_ptr<Renderer> m_renderer;
    std::unique_ptr<Input> m_input;
    std::unique_ptr<Camera> m_mainCamera;
    std::unique_ptr<Camera> m_GUICamera;
    std::unique_ptr<World> m_map;
    std::unique_ptr<Player> m_player;

    // Textures
    std::map<std::string, SDL_Texture*> m_textureMap;

    // Fonts
    std::map<std::string, TTF_Font*> m_fontMap;

    // Sounds
    std::map<std::string, Mix_Chunk*> m_soundMap;

    // Shaders
    std::map<std::string, std::unique_ptr<grim::Shader>> m_shaderMap;
    std::map<std::string, std::unique_ptr<ShaderProgram>> m_shaderProgramMap;

    // This is here TEMPORARILY for debug purposes
    double m_frameCount;
    double m_frameRate;
    double m_gameStartTime;
    Mix_Music* m_bgMusic;

    std::chrono::high_resolution_clock::time_point startTime;

    GLuint vaoID;
    GLuint vboID;
    GLuint eboID;

    ShaderProgram* program;

    GLuint kittenTexID;
    GLuint puppyTexID;
};
