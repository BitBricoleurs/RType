//
// Created by Bartosz on 9/27/23.
//

#include "AComponent.hpp"
#include "Vect2.hpp"
#include "ComponentsType.hpp"

namespace PhysicsEngine {
    class GravityComponent : public GameEngine::AComponent {
    public:
        GravityComponent(const Utils::Vect2& gravity) : gravity(gravity) {}
        ~GravityComponent() override = default;

        size_t componentType = GameEngine::ComponentsType::getNewComponentType("GravityComponent");
        Utils::Vect2 gravity;
    private:
    };
}
