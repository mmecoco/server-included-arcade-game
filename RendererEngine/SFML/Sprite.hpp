#pragma once

#include <SFML/Graphics.hpp>
#include "../Drawable.hpp"
#include "DrawableObject.hpp"

namespace Eligos {
    namespace Drawable {
        class Sprite : public Drawable::Object
        {
            private:
                sf::Sprite m_Sprite;

            public:
                Sprite(Eligos::Drawable::Object *);
                Sprite(NoDrawable::Texture *Texture);
                virtual ~Sprite() = default;
                Sprite(Sprite &sprite);

            public:
                virtual void setPosition(float x, float y);
                virtual void setRotation(float angle);
                virtual void setScale(float FactorX, float FactorY);
                virtual void setOrigin(float x, float y);
                virtual void move(float OffsetX, float OffsetY);
                virtual const Drawable::Object *getObject() const;
                const sf::Sprite &getSprite(void) const;
                virtual void setString(const std::string &str) {};
        };
    } // namespace Drawable
} // namespace Eligos