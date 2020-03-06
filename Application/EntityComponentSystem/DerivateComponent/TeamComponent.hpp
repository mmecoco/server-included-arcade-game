#pragma once

#include <iostream>
#include <memory>
#include "Component.hpp"

class TeamComponent : public Components
{
public:
    bool m_isTeam;
public:
    TeamComponent(int id) : Components(id, getCompId()) {};
    virtual ~TeamComponent() = default;
    static Components *Create(const int &id) { return new TeamComponent(id); };
    virtual void modify(bool isTeam)
    {
        // if isTeam is true, missile won't touch allies
        m_isTeam = isTeam;
    };
    virtual void dump() {}
    int getEntityId() const { return m_entityId; };
    virtual Components *clone()
    {
        std::cout << "CREATION COPY Team" << std::endl;
        return new TeamComponent(*this);
    }
    static int getCompId() { return 18; };
};
