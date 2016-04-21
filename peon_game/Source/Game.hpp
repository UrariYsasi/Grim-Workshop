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

    bool Initialize();
    virtual void Run();
    virtual void Terminate();

    grim::graphics::Camera* GetMainCamera();
    World* GetWorld();

    grim::graphics::Texture* GetTexture(const std::string& ID);
    TTF_Font* GetFont(const std::string& id);
    grim::graphics::Shader* GetShader(const std::string& ID);
    grim::graphics::ShaderProgram* GetShaderProgram(const std::string& ID);

    grim::graphics::Sprite* GetEntitySprite(const EntityID& id);
    Player* GetPlayer();

private:
    void Update(float deltaTime);
    void Render();

    bool LoadFont(const std::string& path, const std::string& id, const int& size = 16);

    /*
        Load a texture with the given file name from the Resources/Textures folder
        and store it in the texture map with the given ID.
    */
    bool LoadTexture(const std::string& path, const std::string& ID, const GLenum& scaleMode = GL_NEAREST);

    /*
        Load a shader with the given file name from the Resources/Shaders folder
        and store it in the shader map with the given ID.
    */
    bool LoadShader(const std::string& path, const GLenum& shaderType, const std::string& ID);

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

    // Shaders
    std::map<std::string, std::unique_ptr<grim::graphics::Shader>> m_shaderMap;

    // Shader programs
    std::map<std::string, std::unique_ptr<grim::graphics::ShaderProgram>> m_shaderProgramMap;

    // Sprites
    std::map<EntityID, std::unique_ptr<grim::graphics::Sprite>> m_spriteMap;

    // This is here TEMPORARILY for debug purposes
    Mix_Music* m_bgMusic;

    /*
        User Interface
    */

    grim::ui::TextView* m_frameRateWidget;
    grim::ui::TextView* m_dateWidget;
    grim::ui::TextView* m_peonCountWidget;
    grim::ui::TextView* m_woodCountWidget;
    grim::ui::TextView* m_faithCountWidget;

    grim::ui::TextView* m_basicPeonLabel;
    grim::ui::TextView* m_warriorPeonLabel;
    grim::ui::TextView* m_wizardPeonLabel;

    std::unique_ptr<grim::graphics::Sprite> m_spellBookSprite;
    grim::ui::SpriteView* m_spellbook;

    std::unique_ptr<grim::graphics::Sprite> m_buttonSprite;
    grim::ui::ButtonView* m_buttonOne;
};