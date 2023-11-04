//
// Created by alexandre on 30/10/23.
//

#pragma once

#include "ISystem.hpp"
#include "ComponentContainer.hpp"
#include "ComponentsType.hpp"
#include "EventHandler.hpp"
#include "EntityFactory.hpp"

namespace Server {
    class PowerUpDualShoot : public GameEngine::ISystem {
    public:
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    };
}
