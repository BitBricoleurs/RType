//
// Created by Clément Lagasse on 11/10/2023.
//

#include "CreateBullet.hpp"
#include "Logger.hpp"

namespace Client {

    void CreateBullet::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
    {
        try {
            std::shared_ptr<Network::OwnedMessage> message;

            message = std::any_cast<std::shared_ptr<Network::OwnedMessage>>(eventHandler.getTriggeredEvent().second);
            std::shared_ptr<Network::IMessage> IMessage = message->message;
            std::shared_ptr<Network::Message> messageData = std::make_shared<Network::Message>(IMessage->getMessage());

            std::vector<size_t> ids = messageData->getIDs();
            std::vector<std::any> args = messageData->getArgs();

            if (ids.size() > 1 && args.size() != (ids.size() * 6))
                return;

            int arg_index = 0;
            for (auto &id : ids) {
                BulletOwner number = static_cast<BulletOwner>(std::any_cast<int>(args[arg_index]));
                BulletType typeBull = static_cast<BulletType>(std::any_cast<int>(args[arg_index + 1]));

                EntityFactory  &factory = EntityFactory::getInstance();
                Utils::Vect2 pos(static_cast<float>(std::any_cast<int>(args[arg_index + 2])) / 1000, static_cast<float>(std::any_cast<int>(args[arg_index + 3])) / 1000);
                Utils::Vect2 velocity(static_cast<float>(std::any_cast<int>(args[arg_index + 4])) / 1000, static_cast<float>(std::any_cast<int>(args[arg_index + 5])) / 1000);
                size_t entityId = 0;
                std::string path = "";
                if (number == BulletOwner::PLAYER) {
                    entityId = factory.createPlayerBullet(componentsContainer, eventHandler, pos, velocity, typeBull);
                } else {
                    entityId = factory.createBaseEnemyBullet(componentsContainer, eventHandler, pos, velocity);
                }
                factory.registerEntity(entityId, id);
                eventHandler.queueEvent("PLAY_SOUND", entityId);
                arg_index += 6;
                GameEngine::Logger::info("Created bullet with id " + std::to_string(entityId) + " and owner " + std::to_string(number) + " and type " + std::to_string(typeBull));
            }
        } catch (std::bad_any_cast &e) {
            std::cerr << "Error from CreateBulletSystem " << e.what() << std::endl;
        }
    }

}