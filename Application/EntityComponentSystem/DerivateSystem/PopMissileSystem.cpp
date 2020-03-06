#include "PopMissileSystem.hpp"

void PopMissilesystem::update(EventManager &eventManager, std::vector<Entities> &a)
{
    for (auto &i : *m_input)
    {
        if (i->m_input == Eligos::input_keys::SPACE)
        {
            for (auto &j : *m_position)
            {
                if (j->getEntityId() == i->getEntityId())
                {
                    for (auto &k : *m_shootRate) {

                        if (k->getEntityId() == i->getEntityId())
                        {
                            if (k->m_clock.getClock().count() > k->m_time) {
                                IEvent *event(new MissileEvent({j->x, j->y}, j->getEntityId()));
                                eventManager.push(event);
                                k->m_clock.restart();
                            }
                        }
                    }
                }
            }
        }
    }
}