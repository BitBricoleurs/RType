//
// Created by Theophilus Homawoo on 11/10/2023.
//

#include "UpdateVelocity.hpp"

namespace Client {

    void UpdateVelocity::update(GameEngine::ComponentsContainer &componentsContainer,
                        GameEngine::EventHandler &eventHandler) {
        try {
           std::shared_ptr<Network::OwnedMessage> message;

            try {
                message = std::any_cast<std::shared_ptr<Network::OwnedMessage>>(eventHandler.getTriggeredEvent().second);
            } catch (std::bad_any_cast &e) {
                    std::cerr << "Error from UpdateVelocity System " << e.what() << std::endl;
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
                if (isEntitySelf(componentsContainer, entityToUpdate)) {
                    return;
                }
                auto velocityComponent = componentsContainer.getComponent(entityToUpdate, GameEngine::ComponentsType::getComponentType("VelocityComponent"));
                if (!velocityComponent.has_value())
                    return;
                Utils::Vect2 newVelocity(std::any_cast<float>(args[0]), std::any_cast<float>(args[1]));
                if (isEntitySmoothing(componentsContainer, entityToUpdate) && (newVelocity.x != 0 && newVelocity.y != 0)) {
                    stopSmoothing(componentsContainer, entityToUpdate);
                }

                auto velocity = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(velocityComponent.value());
                velocity->velocity = newVelocity;

                auto bug = componentsContainer.getComponent(entityToUpdate, GameEngine::ComponentsType::getComponentType("Bug"));
                if (bug.has_value())
                    eventHandler.queueEvent("UpdateBugSprite", entityToUpdate);
            }

        } catch (std::bad_any_cast &e) {
            std::cerr << "Error from UpdateVelocity System " << e.what() << std::endl;
        }
    }

} // namespace Client

bool Client::UpdateVelocity::isEntitySelf(GameEngine::ComponentsContainer &componentsContainer, size_t entityToCheck)
{
    auto isPLayerType = GameEngine::ComponentsType::getComponentType("IsPlayer");

    auto entities = componentsContainer.getEntitiesWithComponent(isPLayerType);
    for (auto entity: entities) {
        if (entityToCheck == entity) {
            return true;
        }
    }
    return false;
}

bool Client::UpdateVelocity::isEntitySmoothing(GameEngine::ComponentsContainer &componentsContainer, size_t entity)
{
    auto smoothingType = GameEngine::ComponentsType::getComponentType("SmoothingMovement");
    auto smoothing = componentsContainer.getComponent(entity, smoothingType);
    if (smoothing.has_value()) {
        return true;
    }
    return false;
}

void Client::UpdateVelocity::stopSmoothing(GameEngine::ComponentsContainer &componentsContainer, size_t entity)
{
    auto smoothingType = GameEngine::ComponentsType::getComponentType("SmoothingMovement");
    auto smoothing = componentsContainer.getComponent(entity, smoothingType);
    if (smoothing.has_value()) {
        componentsContainer.unbindComponentFromEntity(entity, smoothingType);
    }
}