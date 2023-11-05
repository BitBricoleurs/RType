//
// Created by Theophilus Homawoo on 05/10/2023.
//

#pragma once

#include "Score.hpp"
#include "TextComponent.hpp"
#include "ISystem.hpp"
#include "EventHandler.hpp"
#include "ComponentsType.hpp"
#include "ComponentContainer.hpp"
#include "Message.hpp"

namespace Client {
    class UpdateScore : public GameEngine::ISystem {
        void update(GameEngine::ComponentsContainer& componentsContainer, GameEngine::EventHandler& eventHandler) override;
    };
}