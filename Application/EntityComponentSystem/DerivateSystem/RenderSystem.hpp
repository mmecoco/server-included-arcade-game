#pragma once

#include "SystemBase.hpp"
#include "DerivateComponent/TextureComponent.hpp"
#include "Drawable.hpp"
#include "Renderer.hpp"
#include "DrawableObjectComponent.hpp"


class RenderSystem : public SystemBase
{
private:
    std::shared_ptr<Eligos::RendererAPI> m_api;
    std::vector<DrawableObjComponent *> *m_object;
public:
    RenderSystem() : SystemBase(0) {};
    ~RenderSystem() = default;

    virtual void init(std::vector<DrawableObjComponent *> *obj) { m_object = obj; };
    virtual void init(std::shared_ptr<Eligos::RendererAPI> api) { m_api = api; };
    virtual void update(EventManager &, std::vector<Entities> &);
    virtual void dump() { std::cout << "RenderSystem" << std::endl; }

    static SystemBase *Create() { return new RenderSystem(); }
};
