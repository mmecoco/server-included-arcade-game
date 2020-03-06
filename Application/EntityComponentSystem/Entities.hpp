#pragma once

#include "Component.hpp"
// #include "Layer.hpp"

class Entities
{
private:
    int m_id;
    ComponentList m_listOfComp;
public:
    Entities() = delete;
    Entities(int id) : m_id(id) {};
    Entities(const Entities &) = default;
    Entities(Entities &&) = default;
    Entities &operator=(const Entities &) = default;
    Entities &operator=(Entities &&) = default;
    ~Entities() = default;

    bool addComponent(int idOfComponent);
    bool hasComponent(int idOfComponent) const;
    bool removeComponent(int idOfComponent);
    bool removeAllComponent();

    int &getId() { return m_id; };
    int getId() const { return m_id; };
    const ComponentList getComponents() const;
    void setId(int m_id);
    void clear();
};