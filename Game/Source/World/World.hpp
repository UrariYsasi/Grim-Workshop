#pragma once

class Game;
class TerrainTile;
class Entity;
class Peon;
class Stockpile;
class Region;

class World
{
public:
    World(Game* game);
    ~World();

    void Update(float deltaTime);
    void Render();
    void ProcessTime();
    void Generate();
    Region* CreateRegion(const glm::ivec2& coordinates);
    void ExploreRegion(const glm::ivec2& coordinates);
    glm::ivec2 ConvertToRegionCoordinates(const glm::vec3& position);
    Entity* Spawn(const EntityID& ID, const glm::vec3& position);
    void CalculateEntityDepth(Entity* const entity);
    bool ShouldCullEntity(Entity* const entity);

    /*
        Gets the Entity with the given ID that is currently colliding with the given point.

        If the give ID is NONE, then it will return any Entity.
    */
    Entity* GetEntityAtPoint(const glm::vec2& point, EntityID ID = EntityID::NONE);

    /*
        Finds and returns all Entities with the given ID that are contained
        in the given Rect.

        If the ID given is NONE, it will return all Entity types.
    */
    std::list<Entity*> GetEntitiesInRect(EntityID ID, const grim::graphics::Rect& rect);

    /*
        Finds and returns the first Entity with the given ID.

        This is used to find unique Entities, such as the Obelisk.
    */
    Entity* FindEntity(EntityID ID);

    Game* GetGame();
    Region* GetRegion(const glm::ivec2& coordinates);
    uint16_t GetDay() const;
    std::string GetMonth() const;
    uint16_t GetYear() const;
    glm::vec2 GetCenter();
    glm::vec2 GetSize() const;
    bool IsPassable(const glm::vec2& point) const;
    bool IsRegionExplored(const glm::ivec2& coordinates);

private:
    void CleanEntities();

public:
    const static uint16_t SIZE = 64; // The map size, in tiles.
    const static uint16_t DAY_LENGTH = 5000; // The time, in milliseconds, in a game day.
    const static uint16_t MONTH_LENGTH = 30; // The amount of days in a game month.
    const static uint16_t YEAR_LENGTH = 12; // The amount of months in a game year.

private:
    Game* m_game;
    std::unordered_map<glm::ivec2, std::unique_ptr<Region>> m_regions;
    std::list<std::unique_ptr<Entity>> m_entities;

    // Time
    grim::utility::Timer m_worldTimer;
    int m_day;
    int m_month;
    int m_year;
};