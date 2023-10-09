/*
** EPITECH PROJECT, 2023
** RType
** File description:
** SpawnMob
*/

#include "SpawnMob.hpp"

void SpawnMob::update(GameEngine::ComponentsContainer &componentsContainer,
                      GameEngine::EventHandler &eventHandler) {

  int random = rand() % 2 + 1;
  int randomY = rand() % 950;
  if (random == 1)
    EntityFactory::getInstance().spawnCancerMob(
        componentsContainer, eventHandler, GameEngine::Vect2(2000, randomY),
        GameEngine::Vect2(-2, 0));
  else if (random == 2) {
    EntityFactory::getInstance().spawnPataPataMob(
        componentsContainer, eventHandler, GameEngine::Vect2(2000, randomY),
        GameEngine::Vect2(-4, 0));
  }
}
