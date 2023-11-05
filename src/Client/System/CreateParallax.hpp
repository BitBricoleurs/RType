//
// Created by alexandre on 22/10/23.
//

#pragma once

#include "ISystem.hpp"
#include "EventHandler.hpp"
#include "ComponentsType.hpp"
#include "VelocityComponent.hpp"
#include "Message.hpp"
#include "EntityFactory.hpp"
#include "ParallaxUtils.hpp"

namespace Client {

    class CreateParallax : public GameEngine::ISystem {
    public:
        CreateParallax() = default;
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;

    };

}
