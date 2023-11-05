/*
** EPITECH PROJECT, 2023
** RType
** File description:
** NetworkReceiveFlash
*/

#pragma once

#include "ISystem.hpp"
#include "EventHandler.hpp"
#include "ComponentsType.hpp"
#include "Message.hpp"
#include "EntityFactory.hpp"
#include "SpriteComponent.hpp"

namespace Client {

    class NetworkReceiveFlash : public GameEngine::ISystem {
    public:
        NetworkReceiveFlash() = default;
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    };
}
