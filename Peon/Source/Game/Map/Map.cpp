#include "PCH.hpp"
#include "Map.hpp"
#include "../Game.hpp"
#include "../Terrain/GrassTile.hpp"
#include "../Entity/Tree.hpp"
#include "../Entity/Rock.hpp"
#include "../Entity/Stockpile.hpp"
#include "../Entity/Peon.hpp"
#include "../Entity/Obelisk.hpp"

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
    CleanEntities();

    // Entities
    for (auto it = m_entities.begin(); it != m_entities.end(); it++)
    {
        Entity* e = (*it).get();
        e->Update(deltaTime);
    }
}

void Map::Render()
{
    // Terrain
    for (auto it = m_terrain.begin(); it != m_terrain.end(); it++)
    {
        Tile* t = (it->second).get();
        t->Render();
    }

    // Z sort Entities
    m_entities.sort([](std::unique_ptr<Entity> const& a, std::unique_ptr<Entity> const& b)
    {
        Rectangle aHit = a->GetHitBox();
        Rectangle bHit = b->GetHitBox();

        return (aHit.y + aHit.height) < (bHit.y + bHit.height);
    });

    // Entities
    for (auto it = m_entities.begin(); it != m_entities.end(); it++)
    {
        Entity* e = (*it).get();
        e->Render();
    }
}

void Map::Generate()
{
    Debug::Log("Generating map...");

    // Terrain
    for (int x = -(MAP_SIZE / 2); x < (MAP_SIZE / 2); x++)
    {
        for (int y = -(MAP_SIZE / 2); y < (MAP_SIZE / 2); y++)
        {
            Vector2D position(x, y);
            m_terrain[position] = std::make_unique<GrassTile>(m_game, position * 32);
        }
    }

    // Resources
    for (int x = -(MAP_SIZE / 2); x < (MAP_SIZE / 2); x++)
    {
        for (int y = -(MAP_SIZE / 2); y < (MAP_SIZE / 2); y++)
        {
            double val = m_generator.GeneratePerlin2D((double)(x + 59) / MAP_SIZE * 25, (double)(y + 73) / MAP_SIZE * 25);
            val = (val + 1) / 2.0;

            if (val > 1.0)
            {
                val = 1.0;
            }
            else if (val < 0.0)
            {
                val = 0.0;
            }

            if (val > .5)
            {
                Vector2D position(x * 32, y * 32);
                m_entities.push_back(std::make_unique<Tree>(m_game, position));
            }

            if (val < .25)
            {
                Vector2D position(x * 32, y * 32);
                m_entities.push_back(std::make_unique<Rock>(m_game, position));
            }
        }
    }

    // Stockpile
    m_entities.push_back(std::make_unique<Stockpile>(m_game, Vector2D(-64, 0)));

    // Obelisk
    m_entities.push_back(std::make_unique<Obelisk>(m_game, Vector2D(0, 0)));

    // Peons
    SpawnPeon(3);

    Debug::Log("Map generation complete.");
}

/*
    Delete all entities that have been marked for deletion in the previous frame.
*/
void Map::CleanEntities()
{
    for (auto it = m_entities.begin(); it != m_entities.end(); it++)
    {
        if ((*it)->IsDeleted())
        {
            m_entities.erase(it++);
        }
    }
}

/*
    Create some peons on the map.
*/
void Map::SpawnPeon(int quantity)
{
    for (int i = 0; i < quantity; i++)
    {
        Vector2D position(Random::Generate(-128, 128), Random::Generate(-128, 128));
        m_entities.push_back(std::make_unique<Peon>(m_game, position));
    }
}