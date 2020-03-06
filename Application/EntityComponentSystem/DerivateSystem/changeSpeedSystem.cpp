#include "changeSpeedSystem.hpp"

void changeSpeedSystem::update(EventManager &a, std::vector<Entities> &b)
{
    for (auto &i : *m_input)
    {
        for (auto &j : *m_velocity)
        {
            for (auto &k : *m_Direction)
            {
                if (i->getEntityId() == j->getEntityId() && j->getEntityId() == k->getEntityId())
                {
                    if (in[i->m_input] == -1)
                    {
                        (j->m_Velocity > 0.5) ? j->m_Velocity -= 0.5 : j->m_Velocity = 0;
                        return;
                    }
                    if (k->m_Direction == in[i->m_input]) {
                        if (j->m_Velocity < 5)
                            j->m_Velocity += 0.3;
                        else
                            j->m_Velocity = 5;
                    }
                    else if (in[i->m_input] != k->m_Direction)
                    {
                        k->m_Direction = in[i->m_input];
                        j->m_Velocity = 0;
                    }
                }
            }
        }
    }
}
