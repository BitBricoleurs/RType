/*
** EPITECH PROJECT, 2023
** RType
** File description:
** NetworkReceiveLifeLost
*/

#pragma once

#include "ISystem.hpp"
#include "EventHandler.hpp"
#include "ComponentsType.hpp"
#include "Message.hpp"
#include "EntityFactory.hpp"
#include "SpriteComponent.hpp"

namespace Client {

    class NetworkReceiveLifeLost : public GameEngine::ISystem {
    public:
        NetworkReceiveLifeLost() = default;
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    private:
        bool dead = false;
    };
}
