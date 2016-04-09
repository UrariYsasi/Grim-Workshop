#pragma once
#include "Entity.hpp"

class ItemDrop : public Entity
{
public:
    ItemDrop(Game* game, const glm::vec2& position, const ItemType& type);
    virtual ~ItemDrop();

    ItemType GetItem() const;

    virtual void Update(float deltaTime);
    virtual void Render(grim::graphics::SpriteBatch& spriteBatch);
    virtual void Consume(Obelisk* obelisk);

private:
    ItemType m_type;
};
