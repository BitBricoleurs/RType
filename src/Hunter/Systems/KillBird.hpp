/*
** EPITECH PROJECT, 2023
** RType
** File description:
** KillBird
*/

#pragma once

#include "ButtonComponent.hpp"
#include "ComponentsType.hpp"
#include "EventHandler.hpp"
#include "ISystem.hpp"
#include "VelocityComponent.hpp"

class KillBird : public GameEngine::ISystem {
public:
  void update(GameEngine::ComponentsContainer &componentsContainer,
              GameEngine::EventHandler &eventHandler) override;
};
