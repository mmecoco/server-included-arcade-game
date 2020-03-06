#include <iostream>
#include <vector>

extern "C" void back(std::vector<std::vector<std::string>> &loadedScriptname)
{
    loadedScriptname.push_back({"../ScriptFile/defaultEntityBck.json"});
}

extern "C" void game(std::vector<std::vector<std::string>> &loadedScriptname)
{
    loadedScriptname.push_back({"../ScriptFile/defaultEntityGame.json"});
}

extern "C" void uiHealth(std::vector<std::vector<std::string>> &loadedScriptname)
{
    loadedScriptname.push_back({"../ScriptFile/defaultEntityUIhealth.json"});
}

extern "C" void uishield(std::vector<std::vector<std::string>> &loadedScriptname)
{
    loadedScriptname[2].push_back("../ScriptFile/defaultEntityUIshield.json");
}
