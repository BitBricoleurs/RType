//
// Created by Clément Lagasse on 23/10/2023.
//

#include "CheckEveryClientReady.hpp"

void Server::CheckEveryClientReady::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    auto compTypeGameState = GameEngine::ComponentsType::getComponentType("GameState");
    std::vector<size_t> gameStateEntities = componentsContainer.getEntitiesWithComponent(compTypeGameState);
    if (gameStateEntities.empty())
        return;
    auto compMay = componentsContainer.getComponent(gameStateEntities[0], compTypeGameState);
    if (!compMay.has_value())
        return;
    auto gameStateComp = std::static_pointer_cast<Utils::GameState>(compMay.value());
    if (gameStateComp->_state != Utils::GameState::State::WAITING)
        return;
    auto compTypeIsReady = GameEngine::ComponentsType::getComponentType("IsReady");
    std::vector<size_t> isReadyEntities = componentsContainer.getEntitiesWithComponent(compTypeIsReady);
    auto compTypeNetworkClientId = GameEngine::ComponentsType::getComponentType("NetworkClientId");
    std::vector<size_t> networkClientIdEntities = componentsContainer.getEntitiesWithComponent(compTypeNetworkClientId);
    if (isReadyEntities.size() == networkClientIdEntities.size()) {
        gameStateComp->_state = Utils::GameState::State::RUNNING;
        for (auto &entity : isReadyEntities) {
            componentsContainer.unbindComponentFromEntity(entity, compTypeIsReady);
        }
        std::cout << "Game is starting" << std::endl;
        std::vector<size_t> ids = {};
        std::vector<std::any> args = {};
        std::shared_ptr<Network::IMessage> message = std::make_shared<Network::Message>("START_GAME", ids, "", args);
        std::shared_ptr<Network::AllUsersMessage> userMessage = std::make_shared<Network::AllUsersMessage>(message);
        eventHandler.queueEvent("SEND_NETWORK", userMessage);
    }
}