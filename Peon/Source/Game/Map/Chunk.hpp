#pragma once

class Map;
class PerlinGenerator;
class Tile;

class Chunk
{
public:
    Chunk(Map* map, PerlinGenerator* generator, Vector2D position);
    ~Chunk();
    
    void Update(double deltaTime);
    void Render();

    void Generate();

private:
    const static int CHUNK_SIZE = 32;

    Map* m_map;
    PerlinGenerator* m_generator;
    Vector2D m_position;

    std::list< std::unique_ptr<Tile> > m_terrain;
};