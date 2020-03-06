#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "NoDrawableObject.hpp"

namespace Eligos
{
    namespace NoDrawable
    {
        class Texture : public NoDrawable::Object
        {
        private:
            sf::Texture m_Texture;

        public:
            Texture() = default;
            virtual ~Texture() = default;
            Texture(const Texture &) = delete;

        public:
            virtual bool loadFromFile(const std::string &filename);
            virtual bool loadFromMemory(void *data, std::size_t size);
            virtual const NoDrawable::Object *getObject(void) const;
            const sf::Texture &getTexture(void) const;
        };
    } // namespace NoDrawable
} // namespace Eligos
