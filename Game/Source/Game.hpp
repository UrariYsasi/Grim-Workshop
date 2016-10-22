/*
    Game.hpp
    Game

    Declan Hopkins
    8/31/2016
*/

#pragma once

class Entity;
class Peon;
class Stockpile;
class TerrainTile;
class World;
class Player;

class Game : public grim::IGame
{
public:
    Game();
    ~Game();

    bool Initialize();
    virtual void Run();
    virtual void Terminate();

    grim::graphics::Camera* GetMainCamera();
    World* GetWorld();
    TTF_Font* GetFont(const std::string& id);
    grim::graphics::Shader* GetShader(const std::string& ID);
    grim::graphics::ShaderProgram* GetShaderProgram(const std::string& ID);
    grim::assets::Material* GetMaterial(const std::string& ID);
    grim::graphics::Sprite* GetEntitySprite(const EntityID& id);
    Player* GetPlayer();
    grim::Engine* const GetEngine();

    virtual void Update() override;
    virtual void Render() override;

private:
    bool LoadFont(const std::string& path, const std::string& id, const int& size = 16);

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

    bool CreateMaterial(const std::string& ID, grim::assets::Texture* const texture, grim::graphics::ShaderProgram* const shaderProgram);

    /*
        Read a file and output its contents in string form.
    */
    std::string ReadFile(const std::string& path);

private:
    grim::Engine m_engine;

    std::unique_ptr<grim::graphics::Camera> m_mainCamera;
    std::unique_ptr<World> m_map;
    std::unique_ptr<Player> m_player;

    // Textures
    std::map<std::string, std::unique_ptr<grim::assets::Texture>> m_textureMap;

    // Fonts
    std::map<std::string, TTF_Font*> m_fontMap;

    // Shaders
    std::map<std::string, std::unique_ptr<grim::graphics::Shader>> m_shaderMap;

    // Shader programs
    std::map<std::string, std::unique_ptr<grim::graphics::ShaderProgram>> m_shaderProgramMap;

    // Materials
    std::map<std::string, std::unique_ptr<grim::assets::Material>> m_materialMap;

    // Sprites
    std::map<EntityID, std::unique_ptr<grim::graphics::Sprite>> m_spriteMap;

    // This is here TEMPORARILY for debug purposes
    Mix_Music* m_bgMusic;
};