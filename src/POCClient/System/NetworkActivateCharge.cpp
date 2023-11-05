/*
** EPITECH PROJECT, 2023
** RType
** File description:
** ActivateCharge
*/

#include "NetworkActivateCharge.hpp"

void Client::ActivateCharge::update(GameEngine::ComponentsContainer &componentsContainer,
                  GameEngine::EventHandler &eventHandler) {

    try {
        std::shared_ptr<Network::OwnedMessage> message;
        message = std::any_cast<std::shared_ptr<Network::OwnedMessage>>(eventHandler.getTriggeredEvent().second);
       
        std::shared_ptr<Network::IMessage> IMessage = message->message;
        std::shared_ptr<Network::Message> messageData = std::make_shared<Network::Message>(IMessage->getMessage());

        std::vector<size_t> ids = messageData->getIDs();
        std::vector<std::any> args = messageData->getArgs();

        auto charge = std::any_cast<int>(args[0]);

        auto playerToUpdateServer = std::any_cast<int>(args[1]);
        
        size_t playerToUpdate = EntityFactory::getInstance().getClientId(playerToUpdateServer);
        
        auto isPlayerOpt = componentsContainer.getComponent(playerToUpdate, GameEngine::ComponentsType::getComponentType("IsPlayer"));
        if (isPlayerOpt.has_value())
            return;

        auto starshipOpt = componentsContainer.getComponent(playerToUpdate, GameEngine::ComponentsType::getComponentType("IsStarship"));
        if (starshipOpt.has_value()) {
            auto starship = std::static_pointer_cast<IsStarship>(starshipOpt.value());
            if (starship->entityIdChargeAnimation == 0)
                return;
            auto spriteOpt = componentsContainer.getComponent(starship->entityIdChargeAnimation, GameEngine::ComponentsType::getComponentType("SpriteComponent"));
            if (spriteOpt.has_value()) {
                auto sprite = std::static_pointer_cast<RenderEngine::SpriteComponent>(spriteOpt.value());
                if (charge == 1) {
                    sprite->isVisible = true;
                } else {
                    sprite->isVisible = false;
                }
            }
        }
    } catch (std::bad_any_cast &e) {
        std::cerr << "Error from ActivateCharge System " << e.what() << std::endl;
    }
}