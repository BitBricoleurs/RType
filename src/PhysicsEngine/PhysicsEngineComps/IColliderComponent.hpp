//
// Created by Bartosz on 10/2/23.
//


#include "AComponent.hpp"
#include "CollisionResultComponent.hpp"

namespace GameEngine {

    class IColliderComponent : public AComponent {
    public:
        virtual bool collidesWith(IColliderComponent &other, CollisionResultComponent &result) = 0;
    };
}