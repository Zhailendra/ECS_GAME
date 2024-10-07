/*
** PROJECT, 2023
**
** File description:
** Exception.hpp
*/

#pragma once

#include "Includes.hpp"

namespace game {
    class Error : public std::exception {
        public:
            explicit Error(std::string msg) : _msg(std::move(msg))
            {};

            const char *what() const noexcept override
                    {
                            return (_msg.c_str());
                    }

        protected:
            const std::string _msg;
    };

}
