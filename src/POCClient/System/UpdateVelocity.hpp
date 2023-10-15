//
// Created by Theophilus Homawoo on 11/10/2023.
//

#pragma once

#include "ISystem.hpp"
#include "EventHandler.hpp"
#include "ComponentsType.hpp"
#include "VelocityComponent.hpp"
#include "Message.hpp"
#include "EntityFactory.hpp"

namespace Client {
    class UpdateVelocity : public GameEngine::ISystem {
    public:
        UpdateVelocity() = default;
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    };
}