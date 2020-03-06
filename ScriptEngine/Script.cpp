#include <fstream>
#include <iostream>
#include "Script.hpp"
#include "SpriteComponent.hpp"
#include "TextComponent.hpp"
#include "DrawableObjectComponent.hpp"

void ScriptManager::loadEntity(const std::string &fileName)
{
    std::ifstream fileStream(fileName);
    json jsonHandler;

    fileStream >> jsonHandler;

    if (jsonHandler["type"] != "Entity" ||
        m_GeneratedEntity.find(jsonHandler["Code"]) != m_GeneratedEntity.end())
        return;
    m_GeneratedEntity.insert({std::string(jsonHandler["Code"]), {}});
    for (auto i = jsonHandler.begin(); i != jsonHandler.end(); i++)
    {
        if ((*i).contains("id") == true) {
            Components *comp;
            if((*i)["id"] == SpriteComponent::getCompId()) {
                comp = ComponentFactory::Get()->CreateComponent(DrawableObjComponent::getCompId(), -1);
                ((DrawableObjComponent *)comp)->m_type = DrawableObjComponent::type::SPRITE;
            }
            else if ((*i)["id"] == TextComponent::getCompId()) {
                comp = ComponentFactory::Get()->CreateComponent(DrawableObjComponent::getCompId(), -1);
                ((DrawableObjComponent *)comp)->m_type = DrawableObjComponent::type::TEXT;
            }
            else
                comp = ComponentFactory::Get()->CreateComponent((*i)["id"], -1);
            m_GeneratedEntity[jsonHandler["Code"]].push_back(comp);
            modifyValue(i, comp);
        }
    }
}

void ScriptManager::generateEntity(const std::string &str, Eligos::Layer *layer)
{
    std::cout << "Generating Entity..." << std::endl;
    Entities entity = EntitiesFactory::Get()->CreateComponent();

    layer->addEntity(entity);

    std::ifstream fileStream(str);
    json jsonHandler;

    fileStream >> jsonHandler;
    for (int i = 0; i < m_GeneratedEntity[jsonHandler["Code"]].size(); i++)
    {
        m_GeneratedEntity[jsonHandler["Code"]][i]->setEntityId(entity.getId());
        layer->addComponent(entity, m_GeneratedEntity[jsonHandler["Code"]][i]->clone());
    }
}

void ScriptManager::loadScript(const std::string &fileName)
{
    std::ifstream fileStream(fileName);
    json jsonHandler;

    std::cout << "Loading Script : " << fileName << "..." << std::endl;
    fileStream >> jsonHandler;
    if (jsonHandler["type"] != "Script")
        return;

    std::cout << "filename " << fileName << std::endl;
    m_GeneratedScript.insert({fileName, {}});
    for (auto i = jsonHandler.begin(); i != jsonHandler.end(); i++)
    {
        if (i->contains("Timer")) {
            int nbr = (*i)["Entity"]["Number"];
            std::string str = (*i)["Entity"]["Code"];
            m_GeneratedScript[fileName].objects.insert({str, nbr});
            m_GeneratedScript[fileName].timer = (*i)["Timer"];
            m_GeneratedScript[fileName].done = false;
            m_GeneratedScript[fileName].name = std::string(jsonHandler["Code"]);
        }
    }
}

void ScriptManager::generateScript(const std::string &str, Eligos::Layer *where)
{
    std::cout << "Generating Script..." << std::endl;
    std::ifstream fileStream(str);
    json jsonHandler;

    fileStream >> jsonHandler;
    if (jsonHandler["type"] != "Script")
        return;
    if (m_GeneratedScript.find(str) == m_GeneratedScript.end())
        return;
    for (auto i = jsonHandler.begin(); i != jsonHandler.end(); i++)
    {
        if (i->contains("Entity"))
        {
            for (int p = 0; p < (*i)["Entity"]["Number"]; p++) {
                Entities entity = EntitiesFactory::Get()->CreateComponent();
                where->addEntity(entity);

                std::vector<Components *> &ref = m_GeneratedEntity[(*i)["Entity"]["Code"]];
                for (auto &j : ref)
                {
                    if (j->getId() == PositionComponent::getCompId())
                    {
                        Components *comp = j->clone();
                        comp->setEntityId(entity.getId());
                        comp->modify<PositionComponent>((*i)["Entity"]["Position"][p]);
                        where->addComponent(entity, comp);

                    }
                    else if (j->getId() == DrawableObjComponent::getCompId())
                    {
                        Components *comp = j->clone();
                        comp->setEntityId(entity.getId());
                        comp->modify<DrawableObjComponent>(m_texture[(*i)["Entity"]["Sprite"]]);
                        where->addComponent(entity, comp);
                    } else {
                        Components *comp = j->clone();
                        comp->setEntityId(entity.getId());
                        where->addComponent(entity, comp);
                    }
                }
            }
        }
    }
}

void ScriptManager::generateEntityFromScript(const std::string &str, Eligos::Layer *layer) // * create a entity with comp
{
    Entities entity = EntitiesFactory::Get()->CreateComponent();

    layer->addEntity(entity);

    for (int i = 0; i < m_GeneratedEntity[str].size(); i++)
    {
        m_GeneratedEntity[str][i]->setEntityId(entity.getId());
        Components *comp = m_GeneratedEntity[str][i]->clone();
        // comp->modify<PositionComponent>();
        layer->addComponent(entity, comp);
    }
}

void ScriptManager::checkIfGenerateScript(int time, Eligos::Layer *where, std::vector<std::string> &fileName)
{
    std::vector<std::string> str;

    for (auto &i : fileName)
    {
        if (i.find("Event") != std::string::npos)
            str.push_back(i);
    }
    
    for (auto &i : str)
    {
        if (m_GeneratedScript.find(i) != m_GeneratedScript.end())
        {
            std::cout << time << " == " << m_GeneratedScript[i].timer << std::endl;
            if (time >= m_GeneratedScript[i].timer && m_GeneratedScript[i].done == false)
            {
                generateScript(i, where);
                m_GeneratedScript[i].done = true;
            }
        }
    }
}

json ScriptManager::getHandler(const std::string path)
{
    std::ifstream fileStream(path);
    json jsonHandler;

    fileStream >> jsonHandler;

    return jsonHandler;
}