#pragma once
#include "PCH.hpp"

class Entity;

class EntityManager
{
    public:
        EntityManager();
        ~EntityManager();

        std::vector<Entity*> GetEntities() const;
        template<typename T> T* GetEntityOfType() const;
        template<typename T> std::vector<T*> GetEntitiesOfType() const;

        void Update();
        void Render();
        void RegisterEntity(Entity* entity);

    private:
        std::vector<Entity*> m_entities;
};

template<class T>
T* EntityManager::GetEntityOfType() const
{
    for (std::vector< Entity* >::const_iterator it = m_entities.begin(); it != m_entities.end(); it++)
    {
        T* e = dynamic_cast<T*>(*it);
        if (e != nullptr)
        {
            return e;
        }
    }

    return nullptr;
}

template<class T>
std::vector<T*> EntityManager::GetEntitiesOfType() const
{
    std::vector<T*> ret;
    for (std::vector< Entity* >::const_iterator it = m_entities.begin(); it != m_entities.end(); it++)
    {
        T* e = dynamic_cast<T*>(*it);
        if (e != nullptr)
        {
            ret.push_back(e);
        }
    }

    return ret;
}