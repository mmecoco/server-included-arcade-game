#pragma once

#include <iostream>
#include <memory>
#include "Component.hpp"
#include "Drawable.hpp"
#include "Text.hpp"
#include "TextureComponent.hpp"
#include "Sprite.hpp"

class DrawableObjComponent : public Components
{
public:
    std::shared_ptr<Eligos::Drawable::Object> m_obj;
    enum class type {SPRITE, TEXT};
    type m_type;
public:
    DrawableObjComponent(int id) : Components(id, getCompId()){};
    virtual ~DrawableObjComponent() = default;
    static Components *Create(const int &id) { return new DrawableObjComponent(id); };
    virtual void modify(Eligos::NoDrawable::Font *font)
    {
        if (!m_obj)
        {
            m_obj.reset(new Eligos::Drawable::Text(font));
            m_obj->m_Type = Eligos::Drawable::Object::TYPE::TEXT;
        }
    };
    virtual void modify(const std::string &text)
    {
        if (m_obj)
            m_obj->setString(text);
    };
    virtual void modify(Eligos::NoDrawable::Texture *text)
    {
        std::cout << "CREATION TEXTURE" << std::endl;
        m_obj.reset(new Eligos::Drawable::Sprite(text));
        m_obj->m_Type = Eligos::Drawable::Object::TYPE::SPRITE;
    };
    virtual void dump() {}
    virtual Components *clone()
    {
        std::cout << "CREATION Drawable OBJ comp" << std::endl;
        return new DrawableObjComponent(*this);
    }
    int getEntityId() const { return m_entityId; };
    static int getCompId() { return 15; };
};