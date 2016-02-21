#pragma once
#include "Prop.hpp"

class Monster;

class Resource : public Prop
{
public:
    Resource(Game* game, Vector2D position, int entityID, ItemType item);
    virtual ~Resource();

    virtual ItemType GetItem() const = 0;
    bool IsFull();

    virtual void Update(double deltaTime) = 0;
    virtual void Render() = 0;
    void AddPeon();
    void RemovePeon();

protected:
    const static int PEON_LIMIT = 3;

    ItemType m_item;
    int m_peonCount;
    int m_peonLimit;
};
