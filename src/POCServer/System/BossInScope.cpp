/*
** EPITECH PROJECT, 2023
** RType
** File description:
** BossInScope
*/

#include "BossInScope.hpp"

void Server::BossInScope::update(GameEngine::ComponentsContainer &componentsContainer,
              GameEngine::EventHandler &eventHandler) {
    auto bossCore = componentsContainer.getEntityWithUniqueComponent(
        GameEngine::ComponentsType::getComponentType("isBossCore"));

    // check if boss exists and is in scope
    if (bossCore == 0 || hasAppeared)
        return;
    
    auto pos = componentsContainer.getComponent(bossCore, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));

    if (pos == nullptr)
        return;
    auto posComp = std::dynamic_pointer_cast<PhysicsEngine::PositionComponent2D>(pos.value());
    if (posComp->pos.x < 150 || posComp->pos.y < 150 ||
        posComp->pos.y > 1080 - 150 || posComp->pos.x > 1920 - 150) {
        return;
    }
    if (!hasAppeared) {
        eventHandler.scheduleEvent("launchBossPods", 200);
        eventHandler.scheduleEvent("bounceBoss", 3);
        hasAppeared = true;
    }
}
