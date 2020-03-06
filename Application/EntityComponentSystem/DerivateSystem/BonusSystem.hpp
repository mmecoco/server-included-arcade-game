#pragma once

#include <vector>
#include <iostream>
#include "SystemBase.hpp"
#include "Component.hpp"
#include "Entities.hpp"
#include "HeartPointComponent.hpp"
#include "BonusComponent.hpp"

class bonusSystem : public SystemBase
{
private:
    std::vector<BonusComponent *> *m_bonus;
    std::vector<HearthPointComponent *> *m_lifePoint;
    std::vector<PositionComponent *> *m_position;

public:
    bonusSystem() : SystemBase(200) {};
    void init(std::vector<BonusComponent *> *Bonus)
    {
        m_bonus = Bonus;
    }
    void init(std::vector<HearthPointComponent *> *lifePoint)
    {
        m_lifePoint = lifePoint;
    }
    void init(std::vector<PositionComponent *> *position)
    {
        m_position = position;
    }
    virtual ~bonusSystem() = default;
    virtual void update(EventManager &eventManager, std::vector<Entities> &);
    virtual void update(EventManager &eventManager, bool);
    virtual void dump() { std::cout << "bonusSystem" << std::endl;}
    static SystemBase *Create() { return new bonusSystem(); }
};