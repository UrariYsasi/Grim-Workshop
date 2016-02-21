#pragma once
#include "../../Engine/PerlinGenerator.hpp"

class Game;
class TerrainTile;
class Entity;
class Peon;
class Stockpile;

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
    void SpawnOrc(int quantity = 1);
    bool IsPassable(const Vector2D& point);
    Entity* GetEntityAtPoint(const Vector2D& point);
    TerrainTile* GetTerrainAtPoint(const Vector2D& point);

    /*
        Finds and returns all Entities with the given ID that are contained
        in the given Rectangle.

        If the ID given is NONE, it will return all Entity types.
    */
    std::list<Entity*> GetEntitiesInRectangle(int entityID, Rectangle rect);

    /*
        Finds and returns the first Entity with the given ID.

        This is used to find unique Entities, such as the Obelisk.
    */
    Entity* FindEntity(int entityID);

    /*
        Finds Entities with the given ID that are adjacent to the given Entity.

        If the given ID is NONE, then it will search for ALL Entities.
    */
    std::list<Entity*> FindAdjacentEntities(int entityID, Entity* ent);

    /*
        Find Entities with the given ID that are near the given point.

        If the given ID is NONE, then it will search for ALL Entities.
    */
    std::list<Entity*> FindEntitiesInRange(int entityID, const Vector2D& point, int range);

private:
    void CleanEntities();

private:
    const static int MAP_SIZE = 64; // The map size, in tiles.

    Game* m_game;
    PerlinGenerator m_generator;

    std::unordered_map<Vector2D, std::unique_ptr<TerrainTile> > m_terrain;
    std::list< std::unique_ptr<Entity> > m_entities;
};