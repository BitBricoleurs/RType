//
// Created by Clément Lagasse on 11/10/2023.
//

#include "CreateBullet.hpp"

void CreateBullet::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    try {
            std::shared_ptr<Network::OwnedMessage> message;

            message = std::any_cast<std::shared_ptr<Network::OwnedMessage>>(eventHandler.getTriggeredEvent().second);
            std::shared_ptr<Network::IMessage> IMessage = message->message;
            std::shared_ptr<Network::Message> messageData = std::make_shared<Network::Message>(IMessage->getMessage());

            std::vector<size_t> ids = messageData->getIDs();
            std::vector<std::any> args = messageData->getArgs();

        if (ids.size() >= 1 && args.size() != (ids.size() * 2))
            return;

    int arg_index = 0;
    for (auto &id : ids) {
        BulletOwner number = static_cast<BulletOwner>(std::any_cast<int>(args[arg_index]));
        BulletType typeBull = static_cast<BulletType>(std::any_cast<int>(args[arg_index + 1]));
        EntityFactory  &factory = EntityFactory::getInstance();
        Utils::Vect2 pos = {0, 0};
        size_t entityId = 0;
        std::string path = "";
        Utils::Vect2 velocity = {0, 0};
        if (number == BulletOwner::PLAYER)
            entityId = factory.createPlayerBullet(componentsContainer, eventHandler, pos, velocity, typeBull);
        else
            printf("CreateBulletSystem: BulletOwner not implemented\n");
        factory.registerEntity(entityId, id);
        eventHandler.queueEvent("PLAY_SOUND", entityId);
        arg_index += 2;
        }
    } catch (std::bad_any_cast &e) {
        std::cerr << "Error from CreateBulletSystem " << e.what() << std::endl;
    }
}
