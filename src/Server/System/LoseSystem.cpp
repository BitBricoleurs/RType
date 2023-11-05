//
// Created by clagasse on 11/1/23.
//

#include "LoseSystem.hpp"

void Server::LoseSystem::update(GameEngine::ComponentsContainer &componentsContainer,
                                GameEngine::EventHandler &eventHandler)
{
    eventHandler.queueEvent("RESET_LEVEL");
    eventHandler.queueEvent("REVIVE_PLAYER");
    auto compTypeGameState = GameEngine::ComponentsType::getComponentType("GameState");
    size_t gameStateEntity = componentsContainer.getEntityWithUniqueComponent(compTypeGameState);
    auto compMay = componentsContainer.getComponent(gameStateEntity, compTypeGameState);
    if (!compMay.has_value())
        return;
    auto gameStateComp = std::static_pointer_cast<Utils::GameState>(compMay.value());
    gameStateComp->_state = Utils::GameState::State::LOSE;
    std::cout << "All players are dead" << std::endl;
    std::vector<size_t> ids = {};
    std::vector<std::any> args = {static_cast<int>(Utils::GameState::State::LOSE)};
    std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("GAME_OVER", ids, "INT", args);
    std::shared_ptr<Network::AllUsersMessage> allMessage = std::make_shared<Network::AllUsersMessage>(message);
    eventHandler.queueEvent("SEND_NETWORK", allMessage);
    eventHandler.scheduleEvent("GO_BACK_TO_THE_LOBBY", 400, std::any(), 1);
    eventHandler.queueEvent("DELETE_MOBS");
    eventHandler.queueEvent("DELETE_PARALLAX");
    eventHandler.queueEvent("DELETE_POWER_UP");
}