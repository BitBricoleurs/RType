//
// Created by alexandre on 03/10/23.
//

#pragma once

#include "ISystem.hpp"
#include "EventHandler.hpp"
#include "ComponentsType.hpp"
#include "SpriteAnimation.hpp"
#include "VelocityComponent.hpp"
#include "SpriteComponent.hpp"

namespace Client {
    class updateEntitySprite : public GameEngine::ISystem {
    public:
      void update(GameEngine::ComponentsContainer &componentsContainer,
                  GameEngine::EventHandler &eventHandler) override;
    };
}
