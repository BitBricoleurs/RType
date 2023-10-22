//
// Created by Theophilus Homawoo on 11/10/2023.
//

#pragma once

#include "ISystem.hpp"
#include "ComponentsType.hpp"
#include "ComponentContainer.hpp"
#include "EventHandler.hpp"
#include <unordered_map>

namespace Client {
    class ChangeDirPlayer : public GameEngine::ISystem {
        public:
            ChangeDirPlayer();
            void update(GameEngine::ComponentsContainer &componentsContainer,
                        GameEngine::EventHandler &eventHandler) override;
        private:
            float speed;
            std::unordered_map<std::string, std::pair<float, float>> directionMap;
    };
}
