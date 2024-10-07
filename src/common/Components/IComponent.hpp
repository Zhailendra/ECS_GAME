#pragma once

#include "Types.hpp"

namespace game
{
    class IComponent
    {
        public:
            IComponent();
            virtual ~IComponent() = 0;

            virtual Components getType() const = 0;
            virtual void setType(Components type) = 0;
        protected:
            Components _type;
    };
}