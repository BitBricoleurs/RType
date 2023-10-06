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
#include "VelocityComponent.hpp"
#include "AudioComponent.hpp"

class Shoot : public GameEngine::ISystem {
public:
    void update(GameEngine::ComponentsContainer &componentsContainer,
                GameEngine::EventHandler &eventHandler) override;
private:
    std::shared_ptr<GameEngine::AudioComponent> shootSound = std::make_shared<GameEngine::AudioComponent>("assets/music/Shoot.wav");
  bool done = false;
};