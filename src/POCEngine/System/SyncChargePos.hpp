/*
** EPITECH PROJECT, 2023
** RType
** File description:
** SyncChargePos
*/

#pragma once

#include "ChargeShoot.hpp"
#include "EventHandler.hpp"
#include "ISystem.hpp"
#include "PositionComponent2D.hpp"

class SyncChargePos : public GameEngine::ISystem {
  void update(GameEngine::ComponentsContainer &componentsContainer,
              GameEngine::EventHandler &eventHandler) override;
};
