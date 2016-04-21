#include "PCH.hpp"
#include "Region.hpp"

Region::Region(World* world) :
    m_world(world)
{
}

Region::~Region()
{
}

void Region::Update(float deltaTime)
{
}

void Region::Render(const grim::graphics::SpriteBatch& spriteBatch)
{
}