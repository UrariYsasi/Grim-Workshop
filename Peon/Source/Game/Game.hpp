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

    void PlaySound(const std::string& id);

private:
    void Update(double deltaTime);
    void Render();

    bool LoadTexture(const std::string& path, const std::string& id);
    bool LoadFont(const std::string& path, const std::string& id, const int& size = 16);
    bool LoadSound(const std::string& path, const std::string& id);

    /*
        Read a file and output its contents in string form.
    */
    std::string ReadFile(const std::string& path);

    GLuint CompileShader(const std::string& source, GLenum shaderType);
    GLuint LinkShaders(GLuint vertID, GLuint fragID);

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
    std::map<std::string, SDL_Texture*> m_textureWorld;

    // Fonts
    std::map<std::string, TTF_Font*> m_fontWorld;

    // Sounds
    std::map<std::string, Mix_Chunk*> m_soundWorld;

    // This is here TEMPORARILY for debug purposes
    double m_frameCount;
    double m_frameRate;
    double m_gameStartTime;
    Mix_Music* m_bgMusic;

    std::chrono::high_resolution_clock::time_point startTime;

    GLuint vaoID;
    GLuint vboID;
    GLuint eboID;

    GLuint vertexShaderID;
    GLuint fragmentShaderID;
    GLuint shaderProgramID;

    GLuint kittenTexID;
    GLuint puppyTexID;
};
