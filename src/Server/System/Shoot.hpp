//
// Created by alexandre on 03/10/23.
//

#pragma once

#include "AABBComponent2D.hpp"
#include "ComponentsType.hpp"
#include "EntityFactory.hpp"
#include "EventHandler.hpp"
#include "ISystem.hpp"
#include "IsBullet.hpp"
#include "PositionComponent2D.hpp"
#include "RectangleColliderComponent2D.hpp"
#include "AABBComponent2D.hpp"
#include "IsBullet.hpp"
#include "EventHandler.hpp"
#include "VelocityComponent.hpp"
#include "Message.hpp"
#include "GameState.hpp"
#include "UserGameMode.hpp"

namespace Server {

    class Shoot : public GameEngine::ISystem {
    public:
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    private:
      bool done = false;

    };
}
