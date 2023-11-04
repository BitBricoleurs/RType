//
// Created by alexandre on 30/10/23.
//

#pragma once

#include "ISystem.hpp"
#include "Message.hpp"
#include "PowerUpUtils.hpp"
#include "Vect2.hpp"
#include "EntityFactory.hpp"

namespace Client {

    class CreatePowerUpDual : public GameEngine::ISystem {
    public:
        CreatePowerUpDual() = default;
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    };

}
