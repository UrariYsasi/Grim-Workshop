#pragma once

namespace grim
{

class Renderer;
class Camera;
class Mesh;

}

class Game;
class Input;
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
    void IssueCommand(glm::vec2 position);

private:
    const int CAMERA_SPEED_SLOW = 256;
    const int CAMERA_SPEED_NORMAL = 1024;
    const int CAMERA_SPEED_FAST = 1792;

    Game* m_game;
    Input* m_gameInput;
    grim::Camera* m_gameCamera;
    grim::Renderer* m_gameRenderer;
    World* m_gameWorld;

    int m_cameraSpeed;
    bool m_isBoxSelecting;
    grim::Rect m_boxSelection;
    std::list<Entity*> m_selectedPeons;

    std::unique_ptr<grim::Mesh> m_boxSelectionMesh;
};