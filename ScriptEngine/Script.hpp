#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <map>
#include <vector>
#include "ComponentFactory.hpp"
#include "EntitiesFactory.hpp"
#include "Layer.hpp"
#include "ScriptName.hpp"
#include "Drawable.hpp"

using json = nlohmann::json;

class ScriptManager
{
private:
    struct gameEvent
    {
        bool done;
        int timer;
        std::map<std::string, int> objects;
        std::string name;
    };
    std::map<std::string, gameEvent> m_GeneratedScript;
    std::map<std::string, std::vector<Components *>> m_GeneratedEntity; // * faudra absolument utiliser des shared ptr
    std::map<std::string, Eligos::NoDrawable::Texture *> m_texture;
    std::map<std::string, Eligos::NoDrawable::Font *> m_font;

private :
    void generateEntityFromScript(const std::string &str, Eligos::Layer *where); // * create a entity with comp
    void modify(nlohmann::detail::iter_impl<nlohmann::json> i, std::string, Eligos::Layer *layer);
public:
    ScriptManager() {};
    ~ScriptManager() = default;

    void modifyValue(nlohmann::detail::iter_impl<nlohmann::json> i, Components *comp);
    json getHandler(const std::string path);
    void loadEntity(const std::string &str);                       // * load in Memory the comp
    void generateEntity(const std::string &str, Eligos::Layer *where); // * create a entity with comp
    void loadScript(const std::string &str);
    void generateScript(const std::string &str, Eligos::Layer *where);
    void checkIfGenerateScript(int time, Eligos::Layer *where, std::vector<std::string> &);
};
