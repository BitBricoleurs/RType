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

    class CreateForcePod : public GameEngine::ISystem {
    public:
        CreateForcePod() = default;
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    };

}
