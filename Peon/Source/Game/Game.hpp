#pragma once
#include "../PCH.hpp"
#include "../Engine/Window.hpp"
#include "../Engine/Renderer.hpp"
#include "../Engine/Input.hpp"
#include "Entity/Entity.hpp"
#include "Entity/Peon.hpp"

class Stockpile;

class Game
{
    public:
        Game();
        ~Game();

        void Initialize();
        void Terminate();
        void Update();
        void Render();
        void CleanEntities();
        void SpawnPeon();
        void IssueCommand(Entity* ent);

        void Game::AddResources(const int& resources);
        Stockpile* Game::FindStockpile();

        bool LoadTexture(const std::string& path, const std::string& id);
        bool LoadFont(const std::string& path, const std::string& id, const int& size = 16);
        bool LoadSound(const std::string& path, const std::string& id);

        void RenderTexture(const std::string& id, const int& x, const int& y, const int& width, const int& height);
        void RenderSprite(const std::string& id, const int& col, const int& row, const int& x, const int& y, const int& width, const int& height);
        void RenderText(const std::string& fontID, const int& x, const int& y, const std::string& text, const SDL_Color& color = {0, 0, 0, 255});
        void RenderRect(const SDL_Rect& rect, const SDL_Color& color = {0, 0, 0, 255});

        void PlaySound(const std::string& id);

    public:
        double m_deltaTime;
        int m_peonCount;

    private:
        bool m_isRunning;
        std::unique_ptr<Window> m_window;
        std::unique_ptr<Renderer> m_renderer;
        std::unique_ptr<Input> m_input;

        // Textures
        std::map<std::string, SDL_Texture*> m_textureMap;

        // Fonts
        std::map<std::string, TTF_Font*> m_fontMap;

        // Sounds
        std::map<std::string, Mix_Chunk*> m_soundMap;

        // Entities
        std::list<Entity*> m_entities;
        std::list<Peon*> m_selectedPeons;

        int m_resources;
};
