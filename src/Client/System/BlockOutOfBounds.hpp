/*
** EPITECH PROJECT, 2023
** RType
** File description:
** AnimateOnMove
*/

#pragma once

#include "ComponentsType.hpp"
#include "EventHandler.hpp"
#include "ISystem.hpp"
#include "SpriteAnimation.hpp"
#include "SpriteComponent.hpp"
#include "VelocityComponent.hpp"
#include "PositionComponent2D.hpp"
#include "EntityFactory.hpp"
#include "IMessage.hpp"
#include "IsPlayer.hpp"
#include "Message.hpp"

namespace Client {

    class BlockOutOfBounds : public GameEngine::ISystem {
    public:
      void update(GameEngine::ComponentsContainer &componentsContainer,
                  GameEngine::EventHandler &eventHandler) override;
    };

}