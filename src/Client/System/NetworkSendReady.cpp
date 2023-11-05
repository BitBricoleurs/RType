//
// Created by Clément Lagasse on 23/10/2023.
//

#include "NetworkSendReady.hpp"

void Client::NetworkSendReady::update(GameEngine::ComponentsContainer &componentsContainer,
                                      GameEngine::EventHandler &eventHandler)
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
    std::vector<size_t> ids = {};
    std::vector<std::any> args = {};
    std::shared_ptr<Network::IMessage> message = std::make_shared<Network::Message>("READY", ids, "", args);
    eventHandler.queueEvent("SEND_NETWORK", message);
    eventHandler.queueEvent("CLEAR_NOTIF_PLAY");
}