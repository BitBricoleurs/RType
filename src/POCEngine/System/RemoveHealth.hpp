//
// Created by Theophilus Homawoo on 04/10/2023.
//

#pragma once

#include "ISystem.hpp"
#include "SpriteComponent.hpp"
#include "EventHandler.hpp"
#include "Health.hpp"

class RemoveHealth : public GameEngine::ISystem {
public:
    void update(GameEngine::ComponentsContainer& componentsContainer, GameEngine::EventHandler& eventHandler) override;
};

