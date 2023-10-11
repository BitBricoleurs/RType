//
// Created by Bartosz on 9/27/23.
//

#include "AComponent.hpp"
#include "Utils.hpp"
#include "ComponentsType.hpp"

namespace GameEngine {
    class GravityComponent : public AComponent {
    public:
        GravityComponent(const Vect2& gravity) : gravity(gravity) {}
        ~GravityComponent() override = default;

        size_t componentType = ComponentsType::getNewComponentType("GravityComponent");
        Vect2 gravity;
    private:
    };
}
