//
// Created by clagasse on 11/1/23.
//

#include "GoBackToTheLobbySystem.hpp"

void Server::GoBackToTheLobbySystem::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    auto compTypeGameState = GameEngine::ComponentsType::getComponentType("GameState");
    size_t gameStateEntity = componentsContainer.getEntityWithUniqueComponent(compTypeGameState);
    auto compMay = componentsContainer.getComponent(gameStateEntity, compTypeGameState);
    if (!compMay.has_value())
        return;
    auto gameStateComp = std::static_pointer_cast<Utils::GameState>(compMay.value());
    gameStateComp->_state = Utils::GameState::State::WAITING;
    std::vector<size_t> ids = {};
    std::vector<std::any> args = {static_cast<int>(Utils::GameState::State::WAITING)};
    std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("JOIN_LOBBY", ids, "INT", args);
    std::shared_ptr<Network::AllUsersMessage> allMessage = std::make_shared<Network::AllUsersMessage>(message);
    resetScoreNetwork(componentsContainer, eventHandler);
    eventHandler.queueEvent("SEND_NETWORK", allMessage);
}

void Server::GoBackToTheLobbySystem::resetScoreNetwork(GameEngine::ComponentsContainer &componentsContainer,
                                           GameEngine::EventHandler &eventHandler)
{
    auto scoreEntity = componentsContainer.getEntityWithUniqueComponent(GameEngine::ComponentsType::getComponentType("Score"));
    auto scoreComponentOpt = componentsContainer.getComponent(scoreEntity, GameEngine::ComponentsType::getComponentType("Score"));
    if (scoreComponentOpt.has_value()) {
        auto scoreComponent = std::static_pointer_cast<Score>(scoreComponentOpt.value());
        scoreComponent->score = 0;
        updateScoreNetwork(eventHandler, scoreComponent->score);
    }
}

void Server::GoBackToTheLobbySystem::updateScoreNetwork(GameEngine::EventHandler &eventHandler, size_t score)
{
    std::vector<size_t> ids = {};
    int scoreInt = score;
    std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("UPDATE_SCORE", ids, "INT", std::vector<std::any>{scoreInt});
    std::shared_ptr<Network::AllUsersMessage> allMessage = std::make_shared<Network::AllUsersMessage>(message);
    eventHandler.queueEvent("SEND_NETWORK", allMessage);
}