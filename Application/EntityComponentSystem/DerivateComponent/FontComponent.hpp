#pragma once

#include <iostream>
#include <memory>
#include "Component.hpp"
#include "Drawable.hpp"
#include "Font.hpp"

class FontComponent : public Components
{
public:
    std::shared_ptr<Eligos::NoDrawable::Font> m_font;
public:
    int x;
    int y;
    FontComponent(int id) : Components(id, getCompId()) {};
    virtual ~FontComponent() = default;
    static Components *Create(const int &id) { return new FontComponent(id); };
    virtual void modify(const std::string &path)
    {
        if (!m_font) {
            m_font.reset(new Eligos::NoDrawable::Font());
            m_font->loadFromFile(path);
        }
    };
    virtual void dump() {}
    int getEntityId() const { return m_entityId; };
    virtual Components *clone()
    {
        std::cout << "CREATION COPY Font" << std::endl;
        return new FontComponent(*this);
    }
    static int getCompId() { return 13; };
};
