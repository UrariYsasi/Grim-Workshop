#pragma once

namespace grim
{

class Engine;

namespace ui
{

class SpriteView : public Widget
{
public:
    SpriteView(Engine* const engine, grim::graphics::Sprite* sprite);
    ~SpriteView();

    virtual void Update(float deltaTime);
    virtual void Render();

private:
    grim::graphics::Sprite* m_sprite;
};

}

}