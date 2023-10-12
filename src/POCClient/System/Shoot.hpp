//
// Created by Theophilus Homawoo on 12/10/2023.
//

#pragma once

#include "ISystem.hpp"
#include "ComponentsType.hpp"
#include "ComponentContainer.hpp"
#include "EventHandler.hpp"
#include "Utils.hpp"
#include "PositionComponent2D.hpp"
#include "Shooter.hpp"
#include "EntityFactory.hpp"

namespace Client {
    class Shoot : public GameEngine::ISystem {
    public:
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    private:
        size_t createBulletType0(int charge, const GameEngine::Vect2& shootingPosition, GameEngine::ComponentsContainer& componentsContainer, GameEngine::EventHandler& eventHandler);

        size_t createBulletType1(const GameEngine::Vect2& shootingPosition, GameEngine::ComponentsContainer& componentsContainer, GameEngine::EventHandler& eventHandler);
    };
}