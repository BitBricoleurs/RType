//
// Created by Clément Lagasse on 02/11/2023.
//

#pragma once

#include "ISystem.hpp"
#include "ComponentsType.hpp"
#include "EventHandler.hpp"

namespace Client {

    class InitNotification : public GameEngine::ISystem {
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    public:

    private:
      bool done = false;
    };

}
