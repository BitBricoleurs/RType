//
// Created by Theophilus Homawoo on 11/10/2023.
//

#include "ChangeDirPlayer.hpp"
#include "VelocityComponent.hpp"
#include "IsPlayer.hpp"
#include "Message.hpp"
#include "EntityFactory.hpp"

Client::ChangeDirPlayer::ChangeDirPlayer()
{
    speed = 7;
    directionMap["UP_KEY_PRESSED"] = std::make_pair(0, -speed);
    directionMap["DOWN_KEY_PRESSED"] = std::make_pair(0, speed);
    directionMap["LEFT_KEY_PRESSED"] = std::make_pair(-speed, 0);
    directionMap["RIGHT_KEY_PRESSED"] = std::make_pair(speed, 0);

    directionMap["UP_KEY_RELEASED"] = std::make_pair(0, speed);
    directionMap["DOWN_KEY_RELEASED"] = std::make_pair(0, -speed);
    directionMap["LEFT_KEY_RELEASED"] = std::make_pair(speed, 0);
    directionMap["RIGHT_KEY_RELEASED"] = std::make_pair(-speed, 0);

}

void Client::ChangeDirPlayer::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
    size_t id = componentsContainer.getEntityWithUniqueComponent(GameEngine::ComponentsType::getNewComponentType("IsPlayer"));
    if (id == 0)
        return;
    auto event = eventHandler.getTriggeredEvent();
    auto velocityOptional = componentsContainer.getComponent(id, GameEngine::ComponentsType::getComponentType("VelocityComponent"));
    auto isPlayerOptional = componentsContainer.getComponent(id, GameEngine::ComponentsType::getComponentType("IsPlayer"));

    if (velocityOptional.has_value() && isPlayerOptional.has_value()) {
        auto velocity = std::dynamic_pointer_cast<PhysicsEngine::VelocityComponent>(velocityOptional.value());
        auto isPlayer = std::dynamic_pointer_cast<IsPlayer>(isPlayerOptional.value());

        velocity->velocity.x += directionMap[event.first].first;
        velocity->velocity.y += directionMap[event.first].second;

        if (isPlayer->entityIdForcePod != 0) {
            auto velocityForcePodOpt = componentsContainer.getComponent(isPlayer->entityIdForcePod, GameEngine::ComponentsType::getComponentType("VelocityComponent"));
            if (velocityForcePodOpt.has_value()) {
                auto velocityForcePod = std::dynamic_pointer_cast<PhysicsEngine::VelocityComponent>(velocityForcePodOpt.value());
                velocityForcePod->velocity.x = velocity->velocity.x;
                velocityForcePod->velocity.y = velocity->velocity.y;
            }
        }
        std::vector<size_t> ids = {};
        std::vector<std::any> args = {velocity->velocity.x, velocity->velocity.y};
        std::shared_ptr<Network::IMessage> message = std::make_shared<Network::Message>("MOVE", ids, "FLOAT", args);
        eventHandler.queueEvent("SEND_NETWORK", message);
    }
}
