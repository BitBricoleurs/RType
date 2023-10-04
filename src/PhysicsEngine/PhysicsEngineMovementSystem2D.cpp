//
// Created by Bartosz on 10/2/23.
//

#include "PhysicsEngineMovementSystem2D.hpp"

namespace GameEngine {

    PhysicsEngineMovementSystem2D::PhysicsEngineMovementSystem2D() {
        engine = std::make_unique<PhysicsEngine>();
    }

    void PhysicsEngineMovementSystem2D::update(ComponentsContainer& componentsContainer, EventHandler& eventHandler) {
        auto entitiesWithMovement = componentsContainer.getEntitiesWithComponent(ComponentsType::getComponentType("MovementComponent2D"));

        for (const auto& entityID : entitiesWithMovement) {

            auto components = componentsContainer.getComponentsFromEntity(entityID);
            for (const auto& componentOpt : components) {
                if (componentOpt.has_value()) { // Vérifie si l'optionnel a une valeur.
                    auto component = componentOpt.value();
                        if (component) { // Vérifie si le pointeur partagé n'est pas nul.
                            //std::cout << "Entity: " << entityID << " Component Type: " << component->getComponentType() << "Type: " << ComponentsType::getComponentName(component->getComponentType()) << std::endl;
                        }
                }
        }

            auto positionOptional = componentsContainer.getComponent(entityID, ComponentsType::getComponentType("PositionComponent2D"));
            auto velocityOptional = componentsContainer.getComponent(entityID, ComponentsType::getComponentType("VelocityComponent"));

            if (positionOptional.has_value() && velocityOptional.has_value()) {
                auto position = std::dynamic_pointer_cast<PositionComponent2D>(positionOptional.value());
                auto velocity = std::dynamic_pointer_cast<VelocityComponent>(velocityOptional.value());

                if (position && velocity) {
                    //std::cout << "velocity" << velocity->velocity.x << "," << velocity->velocity.y << std::endl;
                    engine->moveObject(*position, velocity->velocity);
                }
            }
        }
    }
}
