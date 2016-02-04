#pragma once
#include "Prop.hpp"

class Resource : public Prop
{
public:
    Resource(Game* game, Vector2D position, ItemType type);
    virtual ~Resource();

    ItemType GetType() const;

    virtual void Update(double deltaTime) = 0;
    virtual void Render() = 0;

protected:
    ItemType m_type;
};
