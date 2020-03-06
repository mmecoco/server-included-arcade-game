#pragma once

#include <set>
#include "Entities.hpp"

class EntitiesFactory
{
private:
    typedef std::set<int> EntitiesList;

    EntitiesFactory() = default;
    EntitiesFactory(const EntitiesFactory &) = default;
    EntitiesFactory &operator=(const EntitiesFactory &) { return *this; }

    EntitiesList m_FactoryId;
public:
    virtual ~EntitiesFactory() = default;

    static EntitiesFactory *Get(void)
    {
        static EntitiesFactory instance;
        return &instance;
    }
    Entities CreateComponent();
    void DeleteComponent(int id);
};