//
// Created by alexandre on 24/10/23.
//

#pragma once

#include "ISystem.hpp"
#include "Message.hpp"
#include "PowerUpUtils.hpp"
#include "Vect2.hpp"
#include "EntityFactory.hpp"

namespace Client {

    class CreatePowerUp : public GameEngine::ISystem {
    public:
        CreatePowerUp() = default;
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    };

}
