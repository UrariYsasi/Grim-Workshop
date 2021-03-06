#pragma once

class Player;
class World;
class Game;

class PlacementModule
{
public:
    PlacementModule(Player* owner);
    ~PlacementModule();

    void Update(float deltaTime);
    void Render();

    void SetHeldEntity(EntityID ID);
    bool IsPlacing() const;

private:
    Player* m_owner;
    Game* m_game;
    grim::ui::IInputModule* m_input;
    grim::graphics::Camera* m_camera;
    World* m_world;
    
    bool m_isPlacing;
    EntityID m_heldEntityID;
    grim::graphics::Sprite* m_heldEntitySprite;
};