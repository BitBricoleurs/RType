//
// Created by Clément Lagasse on 23/10/2023.
//

#include <cstddef>
#include "AComponent.hpp"
#include "ComponentsType.hpp"

#pragma once

namespace Utils {

    class GameState : public GameEngine::AComponent {
    public:
        enum State {
            WAITING,
            RUNNING,
            WIN,
            LOSE
        };
      GameState(State state);

      size_t getComponentType() override;
        State _state;
    };
}