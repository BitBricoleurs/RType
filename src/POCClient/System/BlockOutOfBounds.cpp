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
    std::cout << "isPlayerId: " << isPlayerId << std::endl;
    auto spriteComp = std::dynamic_pointer_cast<RenderEngine::SpriteComponent>(componentsContainer.getComponent(isPlayerId, GameEngine::ComponentsType::getComponentType("SpriteComponent")).value());
    std::cout << "Pass" << std::endl;
    auto velocityComp = std::dynamic_pointer_cast<PhysicsEngine::VelocityComponent>(componentsContainer.getComponent(isPlayerId, GameEngine::ComponentsType::getComponentType("VelocityComponent")).value());
    std::cout << "Pass" << std::endl;
    auto posComp = std::dynamic_pointer_cast<PhysicsEngine::PositionComponent2D>(componentsContainer.getComponent(isPlayerId, GameEngine::ComponentsType::getComponentType("PositionComponent2D")).value());
    std::cout << "Pass" << std::endl;

    float leftBound = 0;
    float rightBound = screenWidth - spriteComp->rect1.w * spriteComp->scale;
    float upperBound = 0;
    float lowerBound = screenHeight - spriteComp->rect1.h * spriteComp->scale;

    if (posComp->pos.x < leftBound || posComp->pos.x > rightBound ||
        posComp->pos.y < upperBound || posComp->pos.y > lowerBound) {

        velocityComp->velocity.x = 0;
        velocityComp->velocity.y = 0;

        // Ajustement pour garder le sprite à l'intérieur des limites
        if (posComp->pos.x < leftBound) posComp->pos.x = leftBound;
        if (posComp->pos.x > rightBound) posComp->pos.x = rightBound;
        if (posComp->pos.y < upperBound) posComp->pos.y = upperBound;
        if (posComp->pos.y > lowerBound) posComp->pos.y = lowerBound;
    }
}
