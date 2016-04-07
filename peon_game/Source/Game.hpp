#pragma once

class Entity;
class Peon;
class Stockpile;
class TerrainTile;
class World;
class Player;

class Game : public grim::Engine
{
public:
    Game();
    ~Game();

    virtual uint8_t Initialize();
    virtual void Run();
    virtual void Terminate();

    grim::graphics::Renderer* GetRenderer();
    grim::ui::Input* GetInput();
    grim::graphics::Camera* GetMainCamera();
    World* GetWorld();

    grim::graphics::Texture* GetTexture(const std::string& ID);
    TTF_Font* GetFont(const std::string& id);
    grim::graphics::Shader* GetShader(const std::string& ID);
    grim::graphics::ShaderProgram* GetShaderProgram(const std::string& ID);

    grim::graphics::Sprite* GetEntitySprite(const EntityID& id);

private:
    void Update(float deltaTime);
    void Render();

    //bool LoadTexture(const std::string& path, const std::string& id);
    bool LoadFont(const std::string& path, const std::string& id, const int& size = 16);

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
    std::unique_ptr<grim::graphics::Camera> m_mainCamera;
    std::unique_ptr<grim::graphics::Camera> m_uiCamera;
    std::unique_ptr<World> m_map;
    std::unique_ptr<Player> m_player;

    // Textures
    std::map<std::string, std::unique_ptr<grim::graphics::Texture>> m_textureMap;

    // Fonts
    std::map<std::string, TTF_Font*> m_fontMap;

    // Sounds
    std::map<std::string, Mix_Chunk*> m_soundMap;

    // Shaders
    std::map<std::string, std::unique_ptr<grim::graphics::Shader>> m_shaderMap;

    // Shader programs
    std::map<std::string, std::unique_ptr<grim::graphics::ShaderProgram>> m_shaderProgramMap;

    // Sprites
    std::map<EntityID, std::unique_ptr<grim::graphics::Sprite>> m_spriteMap;

    // This is here TEMPORARILY for debug purposes
    Mix_Music* m_bgMusic;

    grim::ui::Text* m_text;
};