#pragma once

#include <iostream>
#include "Component.hpp"

class PositionComponent : public Components
{
public:
    float x;
    float y;
public:
    PositionComponent() = default;
    PositionComponent(int id) : Components(id, getCompId()) {
        std::cout << "CREATION COMP POSITION" << std::endl;
    };
    virtual ~PositionComponent() = default;
    static Components *Create(const int &id) { return new PositionComponent(id); };
    virtual void modify(float mx, float my) { 
        std::cout << "MODIFICATION COMP POSITION" << std::endl;
        x = mx;
        y = my;
    };
    virtual void modify(std::vector<float> value)
    {
        std::cout << "MODIFICATION COMP POSITION" << std::endl;
        x = value[0];
        y = value[1];
    };
    virtual void dump()
    {
        std::cout << "x = " << x << std::endl;
        std::cout << "y = " << y << std::endl;
    }
    virtual Components *clone()
    {
        std::cout << "CREATION COPY COMP POSITION" << std::endl;
        return new PositionComponent(*this);
    }
    int getEntityId() const { return m_entityId; };
    static int getCompId() { return 0; };
};
