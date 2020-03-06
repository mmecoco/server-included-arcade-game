 #include "deathSystem.hpp"

void deathSystem::update(EventManager &eventManager, std::vector<Entities> &entity)
{
    for (auto &it : *m_heartPoint)
    {
        if (it->m_HearthPoint <= 0) {
            for (auto &it2 : entity) {
                if (it2.getId() == it->getEntityId()) {
                    eventManager.push((IEvent *) new KillEntityEvent(it2));
                }
            }
        }
    }
}