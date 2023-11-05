//
// Created by Clément Lagasse on 24/10/2023.
//

#pragma once

#include "ISystem.hpp"
#include "ComponentsType.hpp"
#include "EventHandler.hpp"
#include "LoadConfig.hpp"

namespace Client {
    class InitScreenConnect : public GameEngine::ISystem {
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    public:

    private:
       bool _done = false;
    };

}
