#pragma once

#include <iostream>
#include "Component.hpp"
#include "Clock.hpp"

class ShootRateComponent : public Components
{
public:
    Clock m_clock;
    float m_time;
public:
    ShootRateComponent() = default;
    ShootRateComponent(int id) : Components(id, getCompId()){};
    virtual ~ShootRateComponent() = default;
    static Components *Create(const int &id) { return new ShootRateComponent(id); };
    virtual void modify(float a) { m_time = a; }
    virtual void dump() { std::cout << "PowerDamage = " << m_clock.getClock().count() << std::endl; }
    virtual Components *clone() { return new ShootRateComponent(*this); }
    int getEntityId() const { return m_entityId; }
    static int getCompId() { return 16; };
};