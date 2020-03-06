#include "Font.hpp"

namespace Eligos
{
    namespace NoDrawable
    {
        bool Font::loadFromFile(const std::string &filename)
        {
            return m_Font.loadFromFile(filename);
        }
        bool Font::loadFromMemory(void *data, const std::size_t size)
        {
            return m_Font.loadFromMemory(data, size);
        }
        const NoDrawable::Object *Font::getObject() const
        {
            return this;
        }
        const sf::Font &Font::getFont() const
        {
            return m_Font;
        }
    } // namespace NoDrawable
} // namespace Eligos
