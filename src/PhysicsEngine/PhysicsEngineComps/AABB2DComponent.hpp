//
// Created by Bartosz on 9/27/23.
//

#pragma once
#include "AComponent.hpp"
#include "ComponentsType.hpp"
#include "src/UtilsProject/Utils.hpp"

namespace GameEngine {
    class AABB2DComponent : public AComponent {
    public:
        AABB2DComponent() = default;
        AABB2DComponent(const Vect2& min, const Vect2& max) : minExtents(min), maxExtents(max) {}
        ~AABB2DComponent() override = default;

        size_t getComponentType() override { return componentType; }

        Vect2 getMinExtents() const { return minExtents; }
        Vect2 getMaxExtents() const { return maxExtents; }
        void setMinExtents(const Vect2& min) { minExtents = min; }
        void setMaxExtents(const Vect2& max) { maxExtents = max; }

    private:
        size_t componentType = ComponentsType::getNewComponentType("AABBComponent");
        Vect2 minExtents;
        Vect2 maxExtents;
    };

}