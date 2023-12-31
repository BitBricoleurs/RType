/*
** EPITECH PROJECT, 2023
** RType
** File description:
** NetworkReceiveFlash
*/

#include "NetworkReceiveFlash.hpp"

void Client::NetworkReceiveFlash::update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) {
    try {
        std::shared_ptr<Network::OwnedMessage> message;
        message = std::any_cast<std::shared_ptr<Network::OwnedMessage>>(eventHandler.getTriggeredEvent().second);
       
        std::shared_ptr<Network::IMessage> IMessage = message->message;
        std::shared_ptr<Network::Message> messageData = std::make_shared<Network::Message>(IMessage->getMessage());

        std::vector<size_t> ids = messageData->getIDs();
        EntityFactory &entityFactory = EntityFactory::getInstance();
        size_t clientId = 0;
        for (auto &id : ids) {
            clientId = entityFactory.getClientId(id);
        
            if (clientId == 0) {
                std::cout << "Error in NetworkReceiveFlash : mobIdClient == 0" << std::endl;
                return;
            }
           
            auto sprite = componentsContainer.getComponent(clientId, GameEngine::ComponentsType::getComponentType("SpriteComponent"));
            if (!sprite.has_value())
                return;
            auto spriteCast = std::static_pointer_cast<RenderEngine::SpriteComponent>(sprite.value());
            if (spriteCast->flash)
                return;
            spriteCast->flash = true;
            spriteCast->isVisible = !spriteCast->isVisible;
            eventHandler.scheduleEvent("flash", 3, clientId, 5);

        }
    } catch (std::exception &e) {
        std::cout << "Error in NetworkReceiveFlash : " << e.what() << std::endl;
    }
}