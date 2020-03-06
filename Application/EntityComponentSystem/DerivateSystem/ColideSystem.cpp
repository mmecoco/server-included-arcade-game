#include "ColideSystem.hpp"

void ColideSystem::checkColide(int indexposition, int indexhitbox, EventManager &eventManager)
{
    float y_top = ((*m_position)[indexposition])->y - ((*m_hitbox)[indexhitbox])->m_up;
    float y_bot = ((*m_position)[indexposition])->y + ((*m_hitbox)[indexhitbox])->m_down;
    float x_left = ((*m_position)[indexposition])->x - ((*m_hitbox)[indexhitbox])->m_backward;
    float x_right =((*m_position)[indexposition])->x + ((*m_hitbox)[indexhitbox])->m_forward;

    for (auto it = indexposition + 1; it < m_position->size(); it++)
    {
        for (auto &it2 : *m_hitbox)
        {
            if(it2->getEntityId() == ((*m_position)[it])->getEntityId())
            {
                for (auto &it3: *m_bonus)
                {
                    if (it3->getEntityId() == ((*m_position)[it])->getEntityId())
                    {
                        if (y_top <= (((*m_position)[it])->y - it2->m_up) && y_bot >= (((*m_position)[it])->y + it2->m_down)
                        && x_left <= (((*m_position)[it])->x - it2->m_backward) && x_right >= (it2->m_forward + ((*m_position)[it])->x)
                        && (it3->m_bonus != ((*m_bonus)[indexhitbox])->m_bonus))
                        {
                            eventManager.push((IEvent *)new BonusEvent(it3->m_bonus));
                        }
                    }
                }
                for (auto &it3 : *m_team)
                {
                    if (it3->getEntityId() == ((*m_position)[it])->getEntityId())
                    {
                        if (y_top <= (((*m_position)[it])->y - it2->m_up) && y_bot >= (((*m_position)[it])->y + it2->m_down) 
                        && x_left <= (((*m_position)[it])->x -it2->m_backward) && x_right >= (it2->m_forward + ((*m_position)[it])->x) 
                        && (it3->m_isTeam != ((*m_team)[indexhitbox])->m_isTeam))
                        {
                            std::cout << y_top << "  " << y_bot << std::endl;
                            std::cout << x_left << "  " << x_right << std::endl;
                            std::cout << ((*m_position)[it])->y - it2->m_up << "  " << ((*m_position)[it])->y + it2->m_down << std::endl;
                            std::cout <<  ((*m_position)[it])->x - it2->m_backward << "  " << it2->m_forward + ((*m_position)[it])->x << std::endl;
                            eventManager.push((IEvent *)new DamageEvent(it2->getEntityId(), ((*m_hitbox)[indexhitbox])->getEntityId()));
                        }
                    }
                
                }
            }
        }
    }
}

void ColideSystem::update(EventManager &eventManager, std::vector<Entities> &entities)
{
    for (auto it = 0; it <= (m_position->size() - 1) && m_position->size(); it++) 
    {
        for (auto it2 = 0; it2 < (m_hitbox->size()); it2++)
            if (((*m_hitbox)[it2])->getEntityId() == ((*m_position)[it])->getEntityId()){
                std::cout << ((*m_hitbox)[it2])->getEntityId() << std::endl;
                checkColide(it, it2, eventManager);
            }
    }
}
