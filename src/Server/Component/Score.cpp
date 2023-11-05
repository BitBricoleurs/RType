/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Score
*/

#include "Score.hpp"

size_t Server::Score::getComponentType()
{
    return GameEngine::ComponentsType::getNewComponentType("Score");
}
