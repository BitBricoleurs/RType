//
// Created by Clément Lagasse on 23/10/2023.
//

#include "NetworkReceiveStartGame.hpp"

void Client::NetworkReceiveStartGame::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    auto compTypeGameState = GameEngine::ComponentsType::getComponentType("GameState");
    std::vector<size_t> gameStateEntities = componentsContainer.getEntitiesWithComponent(compTypeGameState);
    if (gameStateEntities.empty())
        return;
    auto compMay = componentsContainer.getComponent(gameStateEntities[0], compTypeGameState);
    if (!compMay.has_value())
        return;
    auto gameStateComp = std::static_pointer_cast<Utils::GameState>(compMay.value());
    gameStateComp->_state = Utils::GameState::State::RUNNING;
}