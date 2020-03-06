#pragma once

#include <vector>
#include <string>

#include "Entities.hpp"
#include "EntityComponentSystem/ComponentHolder.hpp"
#include "EntityComponentSystem/SystemBase.hpp"
#include "EntityComponentSystem/EventManager.hpp"
#include "ThreadPool.hpp"

#include "LayerType.hpp"

namespace Eligos
{
    class Layer
    {
    private:
        int m_id;
        bool m_isActivated = true;
        std::vector<Entities> m_entities;
        EventManager &eventManager;
        ThreadPool <EventManager, std::vector<Entities>> m_threadPool;
        std::vector<SystemBase *> m_system;
        ComponentHolder m_Holder;
    public:
        /* 
            * The default constructor is deleted cause i dont want people the create
            * a layer without sending the id
        */

        Layer() = delete;
        Layer(int id, EventManager &event) : m_id(id), eventManager(event), m_threadPool(eventManager)
        {
            reserveEntities();
        };
        virtual ~Layer() = default;
        void init(Eligos::LayerType type);

        /*
            * Functions to enable/disable the whole layer 
        */

        void disable() { m_isActivated = false; };
        void enable() { m_isActivated = true; };      

        void removeComponent(Entities entity, int idOfcomp);
        void removeAllComponent(Entities entity);
        template <class T, typename... Args>
        void addComponent(Entities entity, int idOfComp, Args &&... args) { m_Holder.addComponent<T>(entity, idOfComp, args...); }
        void addComponent(Entities entity, Components *comp) { m_Holder.addComponent(entity, comp); }


        /* 
            * Function about the different entities 
        */
        void removeEntity(Entities &entity);
        void addEntity(Entities &entity);
        void addEntities(std::vector<Entities> &entities);

        void addSystem(SystemBase *newSystem);
        
        /*
            * different getter
        */
        bool getStatus() const;
        int getId() const { return m_id; };
        std::vector<SystemBase *> getSystem() const {return m_system;};

        bool update(); // * Update, a Core function of the ECS 

    private:
        void reserveEntities(const int size = 1000) { return m_entities.reserve(size); };
        
        // * Function to init the type of the Layer
        void initBackground();
        void initGame();
        void initUI();
    };
} // namespace Eligos
