#pragma once
#include "PlacementModule.hpp"
#include "Item/Inventory.hpp"

class Game;
class Entity;
class World;

class Player
{
public:
    Player(Game* game);
    ~Player();

    void Update(float deltaTime);
    void Render();

    Game* GetGame();
    grim::ui::IInput* GetInput();
    grim::graphics::Camera* GetCamera();
    World* GetWorld();

    Inventory* GetInventory();
    void AddPeon(uint32_t quantity = 1);
    void RemovePeon(uint32_t quantity = 1);
    uint32_t GetPeonCount() const;

    void AddFaith(uint32_t quantity = 1);
    void RemoveFaith(uint32_t quantity = 1);
    uint32_t GetFaith() const;

    PlacementModule* GetPlacement();

private:
    void IssueCommand(glm::vec2 position);

private:
    const int CAMERA_SPEED_SLOW = 256;
    const int CAMERA_SPEED_NORMAL = 1024;
    const int CAMERA_SPEED_FAST = 1792;

    Game* m_game;
    grim::ui::IInput* m_gameInput;
    grim::graphics::Camera* m_gameCamera;
    World* m_gameWorld;
    uint32_t m_peonCount;

    int m_cameraSpeed;
    bool m_isBoxSelecting;
    grim::graphics::Rect m_boxSelection;
    std::list<Entity*> m_selectedPeons;
    grim::graphics::Mesh m_boxSelectionMesh;

    uint32_t m_faith;

    /*
        Modules
    */

    PlacementModule m_placementModule;
    Inventory m_inventory;
};