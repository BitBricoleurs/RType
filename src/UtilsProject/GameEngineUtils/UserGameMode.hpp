//
// Created by clagasse on 10/30/23.
//

#include <cstddef>
#include "AComponent.hpp"
#include "ComponentsType.hpp"

#pragma once

namespace Utils {

    class UserGameMode : public GameEngine::AComponent {
    public:
        enum State {
            ALIVE,
            DEAD,
            SPECTATOR,
        };
      UserGameMode(State state);

      size_t getComponentType() override;
        State _state;
    };
}
