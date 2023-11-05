//
// Created by alexandre on 30/10/23.
//

#include "ForcePodUpgrade.hpp"
#include "EntityFactory.hpp"


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
        auto &factory = EntityFactory::getInstance();
        size_t clientId = factory.getClientId(id);

        auto isPlayerType = GameEngine::ComponentsType::getComponentType("IsPlayer");

        auto playerOpt = componentsContainer.getComponent(clientId, isPlayerType);
        if (!playerOpt.has_value())
            return;

        auto player = std::static_pointer_cast<IsPlayer>(playerOpt.value());
        if (powerUp == 1) {
            return;
            try {
                std::cout << "ForcePodUpgrade" << std::endl;
                LoadConfig::ConfigData data = LoadConfig::LoadConfig::getInstance().loadConfig("config/Entity/createForcePod.json");
                componentsContainer.unbindComponentFromEntity(player->entityIdForcePod, GameEngine::ComponentsType::getComponentType("SpriteComponent"));
                auto spriteAnimationComponent = EntityFactory::getInstance().initAnimation(
              data.getString("/involve/0/path"), data.getInt("/involve/0/frames"), data.getInt("/involve/0/rect/width"), data.getInt("/involve/0/rect/height"),
              data.getBool("/involve/0/twoDirections"), data.getBool("/involve/0/reverse"), 2, 0);
                Utils::rect spriteRect;

              spriteRect.w = spriteAnimationComponent->frameWidth;
              spriteRect.h = spriteAnimationComponent->frameHeight;
              spriteRect.x = spriteAnimationComponent->currentFrame.x;
              spriteRect.y = spriteAnimationComponent->currentFrame.y;

            auto posType = GameEngine::ComponentsType::getComponentType("PositionComponent2D");
            auto posOpt = componentsContainer.getComponent(player->entityIdForcePod, posType);
            if (!posOpt.has_value())
                return;
            auto posComponent = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(posOpt.value());
            auto spriteComponent = std::make_shared<RenderEngine::SpriteComponent>(data.getString("/involve/0/path"), posComponent->pos, spriteRect, static_cast<size_t>(data.getInt("/involve/0/layer")), data.getFloat("/involve/0/scale"), data.getFloat("/involve/0/rotation"), Utils::ColorR(data.getInt("/involve/0/tint/r"), data.getInt("/involve/0/tint/g") ,data.getInt("/involve/0/tint/b"), data.getInt("/involve/0/tint/a")));
            componentsContainer.bindComponentToEntity(player->entityIdForcePod, spriteComponent);
        } catch (std::exception &e) {
            std::cout << "Error in ForcePodUpgrade : " << e.what() << std::endl;
            }
        } else if (powerUp == 2) {
            // other
        }
    } catch (const std::bad_any_cast &e) {
        std::cout << "Error in ForcePodUpgrade : " << e.what() << std::endl;
    }
}
