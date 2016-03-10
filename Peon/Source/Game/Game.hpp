#pragma once

namespace grim
{

class Renderer;
class Camera;

}

class Window;
class Input;
class Entity;
class Peon;
class Stockpile;
class TerrainTile;
class World;
class Player;

class Game
{
public:
    Game();
    ~Game();

    grim::Renderer* GetRenderer();
    Input* GetInput();
    grim::Camera* GetMainCamera();
    World* GetWorld();

    int Initialize();
    void Run();
    void Terminate();

    grim::Texture* GetTexture(const std::string& ID);
    TTF_Font* GetFont(const std::string& id);
    grim::Shader* GetShader(const std::string& ID);
    grim::ShaderProgram* GetShaderProgram(const std::string& ID);

    void PlaySound(const std::string& id);

private:
    void Update(double deltaTime);
    void Render();

    //bool LoadTexture(const std::string& path, const std::string& id);
    bool LoadFont(const std::string& path, const std::string& id, const int& size = 16);
    bool LoadSound(const std::string& path, const std::string& id);

    /*
        Load a texture with the given file name from the Resources/Textures folder
        and store it in the texture map with the given ID.
    */
    bool LoadTexture(const std::string& textureFileName, const std::string& ID);

    /*
        Load a shader with the given file name from the Resources/Shaders folder
        and store it in the shader map with the given ID.
    */
    bool LoadShader(const std::string& shaderFileName, const GLenum& shaderType, const std::string& ID);

    /*
        Create a shader program with the given vertex and fragment shader IDs,
        and store it in the shader program map with the given ID.
    */
    bool CreateShaderProgram(const std::string& vertexShaderID, const std::string& fragmentShaderID, const std::string& ID);

    /*
        Read a file and output its contents in string form.
    */
    std::string ReadFile(const std::string& path);

private:
    bool m_isRunning;
    std::unique_ptr<Window> m_window;
    std::unique_ptr<grim::Renderer> m_renderer;
    std::unique_ptr<Input> m_input;
    std::unique_ptr<grim::Camera> m_mainCamera;
    std::unique_ptr<grim::Camera> m_GUICamera;
    std::unique_ptr<World> m_map;
    std::unique_ptr<Player> m_player;

    // Textures
    std::map<std::string, std::unique_ptr<grim::Texture>> m_textureMap;

    // Fonts
    std::map<std::string, TTF_Font*> m_fontMap;

    // Sounds
    std::map<std::string, Mix_Chunk*> m_soundMap;

    // Shaders
    std::map<std::string, std::unique_ptr<grim::Shader>> m_shaderMap;

    // Shader programs
    std::map<std::string, std::unique_ptr<grim::ShaderProgram>> m_shaderProgramMap;

    // This is here TEMPORARILY for debug purposes
    double m_frameCount;
    double m_frameRate;
    double m_gameStartTime;
    Mix_Music* m_bgMusic;
};
