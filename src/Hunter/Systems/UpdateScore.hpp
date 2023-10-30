/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Score
*/

#pragma once

#include "EventHandler.hpp"
#include "ISystem.hpp"
#include "Score.hpp"
#include "TextComponent.hpp"

class UpdateScore : public GameEngine::ISystem {
  void update(GameEngine::ComponentsContainer &componentsContainer,
              GameEngine::EventHandler &eventHandler) override;
};
