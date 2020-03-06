#pragma once

#include <vector>
#include <iostream>
#include "SystemBase.hpp"
#include "Component.hpp"
#include "Entities.hpp"
#include "DerivateComponent/PositionComponent.hpp"
#include "DerivateComponent/VelocityComponent.hpp"
#include "DerivateComponent/DirectionComponent.hpp"
#include "TeamComponent.hpp"
#include "PlayableComponent.hpp"
#include "Clock.hpp"

class moveSystem : public SystemBase
{
private:
    using Duration = std::chrono::duration<double_t, std::milli>;
    Clock m_Clock;
    std::vector<PositionComponent *> *m_position;
    std::vector<VelocityComponent *> *m_velocity;
    std::vector<DirectionComponent *> *m_direction;
    std::vector<PlayableComponent *> *m_player;
    std::vector<TeamComponent *> *m_team;

    double_t m_elapsedTime = m_Clock.getClock().count();
public:
    moveSystem() : SystemBase(1) {};
    void init(std::vector<PositionComponent *> *pos)
    {
        m_position = pos;
    }
    void init(std::vector<VelocityComponent *> *pos)
    {
        m_velocity = pos;
    }
    void init(std::vector<DirectionComponent *> *pos)
    {
        m_direction = pos;
    }
    void init(std::vector<TeamComponent *> *team)
    {
        m_team = team;
    }
    void init(std::vector<PlayableComponent *> *player)
    {
        m_player = player;
    }
    virtual ~moveSystem() = default;
    virtual void update(EventManager &eventManager, std::vector<Entities> &);
    virtual void dump() { std::cout << "MoveSystem" << std::endl;}
    static SystemBase *Create() { return new moveSystem(); }
};