#pragma once

#include <vector>
#include <iostream>
#include "SystemBase.hpp"
#include "Component.hpp"
#include "Entities.hpp"
#include "HeartPointComponent.hpp"
#include "PlayableComponent.hpp"

class EndGameSystem : public SystemBase
{
private:
    std::vector<HearthPointComponent *> *m_heartPoint;
    std::vector<PlayableComponent *> *m_playable;
    bool endGame = false;

public:
    EndGameSystem() : SystemBase(500) {};
    void init(std::vector<HearthPointComponent *> *heartPoint)
    {
        m_heartPoint = heartPoint;
    }
    void init(std::vector<PlayableComponent *> *playable)
    {
        m_playable = playable;
    }
    virtual ~EndGameSystem() = default;
    virtual void update(EventManager &eventManager, std::vector<Entities> &);
    virtual void dump() { std::cout << "EndGameSystem" << std::endl; }
    static SystemBase *Create() { return new EndGameSystem(); }
};