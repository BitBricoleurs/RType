//
// Created by Bartosz on 10/2/23.
//


#include "AComponent.hpp"
#include "CollisionResultComponent.hpp"

namespace GameEngine {

    class AColliderComponent : public AComponent {
    public:
        virtual bool collidesWith(AColliderComponent &other, CollisionResultComponent &result) = 0;
    };
}