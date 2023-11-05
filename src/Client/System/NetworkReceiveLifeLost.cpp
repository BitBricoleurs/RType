/*
** EPITECH PROJECT, 2023
** RType
** File description:
** NetworkReceiveLifeLost
*/

#include "NetworkReceiveLifeLost.hpp"


void Client::NetworkReceiveLifeLost::update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) {
    try {
        std::shared_ptr<Network::OwnedMessage> message;
        message = std::any_cast<std::shared_ptr<Network::OwnedMessage>>(eventHandler.getTriggeredEvent().second);
       
        std::shared_ptr<Network::IMessage> IMessage = message->message;
        std::shared_ptr<Network::Message> messageData = std::make_shared<Network::Message>(IMessage->getMessage());

        std::vector<size_t> ids = messageData->getIDs();
        std::vector<std::any> args = messageData->getArgs();

        auto lives = std::any_cast<int>(args[0]);

        EntityFactory &entityFactory = EntityFactory::getInstance();
        size_t clientId = 0;
        for (auto &id : ids) {
            clientId = entityFactory.getClientId(id);
            auto isPlayerOpt = componentsContainer.getComponent(clientId, GameEngine::ComponentsType::getComponentType("IsPlayer"));
            auto HealthBarId = componentsContainer.getEntityWithUniqueComponent(GameEngine::ComponentsType::getComponentType("IsHealthBar"));
            if (HealthBarId != 0 && isPlayerOpt.has_value()) {
                auto HealthBarComponentOpt = (componentsContainer.getComponent(HealthBarId, GameEngine::ComponentsType::getComponentType("SpriteComponent")));
                if (HealthBarComponentOpt.has_value()) {
                    auto HealthBarComponent = std::static_pointer_cast<RenderEngine::SpriteComponent>(HealthBarComponentOpt.value());
                    HealthBarComponent->rect1.w = lives * 9;
                    if (lives == 3) {
                        HealthBarComponent->rect1.w = 27;
                    }
                }
            }
        }
    } catch (std::exception &e) {
        std::cout << "Error in NetworkReceiveLifeLost : " << e.what() << std::endl;
    }
}