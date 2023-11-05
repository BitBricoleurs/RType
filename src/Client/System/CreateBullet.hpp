//
// Created by Clément Lagasse on 11/10/2023.
//

#pragma once

#include "ISystem.hpp"
#include "EventHandler.hpp"
#include "ComponentsType.hpp"
#include "VelocityComponent.hpp"
#include "Message.hpp"
#include "EntityFactory.hpp"
#include "BulletUtils.hpp"

namespace Client {

    class CreateBullet : public GameEngine::ISystem {
    public:
        CreateBullet() = default;
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    };

}
