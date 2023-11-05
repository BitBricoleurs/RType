//
// Created by Clément Lagasse on 11/10/2023.
//

#include "CreateMob.hpp"

namespace Client {

    void CreateMob::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
    {
            try {
               std::shared_ptr<Network::OwnedMessage> message;

                try {
                    message = std::any_cast<std::shared_ptr<Network::OwnedMessage>>(eventHandler.getTriggeredEvent().second);
                } catch (std::bad_any_cast &e) {
                        std::cerr << "Error from NetworkServerAccept System " << e.what() << std::endl;
                        return ;
                }
                std::shared_ptr<Network::IMessage> IMessage = message->message;
                std::shared_ptr<Network::Message> messageData = std::make_shared<Network::Message>(IMessage->getMessage());

                std::vector<size_t> ids = messageData->getIDs();
                std::vector<std::any> args = messageData->getArgs();

                if (ids.size() != 1)
                    return;
                if (args.size() != (ids.size() * 5))
                    return;
                int arg_index = 0;
                MobType typeMob = static_cast<MobType>(std::any_cast<int>(args[0]));

                EntityFactory  &factory = EntityFactory::getInstance();

                size_t entityId = 0;
                int args_index = 1;
                for (auto id : ids ) {
                     Utils::Vect2 pos(static_cast<float>(std::any_cast<int>(args[arg_index + 1])) / 1000, static_cast<float>(std::any_cast<int>(args[arg_index + 2])) / 1000);
                     Utils::Vect2 velocity(static_cast<float>(std::any_cast<int>(args[arg_index + 3])) / 1000, static_cast<float>(std::any_cast<int>(args[arg_index + 4])) / 1000);

                    if (typeMob == MobType::CANCER) {
                        entityId = factory.spawnCancerMob(componentsContainer, eventHandler, pos, velocity);
                    } else if (typeMob == MobType::PATAPATA) {
                        entityId = factory.spawnPataPataMob(componentsContainer, eventHandler, pos, velocity);
                     } else if (typeMob == MobType::BELLMITECORE) {
                        entityId = factory.createBellmiteBoss(componentsContainer, eventHandler, pos);
                     } else if (typeMob == MobType::BELLMITEPOD) {
                        entityId = factory.createBellmitePod(componentsContainer, eventHandler, pos);
                    } else {
                        entityId = factory.spawnBugMob(componentsContainer, eventHandler, pos, velocity);
                    }
                    factory.registerEntity(entityId, id);
                    arg_index += 5;
                }
            } catch (std::bad_any_cast &e) {
                std::cerr << "Error from UpdatePosition System " << e.what() << std::endl;
            }
    }

}
