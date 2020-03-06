
#include <algorithm>
#include <iostream>
#include "Scene.hpp"
#include "Layer.hpp"

#include "ScriptName.hpp"
#include "EngineException.hpp"
#include "DrawableComponent.hpp"
#include "SpriteComponent.hpp"
#include "FriendEntityComponent.hpp"
#include "DamageSystem.hpp"
#include "BonusSystem.hpp"

namespace Eligos
{
    void Scene::AddLayer(Eligos::Layer *layer)
    {
        m_LayerStack.push_back(layer);
    }
        
    void Scene::CreateLayer(int id)
    {
        Eligos::Layer *new_layer = new Layer(id, m_eventManager);

        m_LayerStack.push_back(new_layer);
    }
    
    void Scene::reserve(int size)
    {
        m_LayerStack.reserve(size);
        // m_system.reserve(size);
    }

    void Scene::generateEntity(const std::string str, Eligos::Layer *layer, IEvent *event)
    {
        Entities ent = EntitiesFactory::Get()->CreateComponent();
        layer->addEntity(ent);

        json j = m_ScripManager.getHandler(str);
        for (auto i = j.begin(); i != j.end(); i++)
        {
            if ((*i).contains("id") == true)
            {
                Components *comp;
                if ((*i)["id"] == SpriteComponent::getCompId())
                {
                    comp = ComponentFactory::Get()->CreateComponent(DrawableObjComponent::getCompId(), -1);
                    ((DrawableObjComponent *)comp)->m_type = DrawableObjComponent::type::SPRITE;
                }
                else
                    comp = ComponentFactory::Get()->CreateComponent((*i)["id"], -1);

                if ((*i)["id"] == PositionComponent::getCompId()) {
                    if (event->m_id == 2)
                        comp->modify<PositionComponent>(((MissileEvent *)event)->m_pos);
                }
                else if ((*i)["id"] == FriendEntityComponent::getCompId())
                {
                    if (event->m_id == 2)
                        comp->modify<FriendEntityComponent>(((MissileEvent *)event)->m_entity_id);
                }
                else
                    m_ScripManager.modifyValue(i, comp);
                comp->setEntityId(ent.getId());
                layer->addComponent(ent, comp);
            }
        }
    }

    bool Scene::update()
    {
        for (int i = 0; i < m_scriptName.size(); i++)
            m_ScripManager.checkIfGenerateScript(m_clock.getClock().count(), m_LayerStack[i], m_scriptName[i]);
        for (auto i = 0; i < m_LayerStack.size(); i++) {
            while (!m_eventManager.isEmpty()) {
                IEvent *event = m_eventManager.processEvent(); 

                if (event->m_type == CREATE_ENTITY) {
                    if (event->m_id == 2)
                        generateEntity(((MissileEvent *)event)->path, m_LayerStack[1], event);
                }
                else if (event->m_type == KILL_ENTITY) {
                    if (event->m_id == 3) {
                        m_LayerStack[1]->removeAllComponent(((KillEntityEvent *)event)->m_entity);
                        m_LayerStack[1]->removeEntity(((KillEntityEvent *)event)->m_entity);
                    }
                }
                if (event->m_type == DAMAGE) {
                    if (event->m_id == 4) {
                        for (auto &it : m_LayerStack[1]->getSystem())
                            if (it->getId() == 100)
                                ((DamageSystem *)it)->update(m_eventManager ,((DamageEvent *)event)->m_dealerId, ((DamageEvent *)event)->m_takerId);
                    }
                }
                if (event->m_type == ENDGAME) {
                    return false;
                }
                if (event->m_type == BONUS)
                {
                    // if (event->m_id == 6)
                        for (auto &it : m_LayerStack[1]->getSystem())
                            if (it->getId() == 200)
                                ((bonusSystem *)it)->update(m_eventManager, ((BonusEvent *)event)->m_bonus);
                }
            } 
            m_LayerStack[i]->update();
        }
        return true;
    }

    void Scene::init(std::vector<std::vector<std::string>> & scriptFiles)
    {
        m_scriptName = scriptFiles;
        for (int i = 0; i < scriptFiles.size(); i++)
        {
            for (int j = 0; j < scriptFiles[i].size(); j++) {
                // std::cout << "Scene INIT fct = " << j << std::endl;
                if (scriptFiles[i][j].find("Entity") != std::string::npos) {
                    m_ScripManager.loadEntity(scriptFiles[i][j]);
                    if (scriptFiles[i][j].find("default") != std::string::npos)
                    {
                        m_ScripManager.generateEntity(scriptFiles[i][j], m_LayerStack[i]);
                    }
                }
                else if (scriptFiles[i][j].find("Event") != std::string::npos)
                    m_ScripManager.loadScript(scriptFiles[i][j]);
                else
                    throw EngineException<CException::ScriptLoading>("Wrong Script Name");
            }
        }
    }

    void Scene::init(std::shared_ptr<Eligos::RendererAPI> api)
    {
        m_api = api;
    }

    void Scene::addSystemLayer(SystemBase *newSystem, int id)
    {
        m_LayerStack[id]->addSystem(newSystem);
    }

} // namespace Eligos
