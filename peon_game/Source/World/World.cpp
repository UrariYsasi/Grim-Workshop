#include "PCH.hpp"
#include "World.hpp"
#include "../Game.hpp"
#include "../Entity/Tree.hpp"
#include "../Entity/Rock.hpp"
#include "../Entity/Stockpile.hpp"
#include "../Entity/Altar.hpp"
#include "../Entity/Peon.hpp"
#include "../Entity/Orc.hpp"
#include "../Entity/Spider.hpp"
#include "../Entity/Obelisk.hpp"
#include "../Entity/ItemDrop.hpp"
#include "../Entity/BeamEffect.hpp"
#include "../Terrain/TerrainTile.hpp"
#include "Region.hpp"

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

void World::Update(float deltaTime)
{
    CleanEntities();
    ProcessTime();

    // Entities
    /*
    for (auto it = m_entities.begin(); it != m_entities.end(); it++)
    {
        Entity* e = (*it).get();
        e->Update(deltaTime);
    }
    */

    // Regions
    for (auto it = m_regions.begin(); it != m_regions.end(); it++)
    {
        (*it).second->Update(deltaTime);
    }
}

void World::Render()
{
    // Regions
    for (auto it = m_regions.begin(); it != m_regions.end(); it++)
    {
        (*it).second->Render();
    }

    // Entities
    /*
    for (auto it = m_entities.begin(); it != m_entities.end(); it++)
    {
        Entity* e = it->get();

        if (!ShouldCullEntity(e))
        {
            CalculateEntityDepth(e);
            e->Render();
        }
    }
    */
}

void World::ProcessTime()
{
    if (!m_worldTimer.IsStarted())
    {
        m_worldTimer.Start();
    }
    else if (m_worldTimer.GetTimeInMilliseconds() > DAY_LENGTH)
    {
        m_worldTimer.Stop();
        m_day++;

        if (m_day > MONTH_LENGTH)
        {
            m_day = 1;
            m_month++;
        }

        if (m_month > YEAR_LENGTH)
        {
            m_month = 1;
            m_year++;
        }
    }
}

void World::Generate()
{
    //grim::utility::Debug::Log("Generating world...");

    // Explore initial Region
    ExploreRegion(glm::ivec2(0, 0));

    //grim::utility::Debug::Log("World generation complete.");
}

Region* World::CreateRegion(const glm::ivec2& coordinates)
{
    if (GetRegion(coordinates) != nullptr)
    {
        return nullptr;
    }

    std::unique_ptr<Region> pNewRegion = std::make_unique<Region>(this, coordinates);
    Region* pRegion = pNewRegion.get();
    pNewRegion->Generate();
    m_regions.emplace(std::make_pair(coordinates, std::move(pNewRegion)));
    return pRegion;
}

void World::ExploreRegion(const glm::ivec2& coordinates)
{
    Region* pRegion = GetRegion(coordinates);
    if (pRegion == nullptr)
    {
        // There is no region here to explore! Create it.
        pRegion = CreateRegion(coordinates);
        if (pRegion == nullptr)
        {
            return;
        }
    }

    if (pRegion->IsExplored()) 
    {
        return; 
    }

    pRegion->SetIsExplored(true);

    // Create surrounding Regions
    CreateRegion(coordinates + glm::ivec2(-1, -1)); // Top left
    CreateRegion(coordinates + glm::ivec2(0, -1));  // Top center
    CreateRegion(coordinates + glm::ivec2(1, -1));  // Top right
    CreateRegion(coordinates + glm::ivec2(-1, 0));  // Center left
    CreateRegion(coordinates + glm::ivec2(1, 0));   // Center right
    CreateRegion(coordinates + glm::ivec2(-1, 1));  // Bottom left
    CreateRegion(coordinates + glm::ivec2(0, 1));   // Bottom center
    CreateRegion(coordinates + glm::ivec2(1, 1));   // Bottom right

    //grim::utility::Debug::Log("Explored Region at (%d, %d).", coordinates.x, coordinates.y);
}

glm::ivec2 World::ConvertToRegionCoordinates(const glm::vec3& position)
{
    glm::ivec2 coordinates;
    coordinates.x = static_cast<int32_t>(std::floor(position.x / (Region::SIZE * TerrainTile::SIZE)));
    coordinates.y = static_cast<int32_t>(std::floor(position.y / (Region::SIZE * TerrainTile::SIZE)));

    return coordinates;
}

Entity* World::Spawn(const EntityID& ID, const glm::vec3& position)
{
    Entity* spawned = nullptr;

    if (ID == EntityID::PEON)
    {
        std::unique_ptr<Peon> ent = std::make_unique<Peon>(m_game, position);
        spawned = ent.get();
        m_entities.push_back(std::move(ent));
    }
    else if (ID == EntityID::ITEM_DROP)
    {
        std::unique_ptr<ItemDrop> ent = std::make_unique<ItemDrop>(m_game, position, ItemType::WOOD);
        spawned = ent.get();
        m_entities.push_back(std::move(ent));
    }
    else if (ID == EntityID::MONSTER_ORC)
    {
        std::unique_ptr<Orc> ent = std::make_unique<Orc>(m_game, position);
        spawned = ent.get();
        m_entities.push_back(std::move(ent));
    }
    else if (ID == EntityID::MONSTER_SPIDER_QUEEN)
    {
        std::unique_ptr<Spider> ent = std::make_unique<Spider>(m_game, position);
        spawned = ent.get();
        m_entities.push_back(std::move(ent));
    }
    else if (ID == EntityID::STRUCTURE_STOCKPILE)
    {
        std::unique_ptr<Stockpile> ent = std::make_unique<Stockpile>(m_game, position);
        spawned = ent.get();
        m_entities.push_back(std::move(ent));
    }
    else if (ID == EntityID::EFFECT_BEAM)
    {
        std::unique_ptr<BeamEffect> ent = std::make_unique<BeamEffect>(m_game, position);
        spawned = ent.get();
        m_entities.push_back(std::move(ent));
    }
    else if (ID == EntityID::RESOURCE_TREE)
    {
        std::unique_ptr<Tree> ent = std::make_unique<Tree>(m_game, position);
        spawned = ent.get();
        m_entities.push_back(std::move(ent));
    }
    else if (ID == EntityID::STRUCTURE_OBELISK)
    {
        std::unique_ptr<Obelisk> ent = std::make_unique<Obelisk>(m_game, position);
        spawned = ent.get();
        m_entities.push_back(std::move(ent));
    }

    return spawned;
}

void World::CalculateEntityDepth(Entity* const entity)
{
    grim::graphics::Transform entityTransform = entity->GetTransform();
    float currentY = m_game->GetMainCamera()->ConvertToScreen(glm::vec2(entityTransform.position.x, entityTransform.position.y)).y;
    float normalizedY = (currentY / m_game->GetMainCamera()->GetHeight());
    float zLayer = normalizedY * 0.001f;

    entityTransform.position.z = zLayer;
    entity->SetTransform(entityTransform);
}

bool World::ShouldCullEntity(Entity* const entity)
{
    grim::graphics::Camera* mainCamera = m_game->GetMainCamera();
    grim::graphics::Transform entityTransform = entity->GetTransform();
    glm::vec2 screenPosition = mainCamera->ConvertToScreen(glm::vec2(entityTransform.position.x, entityTransform.position.y));
    glm::vec2 normalizedScreenPosition = screenPosition / glm::vec2(mainCamera->GetWidth(), mainCamera->GetHeight());

    float minX = -0.1f;
    float maxX = 1.1f;
    float minY = -0.1f;
    float maxY = 1.1f;

    return ((normalizedScreenPosition.x < minX) ||
            (normalizedScreenPosition.x > maxX) ||
            (normalizedScreenPosition.y < minY) ||
            (normalizedScreenPosition.y > maxY));
}

Entity* World::GetEntityAtPoint(const glm::vec2& point, EntityID ID)
{
    Entity* ent = nullptr;
    for (auto it = m_entities.begin(); it != m_entities.end(); it++)
    {
        ent = (*it).get();
        if ((ent->GetID() == ID) || (ID == EntityID::NONE))
        {
            grim::graphics::Rect hitBox = ent->GetHitBox();
            if (hitBox.ContainsPoint(point))
            {
                return ent;
            }
        }
    }

    return nullptr;
}

std::list<Entity*> World::GetEntitiesInRect(EntityID ID, const grim::graphics::Rect& rect)
{
    std::list<Entity*> ents;
    for (auto it = m_entities.begin(); it != m_entities.end(); it++)
    {
        Entity* ent = (*it).get();
        if (ent->GetID() == ID || ID == EntityID::NONE)
        {
            if (ent->IsCollidingWithRect(rect) && !ent->IsDead())
            {
                ents.push_back(ent);
            }
        }
    }

    return ents;
}

Entity* World::FindEntity(EntityID ID)
{
    for (auto it = m_entities.begin(); it != m_entities.end(); it++)
    {
        if ((*it)->GetID() == ID || ID == EntityID::NONE)
        {
            return (*it).get();
        }
    }

    return nullptr;
}

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

Game* World::GetGame()
{
    return m_game;
}

Region* World::GetRegion(const glm::ivec2& coordinates)
{
    auto it = m_regions.find(coordinates);
    if (it != m_regions.end())
    {
        return (it->second).get();
    }

    return nullptr;
}

uint16_t World::GetDay() const
{
    return m_day;
}

std::string World::GetMonth() const
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

uint16_t World::GetYear() const
{
    return m_year;
}

glm::vec2 World::GetCenter() 
{
    return glm::vec2((Region::SIZE * TerrainTile::SIZE) / 2, (Region::SIZE * TerrainTile::SIZE) / 2);
}

glm::vec2 World::GetSize() const
{
    return glm::vec2(((SIZE - 1) * 32.0f), ((SIZE - 1) * 32.0f));
}

bool World::IsPassable(const glm::vec2& point) const
{
    for (auto it = m_entities.begin(); it != m_entities.end(); it++)
    {
        grim::graphics::Rect hitBox = (*it)->GetHitBox();
        if (hitBox.ContainsPoint(point))
        {
            return false;
        }
    }
    return true;
}

bool World::IsRegionExplored(const glm::ivec2& coordinates)
{
    Region* pRegion = GetRegion(coordinates);
    if (pRegion != nullptr)
    {
        return pRegion->IsExplored();
    }

    return false;
}