//
// Created by Bartosz on 9/27/23.
//

#pragma once

#include "AComponent.hpp"
#include "ComponentsType.hpp"
#include <vector>
#include "../../UtilsProject/Utils.hpp"

namespace GameEngine {
    class CollisionInfo {
    public:
        size_t collidingEntity;
        Vect2 collisionPoint;
        Vect2 collisionNormal;
        float penetrationDepth;
    };

    class CollisionResultComponent : public AComponent {
    public:

        void addCollision(const CollisionInfo &info) {
            collisions.push_back(info);
        }

        void clearCollisions() {
            collisions.clear();
        }

        bool hasCollisions() const {
            return !collisions.empty();
        }

        size_t getCollisionCount() const {
            return collisions.size();
        }

        std::vector<CollisionInfo> getCollisions() const {
            return collisions;
        }

    private:
        size_t componentType = ComponentsType::getNewComponentType("CollisionResultComponent");
        std::vector <CollisionInfo> collisions;
    };
}