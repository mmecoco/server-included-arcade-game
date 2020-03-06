#pragma once

#include <vector>

#include "Entities.hpp"
#include "Component.hpp"
#include "DerivateComponent/PositionComponent.hpp"
#include "ComponentFactory.hpp"

class ComponentHolder
{
private:
    std::vector<std::vector<Components *> *> m_Holder;
public:
    template <class T,typename... Args>
    void addComponent(Entities &entity, int idOfComp, Args &&... args)
    {
        entity.addComponent(idOfComp);
        Components *tmp = ComponentFactory::Get()->CreateComponent(idOfComp, entity.getId());
        tmp->modify<T>(args...);
        m_Holder[idOfComp]->push_back(tmp);
    }
    void addComponent(Entities &entity, Components *comp)
    {
        entity.addComponent(comp->getId());
        m_Holder[comp->getId()]->push_back(comp);
    }
    template <class T, typename... Args>
    void modifyComponent(const Entities &entity, int idOfComp, Args &&... args)
    {
        for (auto &i : m_Holder) {
            for (auto k = 0; k < i->size(); k++) {
                if (idOfComp == (*i)[k]->getId() && entity.getId() == (*i)[k]->getEntityId())
                    (*i)[k]->modify<T>(args ...);
            }
        }
    }

    void removeComponent(Entities &, int idOfComp);
    void removeAllComponent(Entities &);

    template <class T>
    std::vector<T *> *getComponent(int idOfComp)
    {
        for (auto &i : m_Holder) {
            for (auto k = 0; k < i->size(); k++) {
                if ((*i)[k]->getId() == idOfComp){
                    return (std::vector<T *> *)(i);
                }
            }
        }
        return nullptr;
    };

    ComponentHolder(int size = 100)
    {
        m_Holder.reserve(1000);
        for (auto i = 0; i < size; i++)
            m_Holder.push_back(new std::vector<Components *>());
    };
    virtual ~ComponentHolder() = default;
};