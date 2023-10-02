//
// Created by Bartosz on 9/27/23.
//

#include "AComponent.hpp"
#include "src/UtilsProject/Utils.hpp"
#include "ComponentsType.hpp"

namespace GameEngine {
    class GravityComponent : public AComponent {
    public:
        GravityComponent() = default;
        GravityComponent(const Vect2& gravity) : gravity(gravity) {}
        ~GravityComponent() override = default;

        size_t getComponentType() override { return componentType; }
        Vect2 getGravity() const { return gravity; }
        void setGravity(const Vect2& gravity) { this->gravity = gravity; }
    private:
        size_t componentType = ComponentsType::getNewComponentType("GravityComponent");
        Vect2 gravity;
    };
}