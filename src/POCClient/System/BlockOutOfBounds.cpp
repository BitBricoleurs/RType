//
// Created by alexandre on 25/10/23.
//

#include "BlockOutOfBounds.hpp"

void Client::BlockOutOfBounds::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    const float screenWidth = 1920.0f;
    const float screenHeight = 1080.0f;

    auto isPlayerId = componentsContainer.getEntityWithUniqueComponent(GameEngine::ComponentsType::getComponentType("IsPlayer"));
    if (isPlayerId == 0)
        return;

    auto isPlayerType = GameEngine::ComponentsType::getComponentType("IsPlayer");
    auto spriteType = GameEngine::ComponentsType::getComponentType("SpriteComponent");
    auto velocityType = GameEngine::ComponentsType::getComponentType("VelocityComponent");
    auto positionType = GameEngine::ComponentsType::getComponentType("PositionComponent2D");

    auto isPlayerOpt = componentsContainer.getComponent(isPlayerId, isPlayerType);
    auto spriteOpt = componentsContainer.getComponent(isPlayerId, spriteType);
    auto velocityOpt = componentsContainer.getComponent(isPlayerId, velocityType);
    auto positionOpt = componentsContainer.getComponent(isPlayerId, positionType);

    if (!isPlayerOpt.has_value() || !spriteOpt.has_value() || !velocityOpt.has_value() || !positionOpt.has_value())
        return;

    auto isPlayerCOmp = std::static_pointer_cast<Client::IsPlayer>(isPlayerOpt.value());
    auto spriteComp = std::static_pointer_cast<RenderEngine::SpriteComponent>(spriteOpt.value());
    auto velocityComp = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(velocityOpt.value());
    auto posComp = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(positionOpt.value());

    float leftBound = 0;
    float rightBound = screenWidth;
    float upperBound = 0;
    float lowerBound = screenHeight;

    if (posComp->pos.x < leftBound || posComp->pos.x + spriteComp->rect1.w * spriteComp->scale > rightBound) {
        velocityComp->velocity.x = 0;
        if (isPlayerCOmp->entityIdForcePod != 0) {
            auto forcePodVelocity = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(componentsContainer.getComponent(isPlayerCOmp->entityIdForcePod, GameEngine::ComponentsType::getComponentType("VelocityComponent")).value());
            forcePodVelocity->velocity.x = 0;
        }
        if (posComp->pos.x < leftBound) posComp->pos.x = leftBound;
        if ( posComp->pos.x + spriteComp->rect1.w * spriteComp->scale > rightBound) posComp->pos.x = rightBound - spriteComp->rect1.w * spriteComp->scale;
        std::vector<size_t> ids = {};
        std::vector<std::any> args = {velocityComp->velocity.x, velocityComp->velocity.y, posComp->pos.x, posComp->pos.y};
        std::shared_ptr<Network::IMessage> message = std::make_shared<Network::Message>("BLOCK", ids, "FLOAT", args);
        eventHandler.queueEvent("SEND_NETWORK", message);

    }
    if (posComp->pos.y < upperBound || posComp->pos.y + spriteComp->rect1.h * spriteComp->scale > lowerBound) {
        velocityComp->velocity.y = 0;
        if (isPlayerCOmp->entityIdForcePod != 0) {
            auto forcePodVelocity = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(componentsContainer.getComponent(isPlayerCOmp->entityIdForcePod, GameEngine::ComponentsType::getComponentType("VelocityComponent")).value());
            forcePodVelocity->velocity.y = 0;
        }
        if (posComp->pos.y < upperBound) posComp->pos.y = upperBound;
        if (posComp->pos.y +  spriteComp->rect1.h * spriteComp->scale > lowerBound) posComp->pos.y = lowerBound -  spriteComp->rect1.h * spriteComp->scale;
        std::vector<size_t> ids = {};
        std::vector<std::any> args = {velocityComp->velocity.x, velocityComp->velocity.y, posComp->pos.x, posComp->pos.y};
        std::shared_ptr<Network::IMessage> message = std::make_shared<Network::Message>("BLOCK", ids, "FLOAT", args);
        eventHandler.queueEvent("SEND_NETWORK", message);
    }
}
