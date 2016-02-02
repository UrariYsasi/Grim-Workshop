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

    int Initialize();
    void Run();
    void Terminate();
    Stockpile* FindStockpile();

    void RenderTexture(const std::string& id, const int& x, const int& y, const int& width, const int& height);
    void RenderSprite(const std::string& id, const int& col, const int& row, const int& x, const int& y, const int& width, const int& height);
    void RenderText(const std::string& fontID, const int& x, const int& y, const std::string& text, const SDL_Color& color = { 0, 0, 0, 255 });
    void RenderRect(const SDL_Rect& rect, const SDL_Color& color = { 0, 0, 0, 255 });

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
    std::unique_ptr<Camera> m_camera;

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
    const static int MAP_SIZE = 100;
    std::list< std::unique_ptr<Tile> > m_terrain;

    // This is here TEMPORARILY for debug purposes
    int m_peonCount;
};
