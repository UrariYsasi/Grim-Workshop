#pragma once

class Window;
class Renderer;
class Input;
class Entity;
class Peon;
class Stockpile;
class Tile;
class Camera;

class Game
{
public:
    Game();
    ~Game();

    Renderer* GetRenderer();

    int Initialize();
    void Run();
    void Terminate();
    Stockpile* FindStockpile();

    SDL_Texture* GetTexture(const std::string& id);
    TTF_Font* GetFont(const std::string& id);

    void PlaySound(const std::string& id);

private:
    void Update(double deltaTime);
    void Render();
    void CleanEntities();
    void SpawnPeon();
    void IssueCommand(Entity* ent);
    void GenerateMap();

    bool LoadTexture(const std::string& path, const std::string& id);
    bool LoadFont(const std::string& path, const std::string& id, const int& size = 16);
    bool LoadSound(const std::string& path, const std::string& id);

private:
    bool m_isRunning;
    std::unique_ptr<Window> m_window;
    std::unique_ptr<Renderer> m_renderer;
    std::unique_ptr<Input> m_input;
    std::unique_ptr<Camera> m_mainCamera;
    std::unique_ptr<Camera> m_GUICamera;

    // Textures
    std::map<std::string, SDL_Texture*> m_textureMap;

    // Fonts
    std::map<std::string, TTF_Font*> m_fontMap;

    // Sounds
    std::map<std::string, Mix_Chunk*> m_soundMap;

    // Entities
    std::list<Entity*> m_entities;
    std::list<Peon*> m_selectedPeons;

    // Terrain
    const static int MAP_SIZE = 40;
    std::list< std::unique_ptr<Tile> > m_terrain;

    // Mouse selection
    bool m_isBoxSelecting;
    Rectangle m_boxSelection;

    // This is here TEMPORARILY for debug purposes
    int m_peonCount;
    double m_frameCount;
    double m_frameRate;
    double m_gameStartTime;
};
