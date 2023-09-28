//
// Created by Bartosz on 9/27/23.
//

#pragma once

#include "AComponent.hpp"
#include "ComponentsType.hpp"
#include "src/UtilsProject/Utils.hpp"

namespace GameEngine {
    class RectangleColliderComponent : public AComponent {
    public:
        RectangleColliderComponent() = default;
        RectangleColliderComponent(const rect& collider) : collider(collider) {}
        ~RectangleColliderComponent() override = default;

        size_t getComponentType() override { return componentType; }
        rect getCollider() const { return collider; }
        void setCollider(const rect& collider) { this->collider = collider; }
    private:
        size_t componentType = ComponentsType::getNewComponentType("RectangleColliderComponent");
        rect collider;
    };
}