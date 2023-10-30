/*
** EPITECH PROJECT, 2023
** RType
** File description:
** MobComponents
*/

#include "MobComponents.hpp"

namespace Server {

    size_t PataPata::getComponentType() {
      return GameEngine::ComponentsType::getNewComponentType("PataPata");
    }

    size_t Cancer::getComponentType() {
      return GameEngine::ComponentsType::getNewComponentType("Cancer");
    }

    size_t Bug::getComponentType() {
      return GameEngine::ComponentsType::getNewComponentType("Bug");
    }

}
