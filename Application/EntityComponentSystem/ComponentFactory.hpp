#pragma once

#include <map>
#include "Component.hpp"

// template <typename... Args>
typedef Components *(*CreateComponentFn)(const int &);
// using CreateComponentFn = std::function<Components *(Args...)>;
// using CreateComponentFn = Components *(T::create(Args &&... args));

class ComponentFactory
{
private:
    typedef std::map<int, CreateComponentFn> mapFactory;

    ComponentFactory();
    ComponentFactory(const ComponentFactory &) = default;
    ComponentFactory &operator=(const ComponentFactory &) { return *this; }

    mapFactory m_FactoryMap;
public:
    ~ComponentFactory() = default;

    static ComponentFactory *Get(void)
    {
        static ComponentFactory instance;
        return &instance;
    }

    void Register(const int &idOfComp, CreateComponentFn pfnCreate);
    Components *CreateComponent(const int &idOfComp, const int &);
};
