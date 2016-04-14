#pragma once

namespace grim
{

namespace ui
{

class SpriteView : public Widget
{
public:
    SpriteView(grim::graphics::Sprite* sprite);
    ~SpriteView();

    virtual void Update(float deltaTime);
    virtual void Render();

private:
    grim::graphics::Sprite* m_sprite;
    grim::graphics::SpriteBatch m_spriteBatch;
};

}

}