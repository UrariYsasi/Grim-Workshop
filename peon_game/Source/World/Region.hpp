#pragma once

class World;
class TerrainTile;

class Region
{
public:
    Region(World* world);
    ~Region();

    void Update(float deltaTime);
    void Render(const grim::graphics::SpriteBatch& spriteBatch);

private:
    World* m_world;
    std::vector<std::vector<std::unique_ptr<TerrainTile>>> m_terrain;
};