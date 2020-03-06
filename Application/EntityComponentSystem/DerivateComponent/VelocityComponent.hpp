#pragma once

#include <iostream>
#include "Component.hpp"

class VelocityComponent : public Components
{
public:
    float m_Velocity;
public:
    VelocityComponent() = default;
    VelocityComponent(int id) : Components(id, getCompId()){};
    virtual ~VelocityComponent() = default;
    static Components *Create(const int &id) { return new VelocityComponent(id); };
    virtual void modify(float Velocity) { m_Velocity = Velocity; }
    virtual void dump() { std::cout << "Velocity = " << m_Velocity << std::endl; }
    virtual Components *clone() { return new VelocityComponent(*this); }
    int getEntityId() const { return m_entityId; }
    static int getCompId() { return 1; };
};