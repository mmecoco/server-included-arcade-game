#include "EndGameSystem.hpp"

void EndGameSystem::update(EventManager &eventManager, std::vector<Entities> &entity)
{
    for (auto &it : *m_playable)
    {
        std::cout << std::boolalpha << it->m_playable << std::endl;
        if (it->m_playable == true)
        {
            for (auto &it2 : *m_heartPoint)
            {
                if (it->getEntityId() == it2->getEntityId() && it2->m_HearthPoint > 0)
                    return;
            }
        }
    }
    endGame = true;
    eventManager.push((IEvent *)new EndGameEvent(true));
}