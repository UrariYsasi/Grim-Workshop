#include "PCH.hpp"
#include "SpriteView.hpp"

namespace grim
{

namespace ui
{

SpriteView::SpriteView(grim::graphics::Sprite* sprite) :
    m_sprite(sprite)
{
    m_width = m_sprite->width;
    m_height = m_sprite->height;
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

    glm::vec3 renderRotation(0.0f, 0.0f, m_rotation);
    glm::vec3 renderScale(m_scale.x, m_scale.y, 1.0f);

    m_spriteBatch.Begin();
    m_spriteBatch.AddSprite(renderPosition, renderRotation, renderScale, m_sprite);
    m_spriteBatch.End();
}

}

}