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
        size_t mobId = ids[0];

        auto sprite = componentsContainer.getComponent(mobId, GameEngine::ComponentsType::getComponentType("SpriteComponent"));
        if (!sprite.has_value())
            return;
        auto spriteCast = std::dynamic_pointer_cast<RenderEngine::SpriteComponent>(sprite.value());
        spriteCast->flash = false;
        
        eventHandler.scheduleEvent("flash", 3, mobId, 5);
    } catch (std::exception &e) {
        std::cout << "Error in NetworkReceiveFlash : " << e.what() << std::endl;
    }
}