#pragma once

#include "Component.hpp"
#include <iostream>

class DirectionComponent : public Components
{
public:
    float m_Direction;

public:
    DirectionComponent() = default;
    DirectionComponent(float Direction) : m_Direction(Direction){};
    DirectionComponent(int id) : Components(id, getCompId()){};
    virtual ~DirectionComponent() = default;
    static Components *Create(const int &id) { return new DirectionComponent(id); };
    virtual void modify(float Direction) { m_Direction = Direction; }
    virtual void dump() { std::cout << "Direction = " << m_Direction << std::endl; }
    virtual Components *clone() { return new DirectionComponent(*this); }
    int getEntityId() const { return m_entityId; }
    static int getCompId() { return 4; };
};