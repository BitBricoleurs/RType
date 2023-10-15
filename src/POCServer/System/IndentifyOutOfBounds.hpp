//
// Created by Theophilus Homawoo on 15/10/2023.
//

#pragma once

#include "ISystem.hpp"
#include "ComponentsType.hpp"
#include "PositionComponent2D.hpp"
#include "EventHandler.hpp"
#include <map>

namespace Server {
    class IndentifyOutOfBounds : public GameEngine::ISystem {
        public:
            void update(GameEngine::ComponentsContainer &componentsContainer,
                        GameEngine::EventHandler &eventHandler) override;
        private:
            int _width = 1920;
            int _height = 1080;
            int _offset = 100;
            std::map<size_t, int> _idTimer;
    };
}