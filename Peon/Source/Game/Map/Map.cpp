#include "PCH.hpp"
#include "Map.hpp"
#include "../Game.hpp"
#include "../Entity/Tree.hpp"
#include "../Entity/Rock.hpp"
#include "../Entity/Stockpile.hpp"
#include "../Entity/Altar.hpp"
#include "../Entity/Peon.hpp"
#include "../Entity/Orc.hpp"
#include "../Entity/Obelisk.hpp"
#include "../Terrain/TerrainTile.hpp"
#include "../../Engine/Input.hpp"
#include "../../Engine/Camera.hpp"

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
        TerrainTile* t = (it->second).get();
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
            m_terrain[position] = std::make_unique<TerrainTile>(m_game, position * 32);
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

    // Altar
    m_entities.push_back(std::make_unique<Altar>(m_game, Vector2D(-256, -128)));

    // Stockpile
    m_entities.push_back(std::make_unique<Stockpile>(m_game, Vector2D(-128, 0)));

    // Obelisk
    m_entities.push_back(std::make_unique<Obelisk>(m_game, Vector2D(0, 0)));

    // Peons
    SpawnPeon(3, Vector2D(-350, -128));

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
void Map::SpawnPeon(int quantity, const Vector2D& position)
{
    for (int i = 0; i < quantity; i++)
    {
        Vector2D spawnPos = position + Vector2D(Random::Generate(-32, 32), Random::Generate(-32, 32));
        m_entities.push_back(std::make_unique<Peon>(m_game, spawnPos));
    }
}

/*
    Create some orcs on the map.
*/
void Map::SpawnOrc(int quantity)
{
    for (int i = 0; i < quantity; i++)
    {
        Vector2D position = m_game->GetInput()->GetMousePosition();
        position = m_game->GetMainCamera()->ConvertToWorld(position);
        //position += Vector2D(Random::Generate(-32, 32), Random::Generate(-32, 32));
        m_entities.push_back(std::make_unique<Orc>(m_game, position));
    }
}

/*
    Checks whether a point on the map is passable or not.
*/
bool Map::IsPassable(const Vector2D& point)
{
    for (auto it = m_entities.begin(); it != m_entities.end(); it++)
    {
        Rectangle hitBox = (*it)->GetHitBox();
        if (hitBox.ContainsPoint(point))
        {
            return false;
        }
    }
    return true;
}

Entity* Map::GetEntityAtPoint(const Vector2D& point)
{
    Entity* ent = nullptr;
    for (auto it = m_entities.begin(); it != m_entities.end(); it++)
    {
        ent = (*it).get();
        Rectangle hitBox = ent->GetHitBox();
        if (hitBox.ContainsPoint(point))
        {
            return ent;
        }
    }

    return nullptr;
}

TerrainTile* Map::GetTerrainAtPoint(const Vector2D& point)
{
    Vector2D tilePosition = Vector2D(round(point.x / 32), round(point.y / 32));
    return m_terrain.at(tilePosition).get();
}

std::list<Entity*> Map::GetEntitiesInRectangle(int entityID, Rectangle rect)
{
    std::list<Entity*> ents;
    for (auto it = m_entities.begin(); it != m_entities.end(); it++)
    {
        Entity* ent = (*it).get();
        if (ent->GetEntityID() == entityID || entityID == NONE)
        {
            if (ent->IsCollidingWithRect(rect) && !ent->IsDead())
            {
                ents.push_back(ent);
            }
        }
    }

    return ents;
}

Entity* Map::FindEntity(int entityID)
{
    for (auto it = m_entities.begin(); it != m_entities.end(); it++)
    {
        if ((*it)->GetEntityID() == entityID || entityID == NONE)
        {
            return (*it).get();
        }
    }

    return nullptr;
}

std::list<Entity*> Map::FindAdjacentEntities(int entityID, Entity* ent)
{
    std::list<Entity*> ents;
    Vector2D position = ent->GetPosition();
    Entity* right = GetEntityAtPoint(position + Vector2D(32, 0));
    Entity* left = GetEntityAtPoint(position + Vector2D(-32, 0));
    Entity* bottom = GetEntityAtPoint(position + Vector2D(0, 32));
    Entity* top = GetEntityAtPoint(position + Vector2D(0, -32));

    if (right != nullptr)
    {
        if (right->GetEntityID() == entityID || entityID == NONE)
        {
            ents.push_back(right);
        }
    }
    if (left != nullptr)
    {
        if (left->GetEntityID() == entityID || entityID == NONE)
        {
            ents.push_back(left);
        }
    }
    if (bottom != nullptr)
    {
        if (bottom->GetEntityID() == entityID || entityID == NONE)
        {
            ents.push_back(bottom);
        }
    }
    if (top != nullptr)
    {
        if (top->GetEntityID() == entityID || entityID == NONE)
        {
            ents.push_back(top);
        }
    }
    return ents;
}

std::list<Entity*> Map::FindEntitiesInRange(int entityID, const Vector2D& point, int range)
{
    std::list<Entity*> ents;
    for (auto it = m_entities.begin(); it != m_entities.end(); it++)
    {
        Entity* ent = (*it).get();
        if (ent->GetEntityID() == entityID || entityID == NONE)
        {
            double distance = Vector2D::Distance(point, ent->GetPosition());
            if (distance <= range)
            {
                ents.push_back(ent);
            }
        }
    }

    return ents;
}
