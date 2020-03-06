#pragma once

#include <iostream>
#include "Component.hpp"

class HearthPointComponent : public Components
{
public:
    int m_HearthPoint;
public:
    HearthPointComponent() = default;
    HearthPointComponent(int id) : Components(id, getCompId()){};
    virtual ~HearthPointComponent() = default;
    static Components *Create(const int &id) {return new HearthPointComponent(id);};
    virtual void modify(int HearthPoint) { m_HearthPoint = HearthPoint; };
    virtual void dump() { std::cout << "HearthPoint = " << m_HearthPoint << std::endl;};
    virtual Components *clone() { return new HearthPointComponent(*this); }
    int getEntityId() const { return m_entityId; }
    static int getCompId() { return 3;};
};
//12 15 1 4 8 14 7 2 0 19 13
//6 7 9 10 11 13 14 16