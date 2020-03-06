#pragma once

#include <queue>
#include "IEvent.hpp"

class EventManager
{
private:
    std::queue<IEvent *> m_eventQueue;
public:
    EventManager() = default;
    virtual ~EventManager() = default;
public:
    void push(IEvent *);
    int getTypeFirstEvent();
    IEvent *processEvent();
    int size() { return m_eventQueue.size(); };
    const bool isEmpty() const { return m_eventQueue.empty(); };
};