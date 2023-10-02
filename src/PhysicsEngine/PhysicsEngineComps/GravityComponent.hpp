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
        GravityComponent(const Vector2& gravity) : gravity(gravity) {}
        ~GravityComponent() override = default;

        size_t getComponentType() override { return ComponentsType::getNewComponentType("GravityComponent"); }
        Vector2 getGravity() const { return gravity; }
        void setGravity(const Vector2& gravity) { this->gravity = gravity; }
    private:
        Vector2 gravity;
    };
}