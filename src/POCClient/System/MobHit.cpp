//
// Created by Bartosz on 10/9/23.
//

#include "MobHit.hpp"

void MobHit::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
    try {
        auto [firstEntity, secondEntity] = std::any_cast<std::pair<size_t, size_t>>(eventHandler.getTriggeredEvent().second);
            auto isbullet = componentsContainer.getComponent(secondEntity, GameEngine::ComponentsType::getComponentType("IsBullet"));
            auto spriteCompType = GameEngine::ComponentsType::getComponentType("SpriteComponent");

            if (isbullet.has_value()) {
                auto isbulletcast = std::static_pointer_cast<IsBullet>(isbullet.value());
                if (isbulletcast->passingThrough == false) {
                    auto spriteComponentMay = componentsContainer.getComponent(secondEntity, spriteCompType);
                    if (spriteComponentMay.has_value()) {
                        auto spriteComponent = std::static_pointer_cast<GameEngine::SpriteComponent>(spriteComponentMay.value());
                        spriteComponent->isVisible = false;
                    }
                }

            }
            isbullet = componentsContainer.getComponent(firstEntity, GameEngine::ComponentsType::getComponentType("IsBullet"));
            if (isbullet.has_value()) {
                auto isbulletcast = std::static_pointer_cast<IsBullet>(*isbullet);
                if (isbulletcast->passingThrough == false) {
                    auto spriteComponentMay = componentsContainer.getComponent(firstEntity, spriteCompType);
                    if (spriteComponentMay.has_value()) {
                        auto spriteComponent = std::static_pointer_cast<GameEngine::SpriteComponent>(spriteComponentMay.value());
                        spriteComponent->isVisible = false;
                    }
                }
            }
    } catch (std::exception &e) {

    }
}

void MobHit::killMobNetwork(GameEngine::EventHandler &eventHandler, std::vector<size_t> &entitiesToKill)
{
     std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("DELETED_ENTITY", entitiesToKill, "", std::vector<std::any>{});
     std::shared_ptr<Network::AllUsersMessage> allMessage = std::make_shared<Network::AllUsersMessage>(message);
     eventHandler.queueEvent("SEND_NETWORK", allMessage);
}