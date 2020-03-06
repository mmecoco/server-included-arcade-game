#include "attributeInputSystem.hpp"

void attributeInputSystem::update(EventManager &a, std::vector<Entities> &b)
{
    for (auto &i : *m_input)
    {
        i->modify(m_api->getInput());
    }
}