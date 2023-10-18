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
      componentsContainer, eventHandler, Utils::Vect2(200, 200));
}
