#pragma once

#include <iostream>
#include "Component.hpp"

class BonusComponent : public Components
{
public:
    bool m_bonus;
public:
    BonusComponent() = default;
    BonusComponent(int id) : Components(id, getCompId()){};
    virtual ~BonusComponent() = default;
    static Components *Create(const int &id) { return new BonusComponent(id); };
    virtual void modify(bool Bonus) { m_bonus = Bonus; }
    virtual void dump() { std::cout << "Bonus = " << m_bonus << std::endl; }
    virtual Components *clone() { return new BonusComponent(*this); }
    int getEntityId() const { return m_entityId; }
    static int getCompId() { return 5; };
};