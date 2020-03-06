#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "NoDrawableObject.hpp"

namespace Eligos
{
    namespace NoDrawable
    {
        class Font : public NoDrawable::Object
        {
        private:
            sf::Font m_Font;

        public:
            Font() = default;
            ~Font() = default;

        public:
            virtual bool loadFromFile(const std::string &filename);
            virtual bool loadFromMemory(void *data, const std::size_t size);
            virtual const NoDrawable::Object *getObject(void) const;
            const sf::Font &getFont(void) const;
        };
    } // namespace NoDrawable
}
// namespace Eligos
