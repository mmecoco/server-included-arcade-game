#pragma once

#include "Component.hpp"
#include <iostream>

class DrawableComponent : public Components
{
public:
    bool m_Drawable;
public:
    DrawableComponent() = default;
    DrawableComponent(bool drawable) : m_Drawable(drawable) {};
    DrawableComponent(int id) : Components(id, getCompId()){};
    virtual ~DrawableComponent() = default;
    static Components *Create(const int &id) { return new DrawableComponent(id); };
    virtual void modify(bool drawable) { m_Drawable = drawable; }
    virtual void dump() { std::cout << "Drawable = " << std::boolalpha << m_Drawable << std::endl; }
    virtual Components *clone() { return new DrawableComponent(*this); }
    static int getCompId() { return 2; };
};