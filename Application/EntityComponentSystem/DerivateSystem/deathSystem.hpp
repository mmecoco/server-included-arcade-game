#pragma once

#include <vector>
#include <iostream>
#include "SystemBase.hpp"
#include "Component.hpp"
#include "Entities.hpp"
#include "HeartPointComponent.hpp"

class deathSystem : public SystemBase
{
private:
    std::vector<HearthPointComponent *> *m_heartPoint;
public:
    deathSystem() : SystemBase(300) {};
    void init(std::vector<HearthPointComponent *> *heartPoint)
    {
        m_heartPoint = heartPoint;
    }
    virtual ~deathSystem() = default;
    virtual void update(EventManager &eventManager, std::vector<Entities> &);
    virtual void dump() { std::cout << "deathSystem" << std::endl;}
    static SystemBase *Create() { return new deathSystem(); }
};