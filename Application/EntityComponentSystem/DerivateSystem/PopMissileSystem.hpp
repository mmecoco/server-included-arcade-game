#pragma once

#include <vector>
#include <iostream>
#include "SystemBase.hpp"
#include "Component.hpp"
#include "Entities.hpp"
#include "InputComponent.hpp"
#include "PositionComponent.hpp"
#include "ShootRateComponent.hpp"

class PopMissilesystem : public SystemBase
{
private:
    std::vector<PositionComponent *> *m_position;
    std::vector<InputComponent *> *m_input;
    std::vector<ShootRateComponent *> *m_shootRate;
public:
    PopMissilesystem() : SystemBase(11) {};
    virtual ~PopMissilesystem() = default;
    
    void init(std::vector<PositionComponent *> *pos)
    {
        m_position = pos;
    }
    void init(std::vector<InputComponent *> *pos)
    {
        m_input = pos;
    }
    void init(std::vector<ShootRateComponent *> *pos)
    {
        m_shootRate = pos;
    }
    virtual void update(EventManager &eventManager, std::vector<Entities> &);
    virtual void dump() { std::cout << "MoveSystem" << std::endl; }
    static SystemBase *Create() { return new PopMissilesystem(); }
};