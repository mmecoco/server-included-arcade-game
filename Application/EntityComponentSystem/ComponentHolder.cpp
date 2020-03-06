#include "ComponentHolder.hpp"

// template <typename... Args>
// void ComponentHolder::addComponent(Entities &entity, int idOfComp, Args &&... args)
// {
//     entity.addComponent(idOfComp);
//     compValue tmp = {idOfComp, ComponentFactory::Get()->CreateComponent(idOfComp)};
//     tmp.second->modify(args ...);
//     m_Holder.insert({entity.getId(), tmp});
// }

void ComponentHolder::removeComponent(Entities &entity, int idOfComp)
{
    entity.removeComponent(idOfComp);

    for (auto &i : m_Holder) {
        for (auto k = 0; k < i->size(); k++) {
            if (idOfComp == (*i)[k]->getId() && entity.getId() == (*i)[k]->getEntityId()) {
                i->erase(i->begin() + k--);
            }
        }
    }
}

void ComponentHolder::removeAllComponent(Entities &entity)
{
    for (auto &i : m_Holder) {
        for (auto k = 0; k < i->size(); k++) {
            if (entity.getId() == (*i)[k]->getEntityId()) {
                i->erase(i->begin() + k--);
            }
        }
    }
}

// template <typename... Args>
// void ComponentHolder::modifyComponent(const Entities &entity, int idOfComp, Args &&... args)
// {
//     for (auto &i : m_Holder) {
//         for (auto k = 0; k < i->size(); k++) {
//             if (idOfComp == (*i)[k]->getId() && entity.getId() == (*i)[k]->getEntityId())
//                 (*i)[k]->modify(args ...);
//         }
//     }
// }