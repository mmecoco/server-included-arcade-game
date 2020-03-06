#pragma once

#include "Component.hpp"

class PlayableComponent : public Components
{
public:
    bool m_playable;

public:
    PlayableComponent(int id) : Components(id, getCompId()){};
    virtual ~PlayableComponent() = default;
    static Components *Create(const int &id) { return new PlayableComponent(id); };
    virtual void modify(bool playable)
    {
        m_playable = playable;
    };
    virtual void dump() {}
    virtual Components *clone()
    {
        return new PlayableComponent(*this);
    }
    int getEntityId() const { return m_entityId; };
    static int getCompId() { return 8; };
};
