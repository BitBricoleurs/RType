//
// Created by alexandre on 22/10/23.
//

#include "CreateParallax.hpp"

void Client::CreateParallax::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    try {
        std::shared_ptr<Network::OwnedMessage> message;
        try {
            message = std::any_cast<std::shared_ptr<Network::OwnedMessage>>(eventHandler.getTriggeredEvent().second);
        } catch (std::bad_any_cast &e) {
            std::cerr << "Error from CreateParallax System " << e.what() << std::endl;
            return ;
        }
        std::shared_ptr<Network::IMessage> IMessage = message->message;
        std::shared_ptr<Network::Message> messageData = std::make_shared<Network::Message>(IMessage->getMessage());
        std::vector<size_t> ids = messageData->getIDs();
        std::vector<std::any> args = messageData->getArgs();
        if (ids.size() != 1)
            return;
        if (args.size() != 5)
            return;
        auto typeMob = static_cast<ParallaxType>(std::any_cast<int>(args[0]));
        auto posXFloat = static_cast<float>(std::any_cast<int>(args[1])) / 1000;
        auto posYFloat = static_cast<float>(std::any_cast<int>(args[2])) / 1000;
        auto speedFloat = static_cast<float>(std::any_cast<int>(args[3])) / 1000;
        Utils::Vect2 pos = {posXFloat, posYFloat};
        Utils::Vect2 velocity = {speedFloat, 0};
        auto layer = std::any_cast<int>(args[4]);
        EntityFactory  &factory = EntityFactory::getInstance();

        size_t entityId = 0;

        for (auto id : ids ) {
            entityId = factory.spawnParallax(componentsContainer, eventHandler, typeMob, pos, velocity, layer);
            factory.registerEntity(entityId, id);
        }
    } catch (std::bad_any_cast &e) {
        std::cerr << "Error from CreateParallax System " << e.what() << std::endl;
    }
}
