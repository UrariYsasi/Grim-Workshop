#include "PCH.hpp"
#include "Region.hpp"
#include "World.hpp"
#include "Game.hpp"
#include "../Terrain/TerrainTile.hpp"

Region::Region(World* world, const glm::ivec2 coordinates) :
    m_world(world),
    m_coordinates(coordinates),
    m_isExplored(false)
{
}

Region::~Region()
{
}

void Region::Update(float deltaTime)
{
}

void Region::Render(grim::graphics::SpriteBatch& spriteBatch)
{
    // Render terrain
    for (auto it = m_terrain.begin(); it != m_terrain.end(); it++)
    {
        (*it)->Render(spriteBatch);
    }
}

void Region::Generate()
{
    if (m_coordinates == glm::ivec2(0, 0))
    {
        m_ID = REGION_OBELISK;
    }
    else if (m_coordinates == glm::ivec2(2, 0))
    {
        m_ID = REGION_BOSS_SPIDER;
    }
    else
    {
        m_ID = REGION_FOREST;
    }

    GenerateTerrain();
    GenerateEntities();
}

void Region::GenerateTerrain()
{
    //uint16_t index = (row * SIZE) + col;

    for (uint16_t row = 0; row < SIZE; row++)
    {
        for (uint16_t col = 0; col < SIZE; col++)
        {
            // Calculate tile position
            glm::ivec2 tilePosition(0);
            tilePosition.x = (col * TerrainTile::SIZE) + (m_coordinates.x * SIZE * TerrainTile::SIZE);
            tilePosition.y = (row * TerrainTile::SIZE) + (m_coordinates.y * SIZE * TerrainTile::SIZE);

            // Create tile
            m_terrain.push_back(std::make_unique<TerrainTile>(this, tilePosition));
        }
    }
}

void Region::GenerateEntities()
{
    // Flora
    std::vector<glm::vec2> outputList = grim::utility::PoissonDiskGenerator::Generate(GetCenter(), 40.0, 64.0, 30, GetRect());
    for (auto pointIt = outputList.begin(); pointIt != outputList.end(); pointIt++)
    {
        glm::vec2 treePosition = (*pointIt);

        if ((m_ID == REGION_BOSS_SPIDER) || (m_ID == REGION_OBELISK))
        {
            // Discard point if it's too close to map center
            if (glm::distance(treePosition, GetCenter()) < 400.0)
            {
                continue;
            }
        }

        m_world->Spawn(EntityID::RESOURCE_TREE, treePosition);
    }

    // Monsters
    if (m_ID == REGION_OBELISK)
    {
        m_world->Spawn(EntityID::PEON, GetCenter() + glm::vec2(0, 64));
        m_world->Spawn(EntityID::PEON, GetCenter() + glm::vec2(-32, 64));
        m_world->Spawn(EntityID::PEON, GetCenter() + glm::vec2(32, 64));
        m_world->Spawn(EntityID::MONSTER_ORC, GetCenter() + glm::vec2(128, 0));
    }

    if (m_ID == REGION_BOSS_SPIDER)
    {
        m_world->Spawn(EntityID::MONSTER_SPIDER_QUEEN, GetCenter());
    }

    // Structures
    if (m_ID == REGION_OBELISK)
    {
        m_world->Spawn(EntityID::STRUCTURE_OBELISK, GetCenter());
    }
}

void Region::SetIsExplored(bool isExplored)
{
    m_isExplored = isExplored;
}

bool Region::IsExplored() const
{
    return m_isExplored;
}

World* Region::GetWorld()
{
    return m_world;
}

glm::vec2 Region::GetCenter()
{
    glm::vec2 center;
    center.x = (m_coordinates.x * GetSize().x) + (GetSize().x / 2);
    center.y = (m_coordinates.y * GetSize().y) + (GetSize().y / 2);
    return center;
}

glm::vec2 Region::GetSize()
{
    return glm::vec2(SIZE * TerrainTile::SIZE, SIZE * TerrainTile::SIZE);
}

grim::graphics::Rect Region::GetRect()
{
    grim::graphics::Rect regionRect;
    regionRect.x = m_coordinates.x * GetSize().x;
    regionRect.y = m_coordinates.y * GetSize().y;
    regionRect.width = (SIZE - 1) * TerrainTile::SIZE;
    regionRect.height = (SIZE - 1) * TerrainTile::SIZE;

    return regionRect;
}