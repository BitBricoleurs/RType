/*
** EPITECH PROJECT, 2023
** RType
** File description:
** ActivateCharge
*/

#pragma once

#include "ComponentsType.hpp"
#include "Message.hpp"
#include "EventHandler.hpp"
#include "ISystem.hpp"
#include "SpriteComponent.hpp"
#include "EntityFactory.hpp"
#include "UserMessage.hpp"

namespace Client {

    class ActivateCharge : public GameEngine::ISystem {
    public:
      void update(GameEngine::ComponentsContainer &componentsContainer,
                  GameEngine::EventHandler &eventHandler) override;
    };

}
