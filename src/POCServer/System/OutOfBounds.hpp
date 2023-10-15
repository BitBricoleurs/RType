//
// Created by Theophilus Homawoo on 15/10/2023.
//

#pragma once

#include "ISystem.hpp"
#include "EventHandler.hpp"
#include "ComponentsType.hpp"
#include "PositionComponent2D.hpp"
#include "Message.hpp"
#include "UserMessage.hpp"

namespace Server {
    class OutOfBounds : public GameEngine::ISystem {
        public:
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
        private:
            int _width = 1920;
            int _height = 1080;
            int _offset = 100;
    };
}