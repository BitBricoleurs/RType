//
// Created by Bartosz on 10/9/23.
//

#pragma once

#include "ISystem.hpp"
#include "ComponentsType.hpp"


class CollisionHandlerShootAndMobs : public GameEngine::ISystem {
public:
    CollisionHandlerShootAndMobs() = default;

    void update(GameEngine::ComponentsContainer &componentsContainer,
                GameEngine::EventHandler &eventHandler) override;
};