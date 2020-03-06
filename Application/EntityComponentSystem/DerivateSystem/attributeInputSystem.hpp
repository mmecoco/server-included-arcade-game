#pragma once

#include <memory>
#include "InputComponent.hpp"
#include "SystemBase.hpp"

class attributeInputSystem : public SystemBase
{
private:
    std::shared_ptr<Eligos::RendererAPI> m_api;
    std::vector<InputComponent *> *m_input;
    // std::vector<InputComponent *> *m_input;

public:
    attributeInputSystem() : SystemBase(5){};
    ~attributeInputSystem() = default;

    virtual void init(std::vector<InputComponent *> *obj) { m_input = obj; };
    virtual void init(std::shared_ptr<Eligos::RendererAPI> obj) { m_api = obj; };
    virtual void update(EventManager &, std::vector<Entities> &);
    virtual void dump() { std::cout << "attributeInputSystem" << std::endl; }

    static SystemBase *Create() { return new attributeInputSystem(); }
};
