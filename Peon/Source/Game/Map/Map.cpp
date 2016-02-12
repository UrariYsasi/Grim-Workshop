#include "PCH.hpp"
#include "Map.hpp"
#include "Chunk.hpp"
#include "../Game.hpp"

Map::Map(Game* game) :
    m_game(game)
{
}

Map::~Map()
{
}

Game* Map::GetGame()
{
    return m_game;
}

void Map::Update(double deltaTime)
{
    for (int x = 0; x < MAP_SIZE; x++)
    {
        for (int y = 0; y < MAP_SIZE; y++)
        {
            Vector2D position(x, y);
            m_chunks[position]->Update(deltaTime);
        }
    }
}

void Map::Render()
{
    for (int x = 0; x < MAP_SIZE; x++)
    {
        for (int y = 0; y < MAP_SIZE; y++)
        {
            Vector2D position(x, y);
            m_chunks[position]->Render();
        }
    }
}

void Map::Generate()
{
    Debug::Log("Generating map...");

    for (int x = 0; x < MAP_SIZE; x++)
    {
        for (int y = 0; y < MAP_SIZE; y++)
        {
            Vector2D position(x, y);
            m_chunks[position] = new Chunk(this, &m_generator, position);
        }
    }

    Debug::Log("Map generation complete.");
}