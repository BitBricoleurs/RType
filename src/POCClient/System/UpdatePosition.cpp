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
                float distance = position->pos.magnitude(targetPosition);
                if (isEntityMotionless(componentsContainer, entityToUpdate)) {
                    trySmoothingPosition(componentsContainer, entityToUpdate, targetPosition);
                    return;
                } else if (isEntitySmoothing(componentsContainer, entityToUpdate)) {
                    return;
                } else {
                    tryRemovingSmoothing(componentsContainer, entityToUpdate);
                }
                if (distance > 50) {
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
}

void Client::UpdatePosition::tryRemovingSmoothing(GameEngine::ComponentsContainer &componentsContainer, size_t entity)
{
    auto smoothingType = GameEngine::ComponentsType::getComponentType("SmoothingMovement");
    if (isEntitySmoothing(componentsContainer, entity)) {
        componentsContainer.unbindComponentFromEntity(entity, smoothingType);
    }
}

bool Client::UpdatePosition::isEntitySmoothing(GameEngine::ComponentsContainer &componentsContainer, size_t entity)
{
    auto smoothingType = GameEngine::ComponentsType::getComponentType("SmoothingMovement");
    auto smoothing = componentsContainer.getComponent(entity, smoothingType);
    if (smoothing.has_value()) {
        return true;
    }
    return false;
}