#include "EntitiesFactory.hpp"
#include <iostream>


Entities EntitiesFactory::CreateComponent()
{
    Entities new_entity(-1);
    int i = 0;

    for (; m_FactoryId.find(i) != m_FactoryId.end(); i++);
    new_entity.setId(i);
    m_FactoryId.insert(i);
    return new_entity;
}

void EntitiesFactory::DeleteComponent(int id)
{
    m_FactoryId.erase(m_FactoryId.find(id));
}