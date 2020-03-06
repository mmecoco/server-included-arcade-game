#pragma once

#include <iostream>
#include <memory>
#include "Component.hpp"
#include "Drawable.hpp"
#include "Text.hpp"

class TextComponent : public Components
{
public:
    std::shared_ptr<Eligos::Drawable::Text> m_text;
public:
    TextComponent(int id) : Components(id, getCompId()){};
    virtual ~TextComponent() = default;
    static Components *Create(const int &id) { return new TextComponent(id); };
    virtual void modify(Eligos::NoDrawable::Font *font)
    {
        if (!m_text) {
            m_text.reset(new Eligos::Drawable::Text(font));
        }
    };
    virtual void modify(const std::string &text)
    {
        if (m_text)
            m_text->setString(text);
    };
    virtual void dump() {}
    virtual Components *clone()
    {
        std::cout << "CREATION COPY text" << std::endl;
        return new TextComponent(*this);
    }
    static int getCompId() { return 14; };
};