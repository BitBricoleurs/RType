//
// Created by clagasse on 11/1/23.
//

#include "RevivePlayer.hpp"

namespace Server {

    void RevivePlayer::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
    {
        auto playerCompType = GameEngine::ComponentsType::getComponentType("IsPlayer");
        auto players = componentsContainer.getEntitiesWithComponent(playerCompType);
        auto healthCompType = GameEngine::ComponentsType::getComponentType("Health");
        auto userGameModeType = GameEngine::ComponentsType::getComponentType("UserGameMode");

        std::vector<size_t> ids;
        std::vector<std::any> args;
        for (auto player : players) {
            auto maybeHealth = componentsContainer.getComponent(player, healthCompType);
            if (!maybeHealth.has_value())
                continue;
            auto health = std::static_pointer_cast<Server::Health>(maybeHealth.value());
            health->currentHealth = health->maxHealth;
            health->lives = 3;
            ids.push_back(player);
            args.emplace_back(health->currentHealth);
            auto maybeUserGameMode = componentsContainer.getComponent(player, userGameModeType);
            if (!maybeUserGameMode.has_value())
                continue;
            auto userGameMode = std::static_pointer_cast<Utils::UserGameMode>(maybeUserGameMode.value());
            userGameMode->_state = Utils::UserGameMode::State::ALIVE;
        }
        std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("REVIVE_PLAYER", ids, "INT", args);
        std::shared_ptr<Network::AllUsersMessage> allMessage = std::make_shared<Network::AllUsersMessage>(message);
        eventHandler.queueEvent("SEND_NETWORK", allMessage);
    }
}