//
// Created by clagasse on 11/1/23.
//

#include "RevivePlayer.hpp"

void Client::RevivePlayer::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
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

                if (ids.size() <= 0)
                    return;

                size_t clientId = 0;
                auto &factory = EntityFactory::getInstance();
                auto spriteType = GameEngine::ComponentsType::getComponentType("SpriteComponent");
                auto userGameModeType = GameEngine::ComponentsType::getComponentType("UserGameMode");
                for (auto &id : ids) {
                    clientId = factory.getClientId(id);
                    auto spriteComponentOpt = componentsContainer.getComponent(clientId, spriteType);
                    if (spriteComponentOpt.has_value() ) {
                        auto spriteComponent = std::static_pointer_cast<RenderEngine::SpriteComponent>(spriteComponentOpt.value());
                        spriteComponent->isVisible = true;
                    }
                    auto userGameModeComponentOpt = componentsContainer.getComponent(clientId, userGameModeType);
                    if (userGameModeComponentOpt.has_value()) {
                        auto userGameModeComponent = std::static_pointer_cast<Utils::UserGameMode>(userGameModeComponentOpt.value());
                        userGameModeComponent->_state = Utils::UserGameMode::State::ALIVE;
                    }
                }
    } catch (std::bad_any_cast &e) {
        std::cerr << "Error from DeathPlayer System " << e.what() << std::endl;
    }
}