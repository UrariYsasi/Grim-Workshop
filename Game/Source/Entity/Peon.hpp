#pragma once
#include "Monster.hpp"

class Peon : public Monster
{
public:
    Peon(Game* game, const glm::vec3& position);
    virtual ~Peon();

    virtual void Update(float deltaTime);
    virtual void Render();

    void Select();
    void Deselect();

private:
    bool m_isSelected;
    grim::graphics::Sprite m_selectionSprite;
    grim::graphics::Sprite m_shadowSprite;
};
