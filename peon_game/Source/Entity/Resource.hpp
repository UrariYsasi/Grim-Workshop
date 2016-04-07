#pragma once
#include "Prop.hpp"

class Monster;

class Resource : public Prop
{
public:
    Resource(Game* game, const glm::vec2& position, int entityID, ItemType item);
    virtual ~Resource();

    virtual ItemType GetItem() const = 0;
    bool IsFull();

    virtual void Update(float deltaTime) = 0;
    virtual void Render(grim::graphics::SpriteBatch& spriteBatch) = 0;
    void AddPeon();
    void RemovePeon();

protected:
    const static int PEON_LIMIT = 3;

    ItemType m_item;
    int m_peonCount;
    int m_peonLimit;
};