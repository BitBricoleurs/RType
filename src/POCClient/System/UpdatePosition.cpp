//
// Created by Theophilus Homawoo on 11/10/2023.
//

#include "UpdatePosition.hpp"

namespace Client {

    void UpdatePosition::update(GameEngine::ComponentsContainer &componentsContainer,
                        GameEngine::EventHandler &eventHandler) {
        try {
           std::shared_ptr<Network::OwnedMessage> message;

            try {
                message = std::any_cast<std::shared_ptr<Network::OwnedMessage>>(eventHandler.getTriggeredEvent().second);
            } catch (std::bad_any_cast &e) {
                    std::cerr << "Error from UpdatePosition System " << e.what() << std::endl;
                    return ;
            }
            std::shared_ptr<Network::IMessage> IMessage = message->message;
            std::shared_ptr<Network::Message> messageData = std::make_shared<Network::Message>(IMessage->getMessage());

            std::vector<size_t> ids = messageData->getIDs();
            std::vector<std::any> args = messageData->getArgs();


            if (ids.size() != 1 || args.size() != 2)
                return;
            EntityFactory &factory = EntityFactory::getInstance();
            for (auto &id : ids) {

                size_t entityToUpdate = factory.getClientId(id);
                auto positionComponent = componentsContainer.getComponent(entityToUpdate, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
                if (!positionComponent.has_value())
                    return;
                float x = std::any_cast<float>(args[0]);
                float y = std::any_cast<float>(args[1]);

                auto position = std::static_pointer_cast<GameEngine::PositionComponent2D>(positionComponent.value());
                position->pos = {x, y};
            }
        } catch (std::bad_any_cast &e) {
            std::cerr << "Error from UpdatePosition System " << e.what() << std::endl;
        }
    }

} // namespace Client