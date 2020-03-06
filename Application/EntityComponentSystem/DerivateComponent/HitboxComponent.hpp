#pragma once

#include <iostream>
#include "Component.hpp"



class HitboxComponent : public Components
{
public:
    float m_up;
    float m_down;
    float m_forward;
    float m_backward;

public:
    HitboxComponent() = default;
    HitboxComponent(int id) : Components(id, getCompId()) {
        std::cout << "CREATION COMP Hitbox" << std::endl;
    };
    virtual ~HitboxComponent() = default;
    static Components *Create(const int &id) { return new HitboxComponent(id); };
    virtual void modify(std::vector<float> hitbox) 
    { 
        std::cout << "MODIFICATION COMP Hitbox" << std::endl;
        m_up = hitbox[0];
        m_down = hitbox[1];
        m_forward = hitbox[2];
        m_backward = hitbox[3];
    };
    virtual void modify(float up, float down, float forward, float backward)
    {
        std::cout << "MODIFICATION COMP Hitbox" << std::endl;
        m_up = up;
        m_down = down;
        m_forward = forward;
        m_backward = backward;
    };
    virtual void dump()
    {
        std::cout << "up = " << m_up << std::endl;
        std::cout << "DOWN = " << m_down << std::endl;
        std::cout << "FORWARD = " << m_forward << std::endl;
        std::cout << "BACKWARD = " << m_backward << std::endl;
    }
    virtual Components *clone()
    {
        std::cout << "CREATION COPY COMP Hitbox" << std::endl;
        return new HitboxComponent(*this);
    }
    int getEntityId() const { return m_entityId; };
    static int getCompId() { return 19; };
};
