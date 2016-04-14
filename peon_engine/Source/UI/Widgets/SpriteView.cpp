#include "PCH.hpp"
#include "SpriteView.hpp"

namespace grim
{

namespace ui
{

SpriteView::SpriteView(grim::graphics::Sprite* sprite) :
    m_sprite(sprite)
{
}

SpriteView::~SpriteView()
{
}

void SpriteView::Update(float deltaTime)
{
}

void SpriteView::Render()
{
    m_spriteBatch.Begin();
    m_spriteBatch.AddSprite(glm::vec3(m_position.x, m_position.y, 0.0f), glm::vec3(0.0f), glm::vec3(512.0f, 512.0f, 1.0f), m_sprite);
    m_spriteBatch.End();
}

}

}