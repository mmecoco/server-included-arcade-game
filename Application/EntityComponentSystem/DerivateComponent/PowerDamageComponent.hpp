#pragma once

#include <iostream>
#include "Component.hpp"

class PowerDamageComponent : public Components
{
public:
    uint16_t m_PowerDamage;
public:
    PowerDamageComponent() = default;
    PowerDamageComponent(int id) : Components(id, getCompId()){};
    virtual ~PowerDamageComponent() = default;
    static Components *Create(const int &id) { return new PowerDamageComponent(id); };
    virtual void modify(uint16_t PowerDamage) { m_PowerDamage = PowerDamage; }
    virtual void dump() { std::cout << "PowerDamage = " << m_PowerDamage << std::endl; }
    virtual Components *clone() { return new PowerDamageComponent(*this); }
    int getEntityId() const { return m_entityId; }
    static int getCompId() { return 10; };
};