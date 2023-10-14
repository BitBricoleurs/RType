//
// Created by Theophilus Homawoo on 11/10/2023.
//

#pragma once

#include "ISystem.hpp"
#include "EventHandler.hpp"
#include "ComponentsType.hpp"
#include "PositionComponent2D.hpp"
#include "Message.hpp"
#include "EntityFactory.hpp"

namespace Client {
    class UpdatePosition : public GameEngine::ISystem {
    public:
        UpdatePosition() = default;
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    };
}