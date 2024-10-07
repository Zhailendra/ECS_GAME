/*
** PROJECT, 2024
** CPP_POOL
** File description:
** AComponent.hpp
*/

#pragma once

#include <iostream>
#include "IComponent.hpp"

namespace game {
    class AComponent : public IComponent {
        public:
            AComponent();
            virtual ~AComponent() override = default;

            virtual Components getType() const final;
            virtual void setType(Components type) final;

        protected:
            Components _type;
    };
}