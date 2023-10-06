/*
** EPITECH PROJECT, 2023
** RType
** File description:
** CreatePlayer
*/

#include "CreatePlayer.hpp"

void CreatePlayer::update(GameEngine::ComponentsContainer &componentsContainer,
                          GameEngine::EventHandler &eventHandler) {

  EntityFactory::getInstance().createNewPlayer(
      componentsContainer, eventHandler, GameEngine::Vect2(0, 0),
      GameEngine::Vect2(-2, 0));
}
