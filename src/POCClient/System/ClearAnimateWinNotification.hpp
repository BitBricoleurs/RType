//
// Created by Clément Lagasse on 03/11/2023.
//

#pragma once

#include "ComponentsType.hpp"
#include "DeathAnimation.hpp"
#include "EventHandler.hpp"
#include "ISystem.hpp"
#include "SpriteComponent.hpp"
#include "EntityFactory.hpp"
#include "WinNotifAnimation.hpp"

namespace Client {

    class ClearAnimateWinNotification : public GameEngine::ISystem {
    public:
      void update(GameEngine::ComponentsContainer &componentsContainer,
                  GameEngine::EventHandler &eventHandler) override;
    };

}
