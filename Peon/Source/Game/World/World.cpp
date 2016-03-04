#include "PCH.hpp"
#include "World.hpp"
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

World::World(Game* game) :
    m_game(game),
    m_day(1),
    m_month(1),
    m_year(1)
{
}

World::~World()
{
}

Game* World::GetGame()
{
    return m_game;
}

int World::GetDay()
{
    return m_day;
}

std::string World::GetMonth()
{
    switch (m_month)
    {
        case 1:
            return "Aerokim";
        case 2:
            return "Jaipeto";
        case 3:
            return "Avoth";
        case 4:
            return "Ino";
        case 5:
            return "Odan";
        case 6:
            return "Jukra";
        case 7:
            return "Taeylom";
        case 8:
            return "Aelond";
        case 9:
            return "Eima";
        case 10:
            return "Draev";
        case 11:
            return "Jandas";
        case 12:
            return "Eraindr";
        default:
            return "UNKNOWN";
    }
}

int World::GetYear()
{
    return m_year;
}

void World::Update(double deltaTime)
{
    CleanEntities();
    ProcessTime();

    // Entities
    for (auto it = m_entities.begin(); it != m_entities.end(); it++)
    {
        Entity* e = (*it).get();
        e->Update(deltaTime);
    }
}

void World::Render()
{
    // Terrain
    for (auto it = m_terrain.begin(); it != m_terrain.end(); it++)
    {
        TerrainTile* t = (it->second).get();
        t->Render();
    }

    /*
    // Z sort Entities
    m_entities.sort([](std::unique_ptr<Entity> const& a, std::unique_ptr<Entity> const& b)
    {
        Rect aHit = a->GetHitBox();
        Rect bHit = b->GetHitBox();

        return (aHit.y + aHit.height) < (bHit.y + bHit.height);
    });
    */

    // Entities
    for (auto it = m_entities.begin(); it != m_entities.end(); it++)
    {
        Entity* e = it->get();
        e->Render();
    }
}

void World::ProcessTime()
{
    if (!m_worldTimer.IsStarted())
    {
        m_worldTimer.Start();
    }
    else if (m_worldTimer.GetTime() > 5000)
    {
        m_worldTimer.Stop();
        m_day++;
        
        if (m_day > 30)
        {
            m_day = 1;
            m_month++;
        }

        if (m_month > 12)
        {
            m_month = 1;
            m_year++;
        }
    }
}

void World::Generate()
{
    Debug::Log("Generating world...");

    // Terrain
    for (int x = 0; x < MAP_SIZE; x++)
    {
        for (int y = 0; y < MAP_SIZE; y++)
        {
            glm::vec2 position((float)x, (float)y);
            m_terrain[position] = std::make_unique<TerrainTile>(m_game, position * 32.0f);
        }
    }

    // Resources
    m_entities.push_back(std::make_unique<Tree>(m_game, glm::vec2(0, 0)));

    // Altar
    //m_entities.push_back(std::make_unique<Altar>(m_game, glm::vec2(-256, -128)));

    // Stockpile
    //m_entities.push_back(std::make_unique<Stockpile>(m_game, glm::vec2(-128, 0)));

    // Obelisk
    //m_entities.push_back(std::make_unique<Obelisk>(m_game, glm::vec2(0, 0)));

    // Peons
    SpawnPeon(3, glm::vec2(0, 0));

    Debug::Log("World generation complete.");
}

/*
    Delete all entities that have been marked for deletion in the previous frame.
*/
void World::CleanEntities()
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
void World::SpawnPeon(int quantity, const glm::vec2& position)
{
    for (int i = 0; i < quantity; i++)
    {
        glm::vec2 spawnPos = position + glm::vec2(Random::Generate(-32, 32), Random::Generate(-32, 32));
        m_entities.push_back(std::make_unique<Peon>(m_game, spawnPos));
    }
}

/*
    Create some orcs on the map.
*/
void World::SpawnOrc(int quantity)
{
    for (int i = 0; i < quantity; i++)
    {
        glm::vec2 mousePos = m_game->GetInput()->GetMousePosition();
        glm::vec2 spawnPos = m_game->GetMainCamera()->ConvertToWorld(mousePos);
        m_entities.push_back(std::make_unique<Orc>(m_game, spawnPos));
    }
}

/*
    Checks whether a point on the map is passable or not.
*/
bool World::IsPassable(const glm::vec2& point)
{
    for (auto it = m_entities.begin(); it != m_entities.end(); it++)
    {
        Rect hitBox = (*it)->GetHitBox();
        if (hitBox.ContainsPoint(point))
        {
            return false;
        }
    }
    return true;
}

Entity* World::GetEntityAtPoint(const glm::vec2& point, int entityID)
{
    Entity* ent = nullptr;
    for (auto it = m_entities.begin(); it != m_entities.end(); it++)
    {
        ent = (*it).get();
        if (ent->GetEntityID() == entityID || entityID == NONE)
        {
            Rect hitBox = ent->GetHitBox();
            if (hitBox.ContainsPoint(point))
            {
                return ent;
            }
        }
    }

    return nullptr;
}

TerrainTile* World::GetTerrainAtPoint(const glm::vec2& point)
{
    glm::vec2 tilePosition = glm::vec2(round(point.x / 32), round(point.y / 32));
    return m_terrain.at(tilePosition).get();
}

std::list<Entity*> World::GetEntitiesInRect(int entityID, Rect rect)
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

Entity* World::FindEntity(int entityID)
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

std::list<Entity*> World::FindEntitiesInRange(int entityID, const glm::vec2& point, int range)
{
    std::list<Entity*> ents;
    for (auto it = m_entities.begin(); it != m_entities.end(); it++)
    {
        Entity* ent = (*it).get();
        if (ent->GetEntityID() == entityID || entityID == NONE)
        {
            double distance = glm::distance(point, ent->GetPosition());
            if (distance <= range)
            {
                ents.push_back(ent);
            }
        }
    }

    return ents;
}
