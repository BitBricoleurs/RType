/*
** EPITECH PROJECT, 2023
** RType
** File description:
** BugDirectionChange
*/

#include "BugDirectionChange.hpp"

namespace Server {

    void BugDirectionChange::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
        try {
            size_t bugId = std::any_cast<size_t>(eventHandler.getTriggeredEvent().second);

            auto bugComponentOpt = componentsContainer.getComponent(bugId, GameEngine::ComponentsType::getComponentType("Bug"));
            auto velocityComponentOpt = componentsContainer.getComponent(bugId, GameEngine::ComponentsType::getComponentType("VelocityComponent"));
            auto positionComponentOpt = componentsContainer.getComponent(bugId, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));

            if (!bugComponentOpt.has_value() || !velocityComponentOpt.has_value() || !positionComponentOpt.has_value())
                return;

            auto bug = std::static_pointer_cast<Bug>(bugComponentOpt.value());
            auto velocity = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(velocityComponentOpt.value());
            auto position = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(positionComponentOpt.value());

            auto &factory = EntityFactory::getInstance();

            if (position->pos.x > bug->directionChangePoints[bug->currentDestinationI].x - 10 && position->pos.x < bug->directionChangePoints[bug->currentDestinationI].x + 10 &&
                position->pos.y > bug->directionChangePoints[bug->currentDestinationI].y - 10 && position->pos.y < bug->directionChangePoints[bug->currentDestinationI].y + 10) {
                //reached  destination
                bug->currentDestinationI++;
                if (bug->currentDestinationI >= bug->directionChangePoints.size()) {
                    //has no more destinations, move out of screen
                    velocity->velocity = Utils::Vect2(-6, 0);
                    factory.updateEntityNetworkWithVelocity(eventHandler, bugId, velocity->velocity);
                    return;
                }
                Utils::Vect2 directionToDestination = bug->directionChangePoints[bug->currentDestinationI] - position->pos;
                float maxVal = std::max(std::abs(directionToDestination.x),
                                        std::abs(directionToDestination.y));
                float scaleFactor = 6.0f / maxVal;
                Utils::Vect2 newVelocity = directionToDestination * scaleFactor;
                velocity->velocity = newVelocity;
                factory.updateEntityNetworkWithVelocity(eventHandler, bugId, velocity->velocity);
            } else if (bug->currentDestinationI >= bug->directionChangePoints.size()) {
                return;
            } else {
                // check if velocity is in the right direction if not update the entity's velocity
                Utils::Vect2 directionToDestination = bug->directionChangePoints[bug->currentDestinationI] - position->pos;
                float maxVal = std::max(std::abs(directionToDestination.x),
                                        std::abs(directionToDestination.y));
                float scaleFactor = 6.0f / maxVal;
                Utils::Vect2 newVelocity = directionToDestination * scaleFactor;
                if (newVelocity.x != velocity->velocity.x || newVelocity.y != velocity->velocity.y) {
                    velocity->velocity = newVelocity;
                    factory.updateEntityNetworkWithVelocity(eventHandler, bugId, velocity->velocity);
                }
            }
        } catch (std::bad_any_cast &e) {
            std::cerr << "Error from BugDirectionChange System " << e.what() << std::endl;
        }
    }
}