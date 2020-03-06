#pragma once

#include <iostream>
#include <memory>
#include "Component.hpp"
#include "Drawable.hpp"
#include "Texture.hpp"

class TextureComponent : public Components
{
private:
    std::shared_ptr<Eligos::NoDrawable::Texture> m_texture;
    
public :
    TextureComponent(int id) : Components(id, getCompId()) {};
    virtual ~TextureComponent() = default;
    static Components *Create(const int &id) { return new TextureComponent(id); };
    virtual void modify(const std::string &str)
    {
        if (!m_texture) {
            m_texture.reset(new Eligos::NoDrawable::Texture());
            m_texture->loadFromFile(str);
        }
    };
    virtual Components *clone() { return new TextureComponent(*this); };
    virtual void dump() {}
    static int getCompId() { return 15; };
};