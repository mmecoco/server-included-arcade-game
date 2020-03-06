#pragma once

#include <memory>
#include <map>
#include "InputComponent.hpp"
#include "DirectionComponent.hpp"
#include "VelocityComponent.hpp"
#include "SystemBase.hpp"

using namespace Eligos;

class changeSpeedSystem : public SystemBase
{
private:
    std::vector<VelocityComponent *> *m_velocity;
    std::vector<DirectionComponent *> *m_Direction;
    std::vector<InputComponent *> *m_input;
    // std::vector<InputComponent *> *m_input;
    std::map<input_keys, float> in = {
        {input_keys::UNKNOW, -1},
        {input_keys::DIAG_1, -45},
        {input_keys::DIAG_2, -135},
        {input_keys::DIAG_3, 135},
        {input_keys::DIAG_4, 45},
        {input_keys::D, 0},
        {input_keys::W, -90},
        {input_keys::A, 180},
        {input_keys::S, 90},
        {input_keys::S, -1},
        {input_keys::Q, -1},
        {input_keys::E, -1},
        {input_keys::SPACE, -1},
        {input_keys::LEFT, 180},
        {input_keys::UP, -90},
        {input_keys::RIGHT, 0},
        {input_keys::DOWN, 90},
    };

public:
    changeSpeedSystem() : SystemBase(6){};
    ~changeSpeedSystem() = default;

    virtual void init(std::vector<InputComponent *> *obj) { m_input = obj; };
    virtual void init(std::vector<VelocityComponent *> *obj) { m_velocity = obj; };
    virtual void init(std::vector<DirectionComponent *> *obj) { m_Direction = obj; };
    virtual void update(EventManager &, std::vector<Entities> &);
    virtual void dump() { std::cout << "changeSpeedSystem" << std::endl; }

    static SystemBase *Create() { return new changeSpeedSystem(); }
};
