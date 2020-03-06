#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "../Drawable.hpp"
#include "DrawableObject.hpp"

namespace Eligos
{
    namespace Drawable
    {
        class Text : public Drawable::Object
        {
        private:
            sf::Text m_Text;

        public:
            Text(const NoDrawable::Font *font, const std::string &text = "default");
            ~Text() = default;

        public:
            virtual void setPosition(float x, float y);
            virtual void setRotation(float angle);
            virtual void setSize(unsigned int);
            virtual void setScale(float FactorX, float FactorY);
            virtual void setColor(int r, int g, int b);
            virtual void setString(const std::string &string);
            virtual void setOrigin(float x, float y);
            virtual void move(float OffsetX, float OffsetY);
            virtual const Drawable::Object *getObject() const;
            const sf::Text &getText() const;
        };
    } // namespace Drawable

} // namespace Eligos
