/*
** EPITECH PROJECT, 2023
** RType
** File description:
** BugDirectionChange
*/

#pragma once

#include "ISystem.hpp"
#include "EventHandler.hpp"
#include "ComponentsType.hpp"
#include "PositionComponent2D.hpp"
#include "VelocityComponent.hpp"
#include "Vect2.hpp"
#include "MobComponents.hpp"
#include "EntityFactory.hpp"

namespace Server {

    class BugDirectionChange : public GameEngine::ISystem {
    public:
        void update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) override;
    };
}
