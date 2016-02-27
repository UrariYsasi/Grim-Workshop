#include "PCH.hpp"
#include "Tree.hpp"
#include "../Game.hpp"
#include "../../Engine/Renderer.hpp"

Tree::Tree(Game* game, Vector2D position) :
    Resource(game, position, TREE, ItemType::WOOD)
{
    m_origin = Vector2D(16, 48);
    m_hitBox = Rectangle(-16, -16, 32, 32);
    m_positionOffset = Vector2D(Random::Generate(-6, 6), Random::Generate(0, -6));
    m_hp = 10;
}

Tree::~Tree()
{
}

ItemType Tree::GetItem() const
{
    return m_item;
}

void Tree::Update(double deltaTime)
{
}

void Tree::Render()
{
    Renderer* renderer = m_game->GetRenderer();
    //int spriteCol = IsDead() ? 1 : 0;
    //int spriteRow = 0;
    //renderer->RenderSprite("resource", spriteCol, spriteRow, (int)(m_position.x - m_origin.x + m_positionOffset.x), (int)(m_position.y - m_origin.y + m_positionOffset.y), (int)SPRITE_SIZE.x, (int)SPRITE_SIZE.y * 2);

    renderer->RenderTexture("tree", (int)(m_position.x - m_origin.x + m_positionOffset.x), (int)(m_position.y - m_origin.y + m_positionOffset.y), 256, 512);

    /*
    if (m_peonCount > 0)
    {
        std::stringstream ss;
        ss << m_peonCount << "/" << m_peonLimit;
        renderer->RenderText("dos", (int)(m_position.x), (int)(m_position.y), ss.str());
    }
    */

    Entity::Render();
}