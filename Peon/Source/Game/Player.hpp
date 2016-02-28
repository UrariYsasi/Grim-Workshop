#pragma once

class Game;
class Input;
class Camera;
class Renderer;
class Entity;
class World;

class Player
{
public:
    Player(Game* game);
    ~Player();

    void Update(double deltaTime);
    void Render();

private:
    void IssueCommand(Vector2D position);

private:
    const int CAMERA_SPEED_SLOW = 256;
    const int CAMERA_SPEED_NORMAL = 1024;
    const int CAMERA_SPEED_FAST = 1792;

    Game* m_game;
    Input* m_gameInput;
    Camera* m_gameCamera;
    Renderer* m_gameRenderer;
    World* m_gameWorld;

    int m_cameraSpeed;
    bool m_isBoxSelecting;
    Rect m_boxSelection;
    std::list<Entity*> m_selectedPeons;
};