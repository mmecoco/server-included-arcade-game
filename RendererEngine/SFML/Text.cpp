#include "Text.hpp"
#include "Font.hpp"

namespace Eligos
{
    namespace Drawable
    {
    Text::Text(const NoDrawable::Font *font, const std::string &text)
    {
        auto RawFont = font->getFont();

        m_Type = TYPE::TEXT;
        m_Text.setFont(RawFont);
        m_Text.setString(text);
        }
        void Text::setPosition(float x, float y)
        {
            m_Text.setPosition(x, y);
        }
        void Text::setRotation(float angle)
        {
            m_Text.setRotation(angle);
        }
        void Text::setScale(float FactorX, float FactorY)
        {
            m_Text, setScale(FactorX, FactorY);
        }
        void Text::setOrigin(float x, float y)
        {
            m_Text.setOrigin(x, y);
        }
        void Text::move(float OffsetX, float OffsetY)
        {
            m_Text.move(OffsetX, OffsetY);
        }
        void Text::setString(const std::string &text)
        {
            m_Text.setString(text);
        }
        void Text::setColor(int r, int g, int b)
        {
            m_Text.setFillColor({sf::Uint8(r), sf::Uint8(g), sf::Uint8(b), 255});
        }
        void Text::setSize(unsigned int size)
        {
            m_Text.setCharacterSize(size);
        }
        const sf::Text &Text::getText() const
        {
            return m_Text;
        }
        const Drawable::Object *Text::getObject() const
        {
            return this;
        }
    } // namespace Drawable
    
} // namespace Eligos
