#include <algorithm>
#include "Layer.hpp"
#include "EntityComponentSystem/ComponentFactory.hpp"
#include "EntityComponentSystem/SystemFactory.hpp"
#include "EntityComponentSystem/DerivateSystem/moveSystem.hpp"
#include "RenderSystem.hpp"
#include "GraphicPositionSystem.hpp"
#include "attributeInputSystem.hpp"
#include "changeSpeedSystem.hpp"
#include "PopMissileSystem.hpp"
#include "ColideSystem.hpp"
#include "DamageSystem.hpp"
#include "deathSystem.hpp"
#include "BonusSystem.hpp"
#include "EndGameSystem.hpp"
#include "SendSystem.hpp"
#include "ReceiveSystem.hpp"

namespace Eligos
{
    void Layer::removeEntity(Entities &entity)
    {
        for (int i = 0; i < m_entities.size(); i++) {
            if (m_entities[i].getId() == entity.getId()) {
                m_entities.erase(m_entities.begin() + i);
                return;
            }
        }
    }

    void Layer::removeComponent(Entities entity, int compId)
    {
        m_Holder.removeComponent(entity, compId);
    };

    void Layer::removeAllComponent(Entities entity)
    {
        m_Holder.removeAllComponent(entity);
    };

    void Layer::addEntity(Entities &entity)
    {
        m_entities.emplace_back(std::move(entity));
    }

    void Layer::addEntities(std::vector<Entities> &entities)
    {
        m_entities.insert(m_entities.end(), entities.begin(), entities.end());
    }

    bool Layer::update()
    {
        IEvent *tmpEvent;

        for (auto &i : m_system)
        {
            i->update(eventManager, m_entities);
            // if (!eventManager.isEmpty()) {
            // tmpEvent = eventManager.processEvent();
                // if (tmpEvent->m_type == type_event::CREATE_COMPONENT) {
            // for (auto &i : m_system) {
                // if (tmpEvent->getId() == i->getId()) {
            // using namespace std::placeholders;
            // m_threadPool.enqueue(std::bind(&SystemBase::update, &(*i), _1, _2), m_entities);
                // }
        }
        return (true);
    }
    void Layer::addSystem(SystemBase *newSystem)
    {
        if (newSystem->getId() == 0) {
            int id = DrawableObjComponent::getCompId();
            ((RenderSystem *)newSystem)->init(m_Holder.template getComponent<DrawableObjComponent>(id));
        }
        else if (newSystem->getId() == 2)
        {
            int id = PositionComponent::getCompId();
            ((GraphicPositionSystem *)newSystem)->init(m_Holder.template getComponent<PositionComponent>(id));
            id = DrawableObjComponent::getCompId();
            ((GraphicPositionSystem *)newSystem)->init(m_Holder.template getComponent<DrawableObjComponent>(id));
        }
        else if (newSystem->getId() == 1)
        {
            int id = PositionComponent::getCompId();
            ((moveSystem *)newSystem)->init(m_Holder.template getComponent<PositionComponent>(id));
            id = VelocityComponent::getCompId();
            ((moveSystem *)newSystem)->init(m_Holder.template getComponent<VelocityComponent>(id));
            id = DirectionComponent::getCompId();
            ((moveSystem *)newSystem)->init(m_Holder.template getComponent<DirectionComponent>(id));
            id = TeamComponent::getCompId();
            ((moveSystem *)newSystem)->init(m_Holder.template getComponent<TeamComponent>(id));
            id = PlayableComponent::getCompId();
            ((moveSystem *)newSystem)->init(m_Holder.template getComponent<PlayableComponent>(id));
        } else if (newSystem->getId() == 5)
        {
            int id = InputComponent::getCompId();
            ((attributeInputSystem *)newSystem)->init(m_Holder.template getComponent<InputComponent>(id));
        }
        else if (newSystem->getId() == 6)
        {
            int id = InputComponent::getCompId();
            ((changeSpeedSystem *)newSystem)->init(m_Holder.template getComponent<InputComponent>(id));
            id = DirectionComponent::getCompId();
            ((changeSpeedSystem *)newSystem)->init(m_Holder.template getComponent<DirectionComponent>(id));
            id = VelocityComponent::getCompId();
            ((changeSpeedSystem *)newSystem)->init(m_Holder.template getComponent<VelocityComponent>(id));
        }
        else if (newSystem->getId() == 11)
        {
            int id = InputComponent::getCompId();
            ((PopMissilesystem *)newSystem)->init(m_Holder.template getComponent<InputComponent>(id));
            id = PositionComponent::getCompId();
            ((PopMissilesystem *)newSystem)->init(m_Holder.template getComponent<PositionComponent>(id));
            id = ShootRateComponent::getCompId();
            ((PopMissilesystem *)newSystem)->init(m_Holder.template getComponent<ShootRateComponent>(id));
        }
        else if (newSystem->getId() == 400)
        {
            int id = PositionComponent::getCompId();
            ((ColideSystem *)newSystem)->init(m_Holder.template getComponent<PositionComponent>(id));
            id = HitboxComponent::getCompId();
            ((ColideSystem *)newSystem)->init(m_Holder.template getComponent<HitboxComponent>(id));
            id = TeamComponent::getCompId();
            ((ColideSystem *)newSystem)->init(m_Holder.template getComponent<TeamComponent>(id));
            id = BonusComponent::getCompId();
            ((ColideSystem *)newSystem)->init(m_Holder.template getComponent<BonusComponent>(id));
        }
        else if (newSystem->getId() == 100)
        {
            int id = PowerDamageComponent::getCompId();
            ((DamageSystem *)newSystem)->init(m_Holder.template getComponent<PowerDamageComponent>(id));
            id = HearthPointComponent::getCompId();
            ((DamageSystem *)newSystem)->init(m_Holder.template getComponent<HearthPointComponent>(id));
        }
        else if (newSystem->getId() == 300)
        {
            int id = HearthPointComponent::getCompId();
            ((deathSystem *)newSystem)->init(m_Holder.template getComponent<HearthPointComponent>(id));
        }
        else if (newSystem->getId() == 200)
        {
            int id = BonusComponent::getCompId();
            ((bonusSystem *)newSystem)->init(m_Holder.template getComponent<BonusComponent>(id));
            id = HearthPointComponent::getCompId();
            ((bonusSystem *)newSystem)->init(m_Holder.template getComponent<HearthPointComponent>(id));
            id = PositionComponent::getCompId();
            ((bonusSystem *)newSystem)->init(m_Holder.template getComponent<PositionComponent>(id));
        }
        else if (newSystem->getId() == 500)
        {
            int id = HearthPointComponent::getCompId();
            ((EndGameSystem *)newSystem)->init(m_Holder.template getComponent<HearthPointComponent>(id));
            id = PlayableComponent::getCompId();
            ((EndGameSystem *)newSystem)->init(m_Holder.template getComponent<PlayableComponent>(id));
        }
        else if (newSystem->getId() == 10)
        {
            int id = PositionComponent::getCompId();
            ((SendSystem *)newSystem)->init(m_Holder.template getComponent<PositionComponent>(id));
            id = DrawableComponent::getCompId();
            ((SendSystem *)newSystem)->init(m_Holder.template getComponent<DrawableComponent>(id));
            id = InputComponent::getCompId();
            ((SendSystem *)newSystem)->init(m_Holder.template getComponent<InputComponent>(id));
        }
        else if (newSystem->getId() == 13)
        {
            int id = PositionComponent::getCompId();
            ((ReceiveSystem *)newSystem)->init(m_Holder.template getComponent<PositionComponent>(id));
            id = InputComponent::getCompId();
            auto i = m_Holder.template getComponent<InputComponent>(id);
            if (!i)
                exit (1);
            ((ReceiveSystem *)newSystem)->init(i);
        }
        m_system.emplace_back(std::move(newSystem));
    }

    void init(Eligos::LayerType type)
    {
        switch (type)
        {
        case Eligos::LayerType::BACKGROUND:
            break;
        case Eligos::LayerType::GAME:
            break;
        case Eligos::LayerType::UI:
            break;
        default:
            break;
        }
    }

    void Layer::initBackground()
    {
        // ? Pas de System designer seulement dans le background
        // ? Donc fonction vide
    }

    void Layer::initGame()
    {
        // ? Pas de System designer seulement dans le background
        // ? Donc fonction vide
        // ! Je donne des idees de System ducoup
        // ? Ces System seront call via Event
        // m_system.push_back(SystemFactory::Get()->CreateSystem("KILL"));
        // m_system.push_back(SystemFactory::Get()->CreateSystem("SHOOT"));
        // m_system.push_back(SystemFactory::Get()->CreateSystem("ADDBUFF"));
        // m_system.push_back(SystemFactory::Get()->CreateSystem("DROPBUFF"));
        // m_system.push_back(SystemFactory::Get()->CreateSystem("ADD SHIELD"));
        // m_system.push_back(SystemFactory::Get()->CreateSystem("ADD BOMB"));
        // m_system.push_back(SystemFactory::Get()->CreateSystem("USE BOMB"));
        // m_system.push_back(SystemFactory::Get()->CreateSystem("ATTACK"));
        // m_system.push_back(SystemFactory::Get()->CreateSystem("HIT"));
    }
    
    void Layer::initUI()
    {
        // ? Pas de System designer seulement dans le background
        // ? Donc fonction vide
        // ! Je donne des idees de System ducoup
        // ? Ces System seront call via Event
        // m_system.push_back(SystemFactory::Get()->CreateSystem("down hp"));
        // m_system.push_back(SystemFactory::Get()->CreateSystem(""));
    }
} // namespace Eligos
