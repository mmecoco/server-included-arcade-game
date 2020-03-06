#pragma once

#include <map>
#include <string>
#include "SystemBase.hpp"

typedef SystemBase *(*CreateSystemFn)();

class SystemFactory
{
private:
    typedef std::map<std::string, CreateSystemFn> mapFactory;

    SystemFactory();
    SystemFactory(const SystemFactory &) = default;
    SystemFactory &operator=(const SystemFactory &) { return *this; }

    mapFactory m_FactoryMap;
public:
    ~SystemFactory() { m_FactoryMap.clear(); };

    static SystemFactory *Get()
    {
        static SystemFactory instance;
        return &instance;
    }

    void Register(const std::string &SystemName, CreateSystemFn pfnCreate);
    SystemBase *CreateSystem(const std::string &SystemName);

};