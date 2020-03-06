#include "Texture.hpp"

namespace Eligos
{
    namespace NoDrawable
    {
        bool Texture::loadFromFile(const std::string &filename)
        {
            return m_Texture.loadFromFile(filename);
        }
        bool Texture::loadFromMemory(void *data, std::size_t size)
        {
            return m_Texture.loadFromMemory(data, size);
        }
        const sf::Texture &Texture::getTexture() const
        {
            return m_Texture;
        }
        const NoDrawable::Object *Texture::getObject(void) const
        {
            return this;
        }
    } // namespace NoDrawable
    
} // namespace Eligos
