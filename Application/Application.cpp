#include <algorithm>
#include <iostream>
#include "Application.hpp"
#include "EngineException.hpp"

namespace Eligos
{
    // void Application::AddScene(std::unique_ptr<Scene> &&scene)
    // {
    //     m_SceneStack.emplace_back(scene);
    // }
    void Application::AddScene(Eligos::Scene *scene)
    {
        m_SceneStack.emplace_back(scene);
    }
    void Application::DeleteScene(int id)
    {
        if (id > m_SceneStack.size())
        {
            m_SceneStack.erase(m_SceneStack.begin() + id);
        }
    }
    void Application::run()
    {
        while (!m_api->isClose())
        {
            m_api->ClearScreen();
            for (auto &i : m_SceneStack)
            {
                if (i->update() == false)
                    m_running = !m_running;
                if (!m_running)
                    break;
            }
            if (!m_running)
                break;
            m_api->Display();
        }
        std::cout << "End Game" << std::endl;
    }
    void Application::CreateScene(int id)
    {
        // std::unique_ptr<Eligos::Scene> ptrScene = std::make_unique<Eligos::Scene>(id);

        m_SceneStack.emplace_back(std::make_unique<Scene>(id));
    }
    void Application::generateScene()
    {
        std::cout << "Generating Scene..." << std::endl;
        try
        {
            Eligos::Scene *ptrScene = new Eligos::Scene(m_CurrentScene++);
            ptrScene->CreateLayer(0);
            ptrScene->CreateLayer(1);
            ptrScene->CreateLayer(2);
            ptrScene->init(m_loadedScriptname);
            ptrScene->init(m_api);
            AddScene(ptrScene);
            std::cout << "Scene Generated" << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            throw EngineException<CException::SceneGeneration>("Cannot generate the Scene");
        }
        
    }
} // namespace Eligos
