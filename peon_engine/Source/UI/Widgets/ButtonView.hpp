#pragma once

namespace grim
{

class Engine;

namespace ui
{

class ButtonView : public Widget
{
public:
    ButtonView(Engine* const engine, grim::graphics::Sprite* background);
    ~ButtonView();

    virtual void Update(float deltaTime);
    virtual void Render();
    virtual void OnClick(const glm::vec2& mousePosition);

private:
    SpriteView m_background;
};

}

}