/*
** EPITECH PROJECT, 2023
** RType
** File description:
** BossComponent
*/

#include "BossComponent.hpp"

namespace Client {

isBossCore::isBossCore() {}

size_t isBossCore::getComponentType() {
  return GameEngine::ComponentsType::getNewComponentType("isBossCore");
}

isBossPod::isBossPod() {
  launched = false;
  bounces = 0;
}

size_t isBossPod::getComponentType() {
  return GameEngine::ComponentsType::getNewComponentType("isBossPod");
}

}