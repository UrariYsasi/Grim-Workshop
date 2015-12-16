#pragma once
#include "PCH.hpp"

class Entity;

class EntityManager
{
    public:
        EntityManager();
        ~EntityManager();

        void Update();
        void Render();
        void RegisterEntity(Entity* entity);
        template<typename T> std::vector<T*> GetEntitiesOfType();

    private:
        std::vector<Entity*> m_entities;
};

template<class T>
std::vector<T*> EntityManager::GetEntitiesOfType()
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