//
// Created by Clément Lagasse on 25/10/2023.
//

#pragma once

#include "ComponentsType.hpp"
#include "DeathAnimation.hpp"
#include "EventHandler.hpp"
#include "ISystem.hpp"
#include "SpriteComponent.hpp"
#include "EntityFactory.hpp"
#include "IsButtonConnect.hpp"
#include "ButtonComponent.hpp"
#include <regex>

namespace Client {

    class ActionButtonConnectClick : public GameEngine::ISystem {
    public:
      void update(GameEngine::ComponentsContainer &componentsContainer,
                  GameEngine::EventHandler &eventHandler) override;
    };
    bool isIpValid (const std::string &ip);
    bool isPortValid (const std::string &port);

}
