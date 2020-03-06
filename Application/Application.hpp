#pragma once

#include <memory>

#include "Scene.hpp"
#include "Layer.hpp"
#include "SfmlRenderer.hpp"

namespace Eligos
{
    class Application
    {
    protected:
        bool m_running = true;
        std::vector<std::unique_ptr<Eligos::Scene>> m_SceneStack;
        std::vector<std::vector<std::string>> m_loadedScriptname; // * Script to be generated for each Layer ?
        int m_CurrentScene = 0;
        std::shared_ptr<Eligos::RendererAPI> m_api;
        virtual void CreateScene(int id); // A voir quel arg je lui donne
    public:
        virtual ~Application() = default;
        virtual void generateScene();
        virtual void AddScene(Eligos::Scene *); // A voir quel arg je lui donne
        // virtual void AddScene(std::unique_ptr<Scene> &&scene);
        virtual void DeleteScene(int id);
        virtual void run();
    };
} // namespace Eligos
