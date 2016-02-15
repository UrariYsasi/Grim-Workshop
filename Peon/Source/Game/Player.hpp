#pragma once

class Game;
class Input;
class Camera;
class Renderer;
class Peon;
class Map;

class Player
{
public:
    Player(Game* game);
    ~Player();

    void Update(double deltaTime);
    void Render();

private:
    const int CAMERA_SPEED_NORMAL = 1024;
    const int CAMERA_SPEED_FAST = 1792;

    Game* m_game;
    Input* m_gameInput;
    Camera* m_gameCamera;
    Renderer* m_gameRenderer;
    Map* m_gameMap;

    int m_cameraSpeed;
    bool m_isBoxSelecting;
    Rectangle m_boxSelection;
    std::list<Peon*> m_selectedPeons;
};