//
// Created by clagasse on 10/30/23.
//

#include "UserGameMode.hpp"

namespace Utils {

    UserGameMode::UserGameMode(State state) : _state(state) {}

    size_t UserGameMode::getComponentType()
    {
        return GameEngine::ComponentsType::getNewComponentType("UserGameMode");
    }
}