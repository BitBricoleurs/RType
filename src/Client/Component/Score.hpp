//
// Created by Theophilus Homawoo on 04/10/2023.
//

#pragma once

#include "AComponent.hpp"
#include "ComponentsType.hpp"

namespace Client {

    class Score : public GameEngine::AComponent {
    public:
        Score() {
            _score = 0;
        }
        ~Score() override = default;

        size_t getComponentType() override;
        int _score;
    };

}
