//
// Created by clagasse on 10/31/23.
//

#include "DeathPlayer.hpp"

void Client::DeathPlayer::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    try {
               std::shared_ptr<Network::OwnedMessage> message;

                try {
                    message = std::any_cast<std::shared_ptr<Network::OwnedMessage>>(eventHandler.getTriggeredEvent().second);
                } catch (std::bad_any_cast &e) {
                        std::cerr << "Error from DeathPlayer System " << e.what() << std::endl;
                        return ;
                }
                std::shared_ptr<Network::IMessage> IMessage = message->message;
                std::shared_ptr<Network::Message> messageData = std::make_shared<Network::Message>(IMessage->getMessage());

                std::vector<size_t> ids = messageData->getIDs();
                std::vector<std::any> args = messageData->getArgs();

                if (ids.size() == 0)
                    return;

                auto &factory = EntityFactory::getInstance();
                std::vector<size_t> clientEntities = {};
                auto mapPlayer = factory.getPlayerMap();
                for (auto &id : ids) {
                    size_t clientId = factory.getClientId(id);
                    if (mapPlayer.find(clientId) != mapPlayer.end()) {
                        clientEntities.push_back(clientId);
                    }
                }
                if (clientEntities.size() == 0)
                    return;
                auto spriteType = GameEngine::ComponentsType::getComponentType("SpriteComponent");
                auto userGameModeType = GameEngine::ComponentsType::getComponentType("UserGameMode");
                for (auto &id : clientEntities) {
                    auto spriteComponentOpt = componentsContainer.getComponent(id, spriteType);
                    auto userGameModeComponentOpt = componentsContainer.getComponent(id, userGameModeType);
                    if (spriteComponentOpt.has_value() ) {
                        auto spriteComponent = std::static_pointer_cast<RenderEngine::SpriteComponent>(spriteComponentOpt.value());
                        spriteComponent->isVisible = false;
                    }
                    if (userGameModeComponentOpt.has_value()) {
                        auto userGameModeComponent = std::static_pointer_cast<Utils::UserGameMode>(userGameModeComponentOpt.value());
                        userGameModeComponent->_state = Utils::UserGameMode::State::DEAD;
                        std::cout << "Player is dead" << std::endl;
                        GameEngine::Logger::info("Player: " + std::to_string(id) + " is dead");
                    }
                }
    } catch (std::bad_any_cast &e) {
        std::cerr << "Error from DeathPlayer System " << e.what() << std::endl;
    }
}