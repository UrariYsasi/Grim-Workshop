#pragma once
#include "Prop.hpp"

class Monster;

class Resource : public Prop
{
public:
    Resource(Game* game, Vector2D position, ItemType item);
    virtual ~Resource();

    virtual ItemType GetItem() const = 0;

    virtual void Update(double deltaTime) = 0;
    virtual void Render() = 0;

protected:
    ItemType m_item;
};
