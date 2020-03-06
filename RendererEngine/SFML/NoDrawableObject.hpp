#pragma once

#include <string>

namespace Eligos
{
    namespace NoDrawable
    {
        class Object
        {
        public:
            virtual ~Object() = default;
            virtual bool loadFromFile(const std::string &filename) = 0;
            virtual bool loadFromMemory(void *data, const std::size_t size) = 0;
            virtual const Object *getObject(void) const = 0;
        };
    } // namespace NoDrawable

} // namespace Eligos
