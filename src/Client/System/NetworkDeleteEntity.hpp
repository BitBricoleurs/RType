//
// Created by Clément Lagasse on 14/10/2023.
//

#pragma once

#include "ISystem.hpp"
#include "EventHandler.hpp"
#include "ComponentsType.hpp"
#include "VelocityComponent.hpp"
#include "Message.hpp"
#include "EntityFactory.hpp"

namespace Client {

    class NetworkDeleteEntity : public GameEngine::ISystem {
    public:
        NetworkDeleteEntity() = default;
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    };
}
