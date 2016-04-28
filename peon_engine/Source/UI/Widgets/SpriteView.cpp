#include "PCH.hpp"
#include "SpriteView.hpp"

namespace grim
{

namespace ui
{

SpriteView::SpriteView(Engine* const engine, grim::graphics::Sprite* sprite) :
    Widget(engine),
    m_sprite(sprite)
{
    m_width = m_sprite->GetWidth();
    m_height = m_sprite->GetHeight();
}

SpriteView::~SpriteView()
{
}

void SpriteView::Update(float deltaTime)
{
    Widget::Update(deltaTime);
}

void SpriteView::Render()
{
    glm::vec3 renderPosition(m_position.x, m_position.y, m_zLayer);

    if (m_parent != nullptr)
    {
        glm::vec2 parentPosition = m_parent->GetPosition();
        renderPosition.x += parentPosition.x;
        renderPosition.y += parentPosition.y;
    }

    glm::vec3 renderRotation(0.0f, 0.0f, m_rotation);
    glm::vec3 renderScale(m_scale.x, m_scale.y, 1.0f);

    grim::graphics::Transform transform(renderPosition, renderRotation, renderScale);
    grim::graphics::RenderCommand command(m_sprite, transform, 1);
    m_engine->GetRenderer()->Submit(command);

    Widget::Render();
}

}

}