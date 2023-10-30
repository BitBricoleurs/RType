//
// Created by Bartosz on 9/27/23.
//

#include "PhysicsEngineCollisionSystem2D.hpp"

namespace PhysicsEngine {

    PhysicsEngineCollisionSystem2D::PhysicsEngineCollisionSystem2D()
            : physicsEngine(std::make_unique<PhysicsEngine>()) {}

    PhysicsEngineCollisionSystem2D::~PhysicsEngineCollisionSystem2D() = default;

    void PhysicsEngineCollisionSystem2D::update(GameEngine::ComponentsContainer& componentsContainer, GameEngine::EventHandler& eventHandler) {
        potentialCollisions.clear();

        auto entitiesWithAABB = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getComponentType("AABBComponent2D"));

        for (size_t i = 0; i < entitiesWithAABB.size(); i++) {
            for (size_t j = i + 1; j < entitiesWithAABB.size(); j++) {
                auto optAABB1 = componentsContainer.getComponent(entitiesWithAABB[i], GameEngine::ComponentsType::getComponentType("AABBComponent2D"));
                auto optAABB2 = componentsContainer.getComponent(entitiesWithAABB[j], GameEngine::ComponentsType::getComponentType("AABBComponent2D"));

                if (!optAABB1 || !optAABB2) continue;

                auto aabb1 = std::dynamic_pointer_cast<AABBComponent2D>(*optAABB1);
                auto aabb2 = std::dynamic_pointer_cast<AABBComponent2D>(*optAABB2);

                if (!aabb1 || !aabb2) continue;

                if (physicsEngine->broadPhase(*aabb1, *aabb2)) {
                    size_t smaller = std::min(entitiesWithAABB[i], entitiesWithAABB[j]);
                    size_t larger = std::max(entitiesWithAABB[i], entitiesWithAABB[j]);
                    potentialCollisions.emplace_back(smaller, larger);
                }
            }
        }
        for (const auto& pair : potentialCollisions) {
            auto optCollider1 = componentsContainer.getComponent(pair.first, GameEngine::ComponentsType::getNewComponentType("AColliderComponent2D"));
            auto optPosition1 = componentsContainer.getComponent(pair.first, GameEngine::ComponentsType::getNewComponentType("PositionComponent2D"));
            auto optCollider2 = componentsContainer.getComponent(pair.second, GameEngine::ComponentsType::getNewComponentType("AColliderComponent2D"));
            auto optPosition2 = componentsContainer.getComponent(pair.second, GameEngine::ComponentsType::getNewComponentType("PositionComponent2D"));

            if (!optCollider1.has_value() || !optPosition1.has_value() || !optCollider2.has_value() || !optPosition2.has_value()) continue;

            auto collider1Opt = std::dynamic_pointer_cast<AColliderComponent2D>(optCollider1.value());
            auto position1Opt = std::dynamic_pointer_cast<PositionComponent2D>(optPosition1.value());
            auto collider2Opt = std::dynamic_pointer_cast<AColliderComponent2D>(optCollider2.value());
            auto position2Opt = std::dynamic_pointer_cast<PositionComponent2D>(optPosition2.value());


            std::pair<std::shared_ptr<AColliderComponent2D>, PositionComponent2D> pair1(collider1Opt, *position1Opt);
            std::pair<std::shared_ptr<AColliderComponent2D>, PositionComponent2D> pair2(collider2Opt, *position2Opt);

            if (physicsEngine->narrowPhase(pair1, pair2)) {
                eventHandler.queueEvent("Collision", std::make_pair(pair.first, pair.second));
            }
        }
    }
}
