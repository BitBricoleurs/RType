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
#include "SpriteComponent.hpp"
#include "Shooter.hpp"
#include <cstring>

class SyncChargePos : public GameEngine::ISystem {
  void update(GameEngine::ComponentsContainer &componentsContainer,
              GameEngine::EventHandler &eventHandler) override;
};
