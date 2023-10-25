//
// Created by Clément Lagasse on 11/10/2023.
//

#include "CreateMob.hpp"

namespace Client {

    void CreateMob::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
    {
            try {
              std::cout << "Create Mob" << std::endl;
              std::shared_ptr<Network::OwnedMessage> message;

              try {
                message = std::any_cast<std::shared_ptr<Network::OwnedMessage>>(
                    eventHandler.getTriggeredEvent().second);
              } catch (std::bad_any_cast &e) {
                std::cerr << "Error from NetworkServerAccept System "
                          << e.what() << std::endl;
                return;
              }
                std::shared_ptr<Network::IMessage> IMessage = message->message;
                std::shared_ptr<Network::Message> messageData = std::make_shared<Network::Message>(IMessage->getMessage());

                std::vector<size_t> ids = messageData->getIDs();
                std::vector<std::any> args = messageData->getArgs();

                if (ids.size() != 1)
                    return;
                if (args.size() != 1)
                    return;
                MobType typeMob = static_cast<MobType>(std::any_cast<int>(args[0]));
                EntityFactory  &factory = EntityFactory::getInstance();
                Utils::Vect2 pos = {0, 0};

                size_t entityId = 0;
                for (auto id : ids ) {
                    if (typeMob == MobType::CANCER) {
                      std::cout << "creating Cancer" << std::endl;
                      entityId = factory.spawnCancerMob(componentsContainer,
                                                        eventHandler, pos, 0);
                    } else if (typeMob == MobType::PATAPATA) {
                      std::cout << "creating PATA" << std::endl;
                      entityId = factory.spawnPataPataMob(componentsContainer,
                                                          eventHandler, pos, 0);
                    } else if (typeMob == MobType::BELLMITECORE) {
                      std::cout << "creating Bellmite" << std::endl;
                      entityId = factory.createBellmiteBoss(componentsContainer,
                                                            eventHandler, pos);
                    } else if (typeMob == MobType::BELLMITEPOD) {
                      std::cout << "creating Bellmite Pod" << std::endl;
                      entityId = factory.createBellmitePod(componentsContainer,
                                                           eventHandler, pos);
                    } else {
                      std::cout << "creating Bug" << std::endl;
                      entityId = factory.spawnBugMob(componentsContainer,
                                                     eventHandler, pos, 0);
                    }
                    factory.registerEntity(entityId, id);
                }
            } catch (std::bad_any_cast &e) {
                std::cerr << "Error from UpdatePosition System " << e.what() << std::endl;
            }
    }

}
