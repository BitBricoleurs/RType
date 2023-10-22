/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Script
*/

#include "Script.hpp"

size_t Server::Script::getComponentType() {
  return GameEngine::ComponentsType::getNewComponentType("Script");
}