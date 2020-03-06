#pragma once

#include <vector>
#include <algorithm>
#include "Entities.hpp"
#include "DerivateComponent/PositionComponent.hpp"
#include "EventManager.hpp"

using Entity = int;

class SystemBase
{
private:
    int m_id;
public:
    SystemBase(int id) : m_id(id){};
    virtual ~SystemBase() = default;
    virtual void update(EventManager &eventManager, std::vector<Entities> &m_entities) = 0;
    virtual void dump() = 0;
    int getId() const { return m_id; };
    // virtual void init(int index, std::vector<Components *> pos) = 0;

};
