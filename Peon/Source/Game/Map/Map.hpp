#pragma once
#include "../../Engine/PerlinGenerator.hpp"

class Chunk;
class Game;

class Map
{
public:
    Map(Game* game);
    ~Map();

    Game* GetGame();

    void Update(double deltaTime);
    void Render();
    void Generate();

private:
    const static int MAP_SIZE = 3;

    Game* m_game;
    PerlinGenerator m_generator;
    std::unordered_map<Vector2D, Chunk*> m_chunks;
};