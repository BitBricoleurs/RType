//
// Created by Bartosz on 10/2/23.
//

#include "AComponent.hpp"
#include "ComponentsType.hpp"

namespace GameEngine {
    class MovementComponent : public AComponent {
    public:
        MovementComponent() = default;
        ~MovementComponent() override = default;

        size_t getComponentType() override { return ComponentsType::getNewComponentType("MovementComponent2D"); }
    };
}
