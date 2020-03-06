#pragma once

#include <iostream>
#include <memory>
#include "Component.hpp"
#include "Drawable.hpp"
#include "TextureComponent.hpp"
#include "Sprite.hpp"

class SpriteComponent : public Components
{
public:
    std::shared_ptr<Eligos::Drawable::Sprite> m_sprite;
public:
    SpriteComponent(int id) : Components(0, id){};
    virtual ~SpriteComponent() = default;
    static Components *Create(const int &id) { return new SpriteComponent(id); };
    virtual void modify(Eligos::NoDrawable::Texture *text)
    {
        if (!m_sprite)
            m_sprite.reset(new Eligos::Drawable::Sprite(text));
    };
    virtual void dump() {}
    virtual Components *clone()
    {
        return new SpriteComponent(*this);
    }
    int getEntityId() const { return m_entityId; };
    static int getCompId() { return 12; };
};
