#pragma once
#include "PCH.hpp"
#include "Peon.hpp"
#include "Tree.hpp"
#include "Stone.hpp"
#include "Bonfire.hpp"
#include "Window.hpp"
#include "Renderer.hpp"
#include "Input.hpp"
#include "EntityManager.hpp"

class Game
{
    public:
        Game();
        ~Game();

        void Initialize();
        void Terminate();
        void Update();
        void Render();

        void LeftClick();
        void LeftClickUp();
        void RightClick();
        void RightClickUp();

        Bonfire* FindBonfire(Peon* peon);
        Tree* FindTree(Peon* peon);
        void SpawnPeons(bool initial);
        void SacrificePeon(Peon* peon);
        void CommandPeons(Entity* target);
        void DepositResources(int amount);
        int GetResources() const;

        bool CheckCollision(SDL_Rect a, SDL_Rect b);

        // Textures
        bool LoadTexture(const std::string& path, const std::string& id);
        void RenderTexture(const std::string& id, const int& x, const int& y, const int& width, const int& height);
        void RenderSprite(const std::string& id, const int& col, const int& row, const int& x, const int& y, const int& width, const int& height);

        // Fonts
        bool LoadFont(const std::string& path, const std::string& id);
        void RenderText(const std::string& fontID, const int& x, const int& y, const std::string& text, SDL_Color color = {0, 0, 0, 255});

        // Sounds
        bool LoadSound(const std::string& path, const std::string& id);
        void PlaySound(const std::string& id);

    public:
        double m_deltaTime;

    private:
        bool m_isRunning;
        std::unique_ptr<Window> m_window;
        std::unique_ptr<Renderer> m_renderer;
        std::unique_ptr<Input> m_input;
        std::unique_ptr<EntityManager> m_entityManager;

        // Textures
        std::map<std::string, SDL_Texture*> m_textureMap;

        // Fonts
        std::map<std::string, TTF_Font*> m_fontMap;

        // Sounds
        std::map<std::string, Mix_Chunk*> m_soundMap;

        // GameObjects
        Bonfire* m_bonfire;

        std::vector<Peon*> m_selectedPeons;

        std::stringstream sstream;
        int m_resources;
        int m_peons;

        int m_peonsToSpawn = 10;
};
