/*
** EPITECH PROJECT, 2023
** RType
** File description:
** HeightVariation
*/

#include "HeightVariation.hpp"

namespace Server {
size_t HeightVariation::getComponentType() {
  return GameEngine::ComponentsType::getNewComponentType("HeightVariation");
}
}
