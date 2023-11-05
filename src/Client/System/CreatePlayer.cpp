//
// Created by Clément Lagasse on 11/10/2023.
//

#include "CreatePlayer.hpp"
#include "UserGameMode.hpp"

namespace Client {

    void CreatePlayer::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
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

                if (args.size() != (ids.size() * 6))
                    return;
                PlayerNumber number = static_cast<PlayerNumber>(std::any_cast<int>(args[0]));
                Utils::UserGameMode::State game = static_cast<Utils::UserGameMode::State>(std::any_cast<int>(args[1]));
                EntityFactory  &factory = EntityFactory::getInstance();
                Utils::Vect2 pos = Utils::Vect2(static_cast<float>(std::any_cast<int>(args[2])) / 1000, static_cast<float>(std::any_cast<int>(args[3])) / 1000);
                Utils ::Vect2 velocity = Utils::Vect2(static_cast<float>(std::any_cast<int>(args[4])) / 1000, static_cast<float>(std::any_cast<int>(args[5])) / 1000);
                size_t entityId = factory.createNewStarship(componentsContainer, eventHandler, pos, velocity, number);
                auto gameMode = std::make_shared<Utils::UserGameMode>(game);
                componentsContainer.bindComponentToEntity(entityId, gameMode);
                if (game != Utils::UserGameMode::State::ALIVE) {
                    auto spriteType = GameEngine::ComponentsType::getComponentType("SpriteComponent");
                    auto spriteComponentOpt = componentsContainer.getComponent(entityId, spriteType);
                    if (spriteComponentOpt.has_value()) {
                        auto spriteComponent = std::static_pointer_cast<RenderEngine::SpriteComponent>(spriteComponentOpt.value());
                        spriteComponent->isVisible = false;
                    }
                }
                factory.registerEntity(entityId, ids.front());
                GameEngine::Logger::info("Created Player with id " + std::to_string(entityId) + " and number " + std::to_string(number));
            } catch (std::bad_any_cast &e) {
                std::cerr << "Error from UpdatePosition System " << e.what() << std::endl;
            }
    }

}