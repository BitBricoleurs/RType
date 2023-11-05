/*
** EPITECH PROJECT, 2023
** RType
** File description:
** BossInScope
*/

#pragma once

#include "BossComponent.hpp"
#include "ComponentsType.hpp"
#include "EventHandler.hpp"
#include "ISystem.hpp"
#include "PositionComponent2D.hpp"

namespace Server {
    class BossInScope : public GameEngine::ISystem {
        public:
            void update(GameEngine::ComponentsContainer &componentsContainer,
            GameEngine::EventHandler &eventHandler) override;

        private:
            bool hasAppeared = false;
    };
}; // namespace Server
