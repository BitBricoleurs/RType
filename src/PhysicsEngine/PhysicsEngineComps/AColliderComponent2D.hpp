//
// Created by Bartosz on 10/2/23.
//

#pragma once
#include "AComponent.hpp"

namespace GameEngine {

    class AColliderComponent2D : public AComponent {
    public:
        virtual bool collidesWith(AColliderComponent2D &other) = 0;
    };
}
