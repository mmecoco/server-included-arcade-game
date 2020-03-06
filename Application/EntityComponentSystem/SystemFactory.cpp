#include "SystemFactory.hpp"
#include "moveSystem.hpp"
#include "RenderSystem.hpp"
#include "GraphicPositionSystem.hpp"
#include "changeSpeedSystem.hpp"
#include "attributeInputSystem.hpp"
#include "PopMissileSystem.hpp"
#include "ColideSystem.hpp"
#include "DamageSystem.hpp"
#include "deathSystem.hpp"
#include "BonusSystem.hpp"
#include "EndGameSystem.hpp"
#include "ReceiveSystem.hpp"
#include "SendSystem.hpp"


void SystemFactory::Register(const std::string &SystemName, CreateSystemFn pfnCreate)
{
    m_FactoryMap[SystemName] = pfnCreate;
}

SystemBase *SystemFactory::CreateSystem(const std::string &SystemName)
{
    auto it = m_FactoryMap.find(SystemName);
    if (it != m_FactoryMap.end())
        return it->second();
    return NULL;
}

SystemFactory::SystemFactory()
{
    Register("MOVE", &moveSystem::Create);
    Register("RENDERER", &RenderSystem::Create);
    Register("RENDERERPOS", &GraphicPositionSystem::Create);
    Register("ATTRIBUTE", &attributeInputSystem::Create);
    Register("SPEEDCHANGE", &changeSpeedSystem::Create);
    Register("SHOOT", &PopMissilesystem::Create);
    Register("COLIDE", &ColideSystem::Create);
    Register("DAMAGE", &DamageSystem::Create);
    Register("DEATH", &deathSystem::Create);
    Register("BONUS", &bonusSystem::Create);
    Register("ENDGAME", &EndGameSystem::Create);
    Register("RECEIVE", &ReceiveSystem::Create);
    Register("SEND", &SendSystem::Create);
}