#pragma once
#include "../../Engine/PerlinGenerator.hpp"

class Game;
class TerrainTile;
class Entity;
class Peon;

class Map
{
public:
    Map(Game* game);
    ~Map();

    Game* GetGame();

    void Update(double deltaTime);
    void Render();
    void Generate();
    void SpawnPeon(int quantity = 1);
    bool IsPassable(const Vector2D& point);
    std::list<Peon*> GetPeonsInRectangle(Rectangle rect);

private:
    void CleanEntities();

private:
    const static int MAP_SIZE = 64; // The map size, in tiles.

    Game* m_game;
    PerlinGenerator m_generator;

    std::unordered_map<Vector2D, std::unique_ptr<TerrainTile> > m_terrain;
    std::list< std::unique_ptr<Entity> > m_entities;
    std::list<Peon*> m_selectedPeons;
};