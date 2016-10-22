#pragma once
#include "Entity.hpp"

class Monster;

class Resource : public Entity
{
public:
    Resource(Game* game, const glm::vec3& position, EntityID ID, ItemType item);
    virtual ~Resource();

    virtual ItemType GetItem() const = 0;
    bool IsFull();

    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;
    void AddPeon();
    void RemovePeon();

protected:
    const static int ENT_PEON_LIMIT = 3;

    ItemType m_item;
    int m_peonCount;
    int m_peonLimit;
};
