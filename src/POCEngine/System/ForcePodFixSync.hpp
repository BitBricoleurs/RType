//
// Created by alexandre on 05/10/23.
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
#include "VelocityComponent.hpp"
#include "PositionComponent2D.hpp"
#include "PhysicsEngineMovementSystem2D.hpp"
#include "IsForcePod.hpp"
#include "Shooter.hpp"

class ForcePodFixSync : public GameEngine::ISystem {
    void update(GameEngine::ComponentsContainer &componentsContainer,
                GameEngine::EventHandler &eventHandler) override;
public:

private:
  bool done = false;
};
