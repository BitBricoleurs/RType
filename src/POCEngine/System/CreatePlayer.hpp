/*
** EPITECH PROJECT, 2023
** RType
** File description:
** CreatePlayer
*/

#pragma once
#include "ComponentsType.hpp"
#include "EntityFactory.hpp"
#include "ISystem.hpp"
#include "Utils.hpp"
#include <iostream>

class CreatePlayer : public GameEngine::ISystem {
public:
  void update(GameEngine::ComponentsContainer &componentsContainer,
              GameEngine::EventHandler &eventHandler) override;
};
