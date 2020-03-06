#include "GraphicPositionSystem.hpp"

void GraphicPositionSystem::update(EventManager &a, std::vector<Entities> &b)
{
    for (auto &i: *m_object)
    {
        for (auto &j : *m_pos)
        {
            if (j->getEntityId() == i->getEntityId())
            {
                i->m_obj->setPosition((float)j->x, (float)j->y);
            }
        }
    }
}