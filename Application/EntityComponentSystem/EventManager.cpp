#include "EventManager.hpp"

void EventManager::push(IEvent *event)
{
    m_eventQueue.push(event);
}

IEvent *EventManager::processEvent()
{
    IEvent *event = m_eventQueue.front();
    m_eventQueue.pop();
    return event;
}

int EventManager::getTypeFirstEvent()
{
    return m_eventQueue.front()->getId();
}