//
// Created by alexandre on 03/10/23.
//

#pragma once

#include "ISystem.hpp"
#include "ComponentsType.hpp"
#include "SpriteComponent.hpp"
#include "PositionComponent2D.hpp"
#include "RectangleColliderComponent2D.hpp"
#include "AABBComponent2D.hpp"
#include "IsBullet.hpp"
#include "EventHandler.hpp"
#include "ChargeShoot.hpp"
#include "VelocityComponent.hpp"

class Shoot : public GameEngine::ISystem {
    void update(GameEngine::ComponentsContainer &componentsContainer,
                GameEngine::EventHandler &eventHandler) override;
public:

private:
  bool done = false;
};