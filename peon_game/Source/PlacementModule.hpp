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

private:
    Player* m_owner;
    Game* m_game;
    grim::ui::IInput* m_input;
    grim::graphics::Camera* m_camera;
    World* m_world;
    
    bool m_isPlacing;
    EntityID m_heldEntityID;
    grim::graphics::SpriteBatch m_spriteBatch;
    grim::graphics::Sprite* m_heldEntitySprite;
};