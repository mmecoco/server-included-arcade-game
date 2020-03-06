#include "Entities.hpp"

void Entities::clear()
{
    m_listOfComp.reset();
    m_id = -1;
}

void Entities::setId(int id)
{
    m_id = id;
}

bool Entities::hasComponent(int idOfComponent) const
{
    return m_listOfComp.test(idOfComponent);
}

bool Entities::addComponent(int idOfComponent)
{
    if (!m_listOfComp.test(idOfComponent))
    {
        m_listOfComp.flip(idOfComponent);
        return true;
    }
    return false;
}

bool Entities::removeAllComponent()
{
    m_listOfComp.reset();
    return true;
}

bool Entities::removeComponent(int idOfComponent)
{
    if (m_listOfComp.test(idOfComponent))
    {
        m_listOfComp.flip(idOfComponent);
        return true;
    }
    return false;
}

const ComponentList Entities::getComponents() const
{
    return m_listOfComp;
}