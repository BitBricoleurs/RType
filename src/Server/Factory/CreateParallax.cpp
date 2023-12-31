/*
** EPITECH PROJECT, 2023
** RType
** File description:
** CreateNewBullet
*/

#include "EntityFactory.hpp"

namespace Server {

    size_t EntityFactory::CreateParallax(GameEngine::ComponentsContainer &container, GameEngine::EventHandler &eventHandler, Utils::Vect2 pos, float speed, float layer, ParallaxType type, bool isLooping)
    {
        size_t entityId = container.createEntity();


        auto parallaxComponent = std::make_shared<IsParallax>(layer, isLooping, type);
        auto positionComponent = std::make_shared<PhysicsEngine::PositionComponent2D>(pos);


        auto velocity = Utils::Vect2(speed, 0);
        auto velocityComponent = std::make_shared<PhysicsEngine::VelocityComponent>(velocity);
        auto movementComponent = std::make_shared<PhysicsEngine::MovementComponent>();
        container.bindComponentToEntity(entityId, parallaxComponent);
        container.bindComponentToEntity(entityId, positionComponent);
        container.bindComponentToEntity(entityId, velocityComponent);
        container.bindComponentToEntity(entityId, movementComponent);

        std::vector<size_t> ids = {entityId};
        std::vector<std::any> args = {static_cast<int>(type), static_cast<int>(pos.x * 1000), static_cast<int>(pos.y * 1000), static_cast<int>(speed * 1000), static_cast<int>(layer)};
        std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("CREATED_PARALLAX", ids, "INT", args);
        std::shared_ptr<Network::AllUsersMessage> allUserMsg = std::make_shared<Network::AllUsersMessage>(message);
        eventHandler.queueEvent("SEND_NETWORK", allUserMsg);
        EntityFactory::getInstance().updateEntityNetwork(eventHandler, entityId, pos, velocity);


        return entityId;
    }
    size_t EntityFactory::spawnParallax(GameEngine::ComponentsContainer & container, GameEngine::EventHandler & eventHandler, Utils::Vect2 pos, float speed, float layer, ParallaxType type, bool isLooping)
    {
        return CreateParallax(container, eventHandler, pos, speed, layer, type, isLooping);
    }
}
