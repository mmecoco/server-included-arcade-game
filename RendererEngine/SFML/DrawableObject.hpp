#pragma once

#include <string>

namespace Eligos
{
    namespace Drawable
    {
        class Object
        {
        public:
            enum class TYPE {
                SPRITE, TEXT
            };
            ~Object() = default;
            virtual void setPosition(float x, float y) = 0;
            virtual void setRotation(float angle) = 0;
            virtual void setScale(float FactorX, float FactorY) = 0;
            virtual void setOrigin(float x, float y) = 0;
            virtual void move(float OffsetX, float OffsetY) = 0;
            virtual const Object *getObject(void) const = 0;
            virtual void setString(const std::string &str) = 0;
            TYPE m_Type;
        };
    } // namespace Drawable
    
} // namespace Eligos
