#pragma once

namespace grim
{

namespace ui
{

class ButtonView : public Widget
{
public:
    ButtonView(grim::graphics::Sprite* background);
    ~ButtonView();

    virtual void Update(float deltaTime);
    virtual void Render();

private:
    SpriteView m_background;
};

}

}