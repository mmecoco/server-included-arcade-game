#pragma once

#include <string>
#include "Entities.hpp"

enum type_event {CREATE_ENTITY, KILL_ENTITY, DAMAGE, ENDGAME, BONUS};
class IEvent
{
public:
    int m_id;
    type_event m_type;
    IEvent(type_event type, int id) : m_type(type), m_id(id) {}
    virtual int getId() const = 0;
    virtual ~IEvent() = default;
};

class DamageEvent : public IEvent
{
private:
public:
    int m_dealerId;
    int m_takerId;
public:
    DamageEvent(int dealerId, int takerId ) : IEvent(type_event::DAMAGE, 4)
    {
        m_dealerId = dealerId;
        m_takerId = takerId;
    };
    virtual ~DamageEvent() = default;
    virtual int getId() const { return m_id; };
};

class BonusEvent : public IEvent
{
private:
public:
    bool m_bonus;

public:
    BonusEvent(bool bonus) : IEvent(type_event::BONUS, 6)
    {
        m_bonus = bonus;
    };
    virtual ~BonusEvent() = default;
    virtual int getId() const { return m_id; };
};

class EndGameEvent : public IEvent
{
private:
public:
    bool m_endGame;

public:
    EndGameEvent(bool endGame) : IEvent(type_event::ENDGAME, 5)
    {
        m_endGame = endGame;
    };
    virtual ~EndGameEvent() = default;
    virtual int getId() const { return m_id; };
};

class KillEntityEvent : public IEvent
{
private:
public:
    Entities m_entity;

public:
    KillEntityEvent(Entities entity) : IEvent(type_event::KILL_ENTITY, 3), m_entity(entity){};
    virtual ~KillEntityEvent() = default;
    virtual int getId() const { return m_id; };
};

class MissileEvent : public IEvent
{
private:
public:
    std::vector<float> m_pos;
    int m_entity_id;
    std::string path = "../ScriptFile/Scene0/missile1Entity.json";

public:
    MissileEvent(std::vector<float> pos, int entity_id) : IEvent(type_event::CREATE_ENTITY, 2)
    {
        m_pos = pos;
        m_entity_id = entity_id;
    };
    virtual ~MissileEvent() = default;
    virtual int getId() const { return m_id; };
};
