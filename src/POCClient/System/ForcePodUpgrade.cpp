//
// Created by alexandre on 30/10/23.
//

#include "ForcePodUpgrade.hpp"

void Client::ForcePodUpgrade::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    try {
        std::shared_ptr<Network::OwnedMessage> message;
        message = std::any_cast<std::shared_ptr<Network::OwnedMessage>>(eventHandler.getTriggeredEvent().second);

        std::shared_ptr<Network::IMessage> IMessage = message->message;
        std::shared_ptr<Network::Message> messageData = std::make_shared<Network::Message>(IMessage->getMessage());

        std::vector<size_t> ids = messageData->getIDs();
        std::vector<std::any> args = messageData->getArgs();

        if (ids.size() != 0 || args.size() != 2)
            return;
        auto id = std::any_cast<int>(args[0]);
        auto powerUp = std::any_cast<int>(args[1]);
        auto player = std::dynamic_pointer_cast<IsPlayer>(componentsContainer.getComponent(id, GameEngine::ComponentsType::getComponentType("IsPlayer")).value());
        auto forcePod = std::dynamic_pointer_cast<RenderEngine::SpriteComponent>(componentsContainer.getComponent(player->entityIdForcePod, GameEngine::ComponentsType::getComponentType("SpriteComponent")).value());
        if (powerUp == 1) {
            forcePod->imagePath = "assets/forcePod2.png";
            forcePod->rect1 = {0, 0, 360, 21};
        } else if (powerUp == 2) {
            forcePod->imagePath = "assets/forcePod3.png";
            forcePod->rect1 = {0, 0, 360, 21};
        }
    } catch (std::exception &e) {
        std::cout << "Error in NetworkReceiveFlash : " << e.what() << std::endl;
    }
}
