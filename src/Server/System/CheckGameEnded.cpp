//
// Created by clagasse on 11/1/23.
//

#include "CheckGameEnded.hpp"

void Server::CheckGameEnded::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    auto compTypeGameState = GameEngine::ComponentsType::getComponentType("GameState");
    size_t gameStateEntity = componentsContainer.getEntityWithUniqueComponent(compTypeGameState);
    auto compMay = componentsContainer.getComponent(gameStateEntity, compTypeGameState);
    if (!compMay.has_value())
        return;
    auto gameStateComp = std::static_pointer_cast<Utils::GameState>(compMay.value());
    if (gameStateComp->_state != Utils::GameState::State::RUNNING)
        return;
    auto playerComp = GameEngine::ComponentsType::getComponentType("IsPlayer");
    auto gameMode = GameEngine::ComponentsType::getComponentType("UserGameMode");
    auto entities = componentsContainer.getEntitiesWithComponent(playerComp);

    if (entities.size() == 0)
        return;
    int countDead = 0;
   for (auto &entity : entities) {
        auto gameModeOpt = componentsContainer.getComponent(entity, gameMode);
        if (gameModeOpt.has_value()) {
            auto gameModeComp = std::static_pointer_cast<Utils::UserGameMode>(gameModeOpt.value());
            if (gameModeComp->_state == Utils::UserGameMode::State::DEAD || gameModeComp->_state == Utils::UserGameMode::State::SPECTATOR) {
                countDead++;
            }
        }
    }
    if (countDead == entities.size()) {
        eventHandler.queueEvent("LOSE_LEVEL");
    }
}