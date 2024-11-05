/*
** PROJECT, 2024
** CPP_POOL
** File description:
** Entity.hpp
*/

#pragma once

#include <iostream>
#include <type_traits>
#include <algorithm>
#include <memory>
#include <list>
#include <cstdint>

#include "AComponent.hpp"

namespace game {

    extern bool displayText;

    class Entity {
        public:
            Entity(std::uint32_t id);
            ~Entity();

            std::uint32_t getId() const;
            void setId(std::uint32_t id);

            template<class T> bool hasComponent() {
                static_assert(std::is_base_of<AComponent, T>::value, "It must inherit from AComponent");
                T comp;

                for (auto &elem : _components) {
                    if (elem.get()->getType() == comp.getType())
                        return true;
                }
                return false;
            }

            template<class T> bool hasType(Components type) {
                for (auto &elem : _components) {
                    if (elem.get()->getType() == type)
                        return true;
                }
                return false;
            }

            template<class T> T &getComponent() {
                static_assert(std::is_base_of<AComponent, T>::value, "It must inherit from AComponent");
                T comp;

                for (auto &elem : _components) {
                    if (elem.get()->getType() == comp.getType())
                        return *std::dynamic_pointer_cast<T>(elem);
                }
                throw std::runtime_error("Component not found");
            }

            template<class T> void addComponent(T component) {
                static_assert(std::is_base_of<AComponent, T>::value, "It must inherit from AComponent");

                if (hasComponent<T>())
                    return;
                _components.push_back(std::make_shared<T>(component));
            }

            template<class T> void removeComponent() {
                static_assert(std::is_base_of<AComponent, T>::value, "It must inherit from AComponent");
                T comp;

                if (!hasComponent<T>())
                    return;
                _components.remove_if([&](std::shared_ptr<AComponent> elem) {
                    return elem.get()->getType() == comp.getType();
                });
            }

        protected:
            template <class A, class B, class... Other> bool hasComponent();
        private:
            std::uint32_t _id;
            std::list<std::shared_ptr<AComponent>> _components;
    };

};