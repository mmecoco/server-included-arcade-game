#pragma once

#include "Component.hpp"
#include "SfmlRenderer.hpp"

class InputComponent : public Components
{
public:
    Eligos::input_keys m_input;

public:
    InputComponent(int id) : Components(id, getCompId()){};
    virtual ~InputComponent() = default;
    static Components *Create(const int &id) { 
        std::cout << "CREATE INPUT" << std::endl;
        return new InputComponent(id); };
    virtual void modify(int input)
    {
        m_input = (Eligos::input_keys)input;
    };
    virtual void modify(Eligos::input_keys input)
    {
        m_input = input;
    };
    virtual void dump() {}
    virtual Components *clone()
    {
        std::cout << "CLONE INPUT" << std::endl;
        return new InputComponent(*this);
    }
    int getEntityId() const { return m_entityId; };
    static int getCompId() { return 7; };
};
