//
// Created by Theophilus Homawoo on 11/10/2023.
//

#include "UpdatePosition.hpp"

namespace Client {

    void UpdatePosition::update(GameEngine::ComponentsContainer &componentsContainer,
                        GameEngine::EventHandler &eventHandler) {
        try {
           std::shared_ptr<Network::OwnedMessage> message;

            try {
                message = std::any_cast<std::shared_ptr<Network::OwnedMessage>>(eventHandler.getTriggeredEvent().second);
            } catch (std::bad_any_cast &e) {
                    std::cerr << "Error from UpdatePosition System " << e.what() << std::endl;
                    return ;
            }
            std::shared_ptr<Network::IMessage> IMessage = message->message;
            std::shared_ptr<Network::Message> messageData = std::make_shared<Network::Message>(IMessage->getMessage());

            std::vector<size_t> ids = messageData->getIDs();
            std::vector<std::any> args = messageData->getArgs();


            if (ids.size() != 1 || args.size() != 2)
                return;
            EntityFactory &factory = EntityFactory::getInstance();
            for (auto &id : ids) {

                size_t entityToUpdate = factory.getClientId(id);
                auto positionComponent = componentsContainer.getComponent(entityToUpdate, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
                if (!positionComponent.has_value())
                    return;
                Utils::Vect2 targetPosition(std::any_cast<float>(args[0]), std::any_cast<float>(args[1]));

                auto position = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(positionComponent.value());
                float distance = position->pos.distanceTo(targetPosition);

                if (isEntityMotionless(componentsContainer, entityToUpdate) && isEntityChangedPosition(componentsContainer, entityToUpdate, targetPosition)) {
                    trySmoothingPosition(componentsContainer, entityToUpdate, targetPosition);
                    return;
                } else if (isEntitySmoothing(componentsContainer, entityToUpdate, targetPosition)) {
                    return;
                } else {
                    tryRemovingSmoothing(componentsContainer, entityToUpdate);
                }
                if (distance > 50 && !isEntityPlayer(componentsContainer, entityToUpdate)) {
                    position->pos = targetPosition;
                }
            }
        } catch (std::bad_any_cast &e) {
            std::cerr << "Error from UpdatePosition System " << e.what() << std::endl;
        }
    }

} // namespace Client

bool Client::UpdatePosition::isEntityMotionless(GameEngine::ComponentsContainer &componentsContainer, size_t entity)
{
    auto velocityComponent = componentsContainer.getComponent(entity, GameEngine::ComponentsType::getComponentType("VelocityComponent"));
    if (!velocityComponent.has_value())
        return false;
    auto velocity = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(velocityComponent.value());
    return (velocity->velocity.x == 0 && velocity->velocity.y == 0);
}

void Client::UpdatePosition::trySmoothingPosition(GameEngine::ComponentsContainer &componentsContainer, size_t entity, Utils::Vect2 &targetPosition)
{
    auto smoothingType = GameEngine::ComponentsType::getComponentType("SmoothingMovement");
    auto smoothing = componentsContainer.getComponent(entity, smoothingType);
    if (smoothing.has_value()) {
        auto smoothingComp = std::static_pointer_cast<Client::SmoothingMovement>(smoothing.value());
        if (targetPosition.y != smoothingComp->_targetPosition.y && targetPosition.x != smoothingComp->_targetPosition.x) {
            smoothingComp->_targetPosition = targetPosition;
        }
        return;
    }
    auto smoothingComp = std::make_shared<SmoothingMovement>(targetPosition);
    componentsContainer.bindComponentToEntity(entity, smoothingComp);
    smoothPosition(componentsContainer, entity, targetPosition);
    std::cout << "Start Smoothing" << std::endl;
}

void Client::UpdatePosition::tryRemovingSmoothing(GameEngine::ComponentsContainer &componentsContainer, size_t entity)
{
    auto smoothingType = GameEngine::ComponentsType::getComponentType("SmoothingMovement");
    auto smoothing = componentsContainer.getComponent(entity, smoothingType);
    if (smoothing.has_value()) {
        auto velocityComponent = componentsContainer.getComponent(entity, GameEngine::ComponentsType::getComponentType("VelocityComponent"));
        if (!velocityComponent.has_value())
            return;
        auto velComp = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(velocityComponent.value());
        velComp->velocity.x = 0;
        velComp->velocity.y = 0;
        componentsContainer.unbindComponentFromEntity(entity, smoothingType);

    }
}

bool Client::UpdatePosition::isEntitySmoothing(GameEngine::ComponentsContainer &componentsContainer, size_t entity, Utils::Vect2 &targetPosition)
{
    auto smoothingType = GameEngine::ComponentsType::getComponentType("SmoothingMovement");
    auto smoothing = componentsContainer.getComponent(entity, smoothingType);
    if (smoothing.has_value() && isVelocitySmoothing(componentsContainer, entity, targetPosition)) {
        return true;
    }
    return false;
}

bool Client::UpdatePosition::isVelocitySmoothing(GameEngine::ComponentsContainer &componentsContainer, size_t entity, Utils::Vect2 &targetPosition)
{
    auto velocityComponent = componentsContainer.getComponent(entity, GameEngine::ComponentsType::getComponentType("VelocityComponent"));
    auto positionComponent = componentsContainer.getComponent(entity, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
    if (!velocityComponent.has_value() || !positionComponent.has_value())
        return false;
    auto velComp = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(velocityComponent.value());
    auto posComp = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(positionComponent.value());
    Utils::Vect2 directionToB = targetPosition - posComp->pos;
    Utils::Vect2 normalizedDirection = directionToB.normalize();
    Utils::Vect2 normalizedVelocity = velComp->velocity.normalize();
    return normalizedDirection.x == normalizedVelocity.x && normalizedDirection.y == normalizedVelocity.y;
}

void Client::UpdatePosition::smoothPosition(GameEngine::ComponentsContainer &componentsContainer, size_t entity, Utils::Vect2 &targetPosition)
{
    auto velocityComponent = componentsContainer.getComponent(entity, GameEngine::ComponentsType::getComponentType("VelocityComponent"));
    auto positionComponent = componentsContainer.getComponent(entity, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
    if (!velocityComponent.has_value() || !positionComponent.has_value())
        return;
    auto velComp = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(velocityComponent.value());
    auto posComp = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(positionComponent.value());
    Utils::Vect2 directionToB = targetPosition - posComp->pos;
    Utils::Vect2 normalizedDirection = directionToB.normalize();
    int speed = 2;
    velComp->velocity = normalizedDirection * speed;
    std::cout << "Smooth Velocity" << " x: " << velComp->velocity.x << " y: " << velComp->velocity.y << std::endl;
}

bool Client::UpdatePosition::isEntityChangedPosition(GameEngine::ComponentsContainer &componentsContainer, size_t entity, Utils::Vect2 &targetPosition)
{
    auto positionComponent = componentsContainer.getComponent(entity, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
    if (!positionComponent.has_value())
        return false;
    auto position = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(positionComponent.value());
    float dist = position->pos.distanceTo(targetPosition);
        if (dist <= 10) {
            return false;
        }
    return true;
}

bool Client::UpdatePosition::isEntityPlayer(GameEngine::ComponentsContainer &componentsContainer, size_t entity)
{
    auto &factory = EntityFactory::getInstance();
    auto mapPlayer = factory.getPlayerMap();
    auto it = mapPlayer.find(entity);
    if (it == mapPlayer.end())
        return false;
    return true;
}