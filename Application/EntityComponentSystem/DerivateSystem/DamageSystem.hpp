#pragma once

#include <vector>
#include <iostream>
#include "SystemBase.hpp"
#include "Component.hpp"
#include "Entities.hpp"
#include "PowerDamageComponent.hpp"
#include "HeartPointComponent.hpp"

    class DamageSystem : public SystemBase
{
private:
    std::vector<PowerDamageComponent *> *m_damage;
    std::vector<HearthPointComponent *> *m_heartPoint;
public:
    DamageSystem() : SystemBase(100) {};
    void init(std::vector<PowerDamageComponent *> *damage){m_damage = damage;};
    void init(std::vector<HearthPointComponent *> *heartPoint) {m_heartPoint = heartPoint;};
    virtual ~DamageSystem() = default;
    virtual void update(EventManager &eventManager, std::vector<Entities> &);
    virtual void update(EventManager &eventManager, int dealer, int taker);
    virtual void dump() { std::cout << "DamageSystem" << std::endl;}
    static SystemBase *Create() { return new DamageSystem(); }
};