#include "PCH.hpp"
#include "EntityManager.hpp"
#include "Entity.hpp"

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
    std::vector<Entity*>::iterator it;
    for (it = m_entities.begin(); it != m_entities.end(); it++)
    {
        delete (*it);
    }
    m_entities.clear();
}

std::vector<Entity*> EntityManager::GetEntities() const
{
    return m_entities;
}

void EntityManager::Update()
{
    std::vector<Entity*>::const_iterator it;
    for (it = m_entities.begin(); it != m_entities.end(); it++)
    {
        (*it)->Update();
    }
}

void EntityManager::Render()
{
    std::vector<Entity*>::const_iterator it;
    for (it = m_entities.begin(); it != m_entities.end(); it++)
    {
        (*it)->Render();
    }
}

void EntityManager::RegisterEntity(Entity* entity)
{
    m_entities.push_back(entity);
}