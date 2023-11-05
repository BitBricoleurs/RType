/*
** EPITECH PROJECT, 2023
** RType
** File description:
** IsLastMob
*/

#pragma once

#include <cstddef>
#include "ComponentsType.hpp"
#include "AComponent.hpp"

namespace Server {

    class IsLastMob : public GameEngine::AComponent {
        public:
          IsLastMob() = default;

          size_t getComponentType() override;
        protected:
        private:
    };
}