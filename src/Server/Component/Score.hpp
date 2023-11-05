/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Score
*/

#pragma once

#include <cstddef>
#include "ComponentsType.hpp"
#include "AComponent.hpp"
#include "Vect2.hpp"

namespace Server {

    class Score : public GameEngine::AComponent {
    public:
        Score() : score(0) {};

        size_t getComponentType() override;

        size_t score;
    };
}