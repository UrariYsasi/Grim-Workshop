#pragma once
#include "Prop.hpp"

class Resource : public Prop
{
public:
    enum Type { NONE, TREE };

    Resource(Game* game, Vector2D position, Type type);
    virtual ~Resource();

    Type GetType() const;

    virtual void Update(double deltaTime) = 0;
    virtual void Render() = 0;

protected:
    Type m_type;
};
