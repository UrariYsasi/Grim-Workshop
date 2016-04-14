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
    glm::vec3 renderPosition(m_position.x, m_position.y, 0.0f);

    if (m_parent != nullptr)
    {
        glm::vec2 parentPosition = m_parent->GetPosition();
        renderPosition.x += parentPosition.x;
        renderPosition.y += parentPosition.y;
    }

    glm::vec3 renderRotation(0.0f);
    glm::vec3 renderScale(m_sprite->width, m_sprite->height, 1.0f);

    m_spriteBatch.Begin();
    m_spriteBatch.AddSprite(renderPosition, renderRotation, renderScale, m_sprite);
    m_spriteBatch.End();
}

}

}