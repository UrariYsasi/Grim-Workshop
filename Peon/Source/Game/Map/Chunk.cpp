#include "PCH.hpp"
#include "Chunk.hpp"
#include "Map.hpp"
#include "../../Engine/PerlinGenerator.hpp"
#include "../Terrain/GrassTile.hpp"

Chunk::Chunk(Map* map, PerlinGenerator* generator, Vector2D position) :
    m_map(map),
    m_generator(generator),
    m_position(position)
{
    Generate();
}

Chunk::~Chunk()
{
}

void Chunk::Update(double deltaTime)
{
}

void Chunk::Render()
{
    // Render terrain
    for (auto it = m_terrain.begin(); it != m_terrain.end(); it++)
    {
        (*it)->Render();
    }
}

void Chunk::Generate()
{
    Debug::Log("Generating Chunk at (%d, %d)", (int)m_position.x, (int)m_position.y);

    // Terrain
    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int y = 0; y < CHUNK_SIZE; y++)
        {
            Vector2D position((m_position.x * (CHUNK_SIZE * 32)) + (x * 32), (m_position.y * (CHUNK_SIZE * 32)) + (y * 32));
            std::unique_ptr<GrassTile> tile = std::make_unique<GrassTile>(m_map->GetGame(), position);
            m_terrain.push_back(std::move(tile));
        }
    }

    // Resources
}