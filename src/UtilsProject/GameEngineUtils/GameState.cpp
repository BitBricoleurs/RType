//
// Created by Clément Lagasse on 23/10/2023.
//

#include "GameState.hpp"

namespace Utils {

    GameState::GameState(State state) : _state(state) {}

    size_t GameState::getComponentType()
    {
        return GameEngine::ComponentsType::getNewComponentType("GameState");
    }
}
