#pragma once

#include <vector>
#include <string>
#include "Layer.hpp"
#include "EntityComponentSystem/ComponentHolder.hpp"
#include "ThreadPool.hpp"
#include "Script.hpp"
#include "Clock.hpp"
//#include "Server.hpp"
#include "SystemFactory.hpp"
#include "Renderer.hpp"
#include "RenderSystem.hpp"

/*
    * Comment va se derouler le jeu a terme
    * on aura un fct private qui tout les x temps
    * genera un event aleatoire qui fera pop des monstres
    * Apres un certain temps on fait pop un boss
    * Puis on recommence (lvl2) avec des appartions plus frequentes
    * Ou des stats plus eleve
*/


namespace Eligos
{
    class Scene
    {
    private:
        int m_id; // * id de la scene 
        bool m_isActivated = true; // * Si la scene est active
        
        bool isGenerated = false; // * Boolean value to check if the Entities are generated 
        std::vector<std::vector<std::string>> m_scriptName; // * The names of the loaded Script 
        ScriptManager m_ScripManager;
        EventManager m_eventManager;
        Clock m_clock;

        ThreadPool<EventManager, std::vector<Entities>> m_threadPool;
        std::vector<Eligos::Layer *> m_LayerStack;
        std::shared_ptr<Eligos::RendererAPI> m_api;
        void generateEntity(const std::string, Eligos::Layer *, IEvent *);

    private:
        Scene() = delete;
    public :
        Scene(int id) : m_id(id), m_threadPool(m_eventManager)
        {
            // ! INIT ICI LES SYSTEMS PRO
            // PRE AU LAYER
            // m_system.push_back(SystemFactory::Get()->CreateSystem("MOVE"));
            // RenderSystem *sys = (RenderSystem *)SystemFactory::Get()->CreateSystem("RENDERER");
            // sys->init(m_api);
            // sys.init();

            // m_system.push_back(sys);
        };
        virtual ~Scene() = default;

        void init(std::vector<std::vector<std::string>> &scriptFiles); // * init la scene en chargeant en memoires les differents scripts
        void init(std::shared_ptr<Eligos::RendererAPI>);

        void AddLayer(Eligos::Layer *);
        void CreateLayer(int id);
        void DeleteLayer(int id);

        void enable() { m_isActivated = true; };
        void disable() { m_isActivated = false; };
        bool getStatus() const { return m_isActivated; };

        // void addSystem(SystemBase *newSystem);
        void addSystemLayer(SystemBase *newSystem, int id);
        // void eraseSystem(int id);
        // void dumpInfoSystem(int id);

        bool update(); // * La fonction principale qui appel fait tourner la scene
    private:
        void reserve(int size = 100);
    };
} // namespace Eligos
