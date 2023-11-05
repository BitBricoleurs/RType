//
// Created by alexandre on 30/10/23.
//

#include "CreatePowerUpDual.hpp"

void Client::CreatePowerUpDual::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
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

                if (ids.size() != 2 && (args.size() != 5))
                    return;

                auto typePowerUp = static_cast<PowerUpType>(std::any_cast<int>(args[0]));
                Utils::Vect2 pos(static_cast<float>(std::any_cast<int>(args[1])) / 1000, static_cast<float>(std::any_cast<int>(args[2])) / 1000);
                Utils::Vect2 pos2(static_cast<float>(std::any_cast<int>(args[3])) / 1000, static_cast<float>(std::any_cast<int>(args[4])) / 1000);
                EntityFactory  &factory = EntityFactory::getInstance();
                try {
                    LoadConfig::ConfigData data = LoadConfig::LoadConfig::getInstance().loadConfig("config/Game/powerUp.json");

                        auto entityIdVect = Client::EntityFactory::getInstance().spawnPowerUpDualShoot(componentsContainer, eventHandler, typePowerUp, pos, pos2);
                        int count = 0;
                        for (auto id : ids ) {
                            factory.registerEntity(entityIdVect[count], id);
                            count++;
                        }
                } catch (std::exception &e) {
                    std::cerr << "Error from createPowerUp System " << e.what() << std::endl;
                }

            } catch (std::bad_any_cast &e) {
                std::cerr << "Error from createPowerUp System " << e.what() << std::endl;
            }

}