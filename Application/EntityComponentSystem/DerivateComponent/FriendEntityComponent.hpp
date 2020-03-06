#pragma once

#include <iostream>
#include <memory>
#include "Component.hpp"

class FriendEntityComponent : public Components
{
public:
    int m_idFriend;
public:
    FriendEntityComponent(int id) : Components(id, getCompId()) {};
    virtual ~FriendEntityComponent() = default;
    static Components *Create(const int &id) { return new FriendEntityComponent(id); };
    virtual void modify(int idFriend)
    {
        // if idFriend is true, missile won't touch allies
        m_idFriend = idFriend;
    };
    virtual void dump() {}
    int getEntityId() const { return m_entityId; };
    virtual Components *clone()
    {
        std::cout << "CREATION COPY FriendEntityComponent" << std::endl;
        return new FriendEntityComponent(*this);
    }
    static int getCompId() { return 17; };
};
