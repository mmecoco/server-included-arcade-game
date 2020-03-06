#include "Sprite.hpp"
#include "Texture.hpp"

namespace Eligos
{
    namespace Drawable
    {
        Sprite::Sprite(Eligos::Drawable::Object *sprite)
        {
            m_Type = TYPE::SPRITE;
            Sprite *plop = (Sprite *)sprite;
            m_Sprite.setTexture(*plop->m_Sprite.getTexture());
        }

        Sprite::Sprite(Sprite &sprite)
        {
            exit(0);
            m_Type = TYPE::SPRITE;
            m_Sprite.setTexture(*sprite.m_Sprite.getTexture());
        }

        Sprite::Sprite(NoDrawable::Texture *Texture) {
            auto &RawTexture = Texture->getTexture();

            m_Type = TYPE::SPRITE;
            m_Sprite.setTexture(RawTexture);
            m_Sprite.setOrigin(RawTexture.getSize().x / 2, RawTexture.getSize().y / 2);
        }
        void Sprite::setPosition(float x, float y)
        {
            m_Sprite.setPosition(x, y);
        }
        void Sprite::setRotation(float angle)
        {
            m_Sprite.setRotation(angle);
        }
        void Sprite::setScale(float FactorX, float FactorY)
        {
            m_Sprite.setScale(FactorX, FactorY);
        }
        void Sprite::setOrigin(float x, float y)
        {
            m_Sprite.setOrigin(x, y);
        }
        void Sprite::move(float OffsetX, float OffsetY)
        {
            m_Sprite.move(OffsetX, OffsetY);
        }
        const Drawable::Object *Sprite::getObject() const
        {
            return this;
        }
        const sf::Sprite &Sprite::getSprite() const
        {
            return m_Sprite;
        }
    } // namespace Drawable
} // namespace Eligos
