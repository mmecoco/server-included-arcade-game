#include <iostream>
#include "Application.hpp"
#include "SystemFactory.hpp"
#include "ComponentFactory.hpp"
#include "EntitiesFactory.hpp"
#include "DrawableComponent.hpp"
#include "ScriptEngine/Script.hpp"
#include "RenderSystem.hpp"
#include "attributeInputSystem.hpp"
#include "changeSpeedSystem.hpp"

class MyGame : public Eligos::Application
{
    /*
        ! INFO
        ! ------------------------
        ! Pour creer une App, voici les etapes :
        * 1) Ajouter les fichiers de Script
        * 2) Register les differents Composant de l'ECS
        * 3) Generer Une Scene;
        * 4) Creer Les Layers
        * 5) INIT la Scene
        * 6) Register les Systems
    */
public:
    MyGame() {
        m_api.reset(new Eligos::SfmlRenderer());
        m_loadedScriptname.push_back({DEFAULT_BCK});
        m_loadedScriptname.push_back({DEFAULT_GAME});
        m_loadedScriptname.push_back({DEFAULT_UI_HEALTH});
        m_loadedScriptname[2].push_back(DEFAULT_UI_SHIELD);
        m_loadedScriptname[1].push_back("../ScriptFile/Scene0/EnemiesEntity.json");
        m_loadedScriptname[1].push_back("../ScriptFile/Scene0/EventScript.json");
        m_loadedScriptname[1].push_back("../ScriptFile/Scene0/EventScript1.json");
        m_loadedScriptname[1].push_back("../ScriptFile/Scene0/missile1Entity.json");
        m_loadedScriptname[0].push_back("../ScriptFile/Scene1/StageEntity.json");
        m_loadedScriptname[0].push_back("../ScriptFile/Scene1/EventScript2.json");

        try {
            generateScene();
              // m_SceneStack[0]->init(m_loadedScriptname);
            RenderSystem *sys = (RenderSystem *)SystemFactory::Get()->CreateSystem("RENDERER");
            RenderSystem *sys1 = (RenderSystem *)SystemFactory::Get()->CreateSystem("RENDERER");
            RenderSystem *sys2 = (RenderSystem *)SystemFactory::Get()->CreateSystem("RENDERER");
            sys->init(m_api);
            sys1->init(m_api);
            sys2->init(m_api);
            m_SceneStack[0]->addSystemLayer(sys, 0);
            m_SceneStack[0]->addSystemLayer(sys1, 1);
            m_SceneStack[0]->addSystemLayer(sys2, 2);

            SystemBase *graphPos = SystemFactory::Get()->CreateSystem("RENDERERPOS");
            SystemBase *graphPos1 = SystemFactory::Get()->CreateSystem("RENDERERPOS");
            SystemBase *graphPos2 = SystemFactory::Get()->CreateSystem("RENDERERPOS");

            m_SceneStack[0]->addSystemLayer(graphPos, 0);
            m_SceneStack[0]->addSystemLayer(graphPos1, 1);
            m_SceneStack[0]->addSystemLayer(graphPos2, 2);

            SystemBase *movesys = SystemFactory::Get()->CreateSystem("MOVE");
            m_SceneStack[0]->addSystemLayer(movesys, 1);
            attributeInputSystem *attSys = (attributeInputSystem *)SystemFactory::Get()->CreateSystem("ATTRIBUTE");
            attSys->init(m_api);
            m_SceneStack[0]->addSystemLayer(attSys, 1);
            SystemBase *speed = SystemFactory::Get()->CreateSystem("SPEEDCHANGE");
            m_SceneStack[0]->addSystemLayer(speed, 1);
            SystemBase *shoot = SystemFactory::Get()->CreateSystem("SHOOT");
            m_SceneStack[0]->addSystemLayer(shoot, 1);
            SystemBase *colide = SystemFactory::Get()->CreateSystem("COLIDE");
            m_SceneStack[0]->addSystemLayer(colide, 1);
            SystemBase *damage = SystemFactory::Get()->CreateSystem("DAMAGE");
            m_SceneStack[0]->addSystemLayer(damage, 1);
            SystemBase *bonus = SystemFactory::Get()->CreateSystem("BONUS");
            m_SceneStack[0]->addSystemLayer(bonus, 1);
            SystemBase *EndGame = SystemFactory::Get()->CreateSystem("ENDGAME");
            m_SceneStack[0]->addSystemLayer(EndGame, 1);
            SystemBase *death = SystemFactory::Get()->CreateSystem("DEATH");
            m_SceneStack[0]->addSystemLayer(death, 1);
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            throw std::logic_error("Invalid Game configuration");
        }
    };
    virtual ~MyGame() = default;
};

using namespace Eligos;

int main(int argc, char const *argv[])
{
    try
    {
        MyGame TestGame;
        TestGame.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    catch (...)
    {
        return 1;
    }
    return 0;
}

// for (auto i = 0; i < m_SceneStack.size(); i++)
// {
//     RenderSystem *sys = (RenderSystem *)SystemFactory::Get()->CreateSystem("RENDERER");
//     sys->init(m_api);
//     m_SceneStack[0]->addSystemLayer(sys, i);
// }
// // for (auto i = 0; i < m_SceneStack.size(); i++)
// // {
// //     SystemBase *graphPos = SystemFactory::Get()->CreateSystem("RENDERERPOS");
// //     m_SceneStack[0]->addSystemLayer(graphPos, i);
// // }
