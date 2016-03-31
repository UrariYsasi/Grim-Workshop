#pragma once
#include "Monster.hpp"

class Peon : public Monster
{
public:
    Peon(Game* game, const glm::vec2& position);
    virtual ~Peon();

    virtual void Update(double deltaTime);
    virtual void Render(grim::graphics::SpriteBatch& spriteBatch);

    void Select();
    void Deselect();

private:
    bool m_isSelected;
    std::unique_ptr<grim::graphics::Sprite> m_selectionSprite;
    std::unique_ptr<grim::graphics::Sprite> m_shadowSprite;
};
