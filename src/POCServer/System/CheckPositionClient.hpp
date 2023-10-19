//
// Created by Clément Lagasse on 13/10/2023.
//

#pragma once

#include "EventHandler.hpp"
#include "ISystem.hpp"
#include "Message.hpp"
#include "UserMessage.hpp"
#include "ComponentsType.hpp"
#include "PositionComponent2D.hpp"
#include "Shooter.hpp"

class CheckPositionClient : public GameEngine::ISystem {
    public:
        CheckPositionClient() = default;
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    private:

};

