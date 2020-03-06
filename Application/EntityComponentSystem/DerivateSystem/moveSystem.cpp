#include "moveSystem.hpp"

void moveSystem::update(EventManager &eventManager, std::vector<Entities> &entities)
{
    m_elapsedTime = 2000;
    for (auto &i : *m_position)
    {
        for (auto &j : *m_velocity)
        {
            if (i->getEntityId() == j->getEntityId())
            {
                for (auto &k : *m_direction)
                {
                    if (j->getEntityId() == k->getEntityId()) 
                    {
                        for (auto &it : *m_player)
                            if (j->getEntityId() == it->getEntityId())
                            {
                                std::cout << m_elapsedTime << std::endl;
                                // std::cout << "cos x" << cos(k->m_Direction) << std::endl;
                                auto tmp_x = i->x + (j->m_Velocity * (m_elapsedTime / 1000)) * cos(k->m_Direction * M_PI / 180);
                                auto tmp_y = i->y + (j->m_Velocity * (m_elapsedTime / 1000)) * sin(k->m_Direction * M_PI / 180);
                                if (!it->m_playable && ((tmp_x > 1920 || tmp_x < 0) || (tmp_y > 1000 || tmp_y < 0))){
                                    for (auto &it2 : entities)
                                        if (it->getEntityId() == it2.getId()) {
                                            eventManager.push((IEvent *)new KillEntityEvent(it2));
                                        }
                                }
                                else {
                                    i->x = tmp_x > 1920 || tmp_x < 0 ? i->x : tmp_x;
                                    i->y = tmp_y > 1000 || tmp_y < 0 ? i->y : tmp_y;
                                }
                            }
                    }
                }
            }
        }
    }
}
