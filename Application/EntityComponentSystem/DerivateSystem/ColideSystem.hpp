#pragma once

#include <vector>
#include <iostream>
#include "SystemBase.hpp"
#include "Component.hpp"
#include "Entities.hpp"
#include "HitboxComponent.hpp"
#include "PositionComponent.hpp"
#include "TeamComponent.hpp"
#include "DirectionComponent.hpp"
#include "BonusComponent.hpp"
#include "IEvent.hpp"

class ColideSystem : public SystemBase
{
private:
    std::vector<PositionComponent *> *m_position;
    std::vector<HitboxComponent *> *m_hitbox;
    std::vector<TeamComponent *> *m_team;
    std::vector<BonusComponent *> *m_bonus;

public:
    ColideSystem() : SystemBase(400) {};
    void init(std::vector<PositionComponent *> *pos){m_position = pos;};
    void init(std::vector<HitboxComponent *> *hitbox) { m_hitbox = hitbox;};
    void init(std::vector<TeamComponent *> *team) { m_team = team; };
    void init(std::vector<BonusComponent *> *bonus) { m_bonus = bonus; };
    void checkColide(int, int, EventManager &);
    virtual ~ColideSystem() = default;
    virtual void update(EventManager &eventManager, std::vector<Entities> &);
    virtual void dump() { std::cout << "ColideSystem" << std::endl;}
    static SystemBase *Create() { return new ColideSystem(); }
};