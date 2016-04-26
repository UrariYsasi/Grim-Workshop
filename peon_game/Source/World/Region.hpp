#pragma once

class World;
class TerrainTile;

class Region
{
public:
    Region(World* world, const glm::ivec2 coordinates);
    ~Region();

    void Update(float deltaTime);
    void Render();
    void Generate();

    void SetIsExplored(bool isExplored);
    bool IsExplored() const;
    World* GetWorld();
    glm::vec2 GetCenter();
    glm::vec2 GetSize();
    grim::graphics::Rect GetRect();

private:
    void GenerateTerrain();
    void GenerateEntities();

public:
    const static uint16_t SIZE = 32;

private:
    World* m_world;
    glm::ivec2 m_coordinates;
    RegionID m_ID;
    std::vector<std::unique_ptr<TerrainTile>> m_terrain;
    bool m_isExplored;
};