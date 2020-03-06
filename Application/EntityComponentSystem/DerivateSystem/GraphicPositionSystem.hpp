#pragma once

#include "SystemBase.hpp"
#include "DrawableObjectComponent.hpp"

class GraphicPositionSystem : public SystemBase
{
private:
    std::vector<DrawableObjComponent *> *m_object;
    std::vector<PositionComponent *> *m_pos;

public:
    GraphicPositionSystem() : SystemBase(2){};
    ~GraphicPositionSystem() = default;

    virtual void init(std::vector<PositionComponent *> *obj) { m_pos = obj; };
    virtual void init(std::vector<DrawableObjComponent *> *obj) { m_object = obj; };
    virtual void update(EventManager &, std::vector<Entities> &);
    virtual void dump() { std::cout << "GraphicPositionSystem" << std::endl; }

    static SystemBase *Create() { return new GraphicPositionSystem(); }
};
