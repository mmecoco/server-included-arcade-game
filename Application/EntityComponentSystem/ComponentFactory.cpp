#include "ComponentFactory.hpp"
#include "PositionComponent.hpp"
#include "VelocityComponent.hpp"
#include "DrawableComponent.hpp"
#include "DirectionComponent.hpp"
#include "SpriteComponent.hpp"
#include "InputComponent.hpp"
#include "TextComponent.hpp"
#include "FontComponent.hpp"
#include "TextureComponent.hpp"
#include "DrawableObjectComponent.hpp"
#include "PlayableComponent.hpp"
#include "TeamComponent.hpp"
#include "FriendEntityComponent.hpp"
#include "AudioComponent.hpp"
#include "HeartPointComponent.hpp"
#include "HitboxComponent.hpp"
#include "PowerDamageComponent.hpp"
#include "BonusComponent.hpp"
#include "ShootRateComponent.hpp"

ComponentFactory::ComponentFactory()
{
    Register(PositionComponent::getCompId(), &PositionComponent::Create);
    Register(SpriteComponent::getCompId(), &SpriteComponent::Create);
    Register(TextureComponent::getCompId(), &TextureComponent::Create);
    Register(FontComponent::getCompId(), &FontComponent::Create);
    Register(TextComponent::getCompId(), &TextComponent::Create);
    Register(DirectionComponent::getCompId(), &DirectionComponent::Create);
    Register(VelocityComponent::getCompId(), &VelocityComponent::Create);
    Register(DrawableComponent::getCompId(), &DrawableComponent::Create);
    Register(DrawableObjComponent::getCompId(), &DrawableObjComponent::Create);
    Register(InputComponent::getCompId(), &InputComponent::Create);
    Register(PlayableComponent::getCompId(), &PlayableComponent::Create);
    Register(TeamComponent::getCompId(), &TeamComponent::Create);
    Register(FriendEntityComponent::getCompId(), &FriendEntityComponent::Create);
    Register(AudioComponent::getCompId(), &AudioComponent::Create);
    Register(HearthPointComponent::getCompId(), &HearthPointComponent::Create);
    Register(HitboxComponent::getCompId(), &HitboxComponent::Create);
    Register(PowerDamageComponent::getCompId(), &PowerDamageComponent::Create);
    Register(BonusComponent::getCompId(), &BonusComponent::Create);
    Register(ShootRateComponent::getCompId(), &ShootRateComponent::Create);
};

void ComponentFactory::Register(const int &idOfComp, CreateComponentFn pfnCreate)
{
    m_FactoryMap[idOfComp] = pfnCreate;
}

Components *ComponentFactory::CreateComponent(const int &ComponentName, const int &idOfEntity)
{
    auto it = m_FactoryMap.find(ComponentName);
    if (it != m_FactoryMap.end())
        return it->second(idOfEntity);
    return NULL;
}
