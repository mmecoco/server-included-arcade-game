#include "DamageSystem.hpp"

void DamageSystem::update(EventManager &eventManager, int dealer, int taker)
{
    for (auto &it : *m_damage)
    {
        for (auto &it2 : *m_heartPoint)
        {
            if (it2->getEntityId() == taker && it->getEntityId() == dealer || (it->getEntityId() == taker && it2->getEntityId() == dealer)) {
                it2->m_HearthPoint -= it->m_PowerDamage;
            }
        }
    }
}

void DamageSystem::update(EventManager &eventManager, std::vector<Entities> &entity)
{

}