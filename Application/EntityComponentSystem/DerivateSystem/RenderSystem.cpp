#include "RenderSystem.hpp"

void RenderSystem::update(EventManager &eventManager, std::vector<Entities> &entities)
{
    // std::cout << "SIZE DRAW = " << m_object->size() << std::endl;
    for (auto &i : *m_object)
    {
        // std::cout << "ID = " << i->getEntityId() << std::endl;
        m_api->Draw(i->m_obj.get());
    }
}