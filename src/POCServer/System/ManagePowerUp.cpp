//
// Created by alexandre on 30/10/23.
//

#include "ManagePowerUp.hpp"

void Server::ManagePowerUp::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    auto id = std::any_cast<size_t>(eventHandler.getTriggeredEvent().second);

    auto player = std::dynamic_pointer_cast<IsPlayer>(componentsContainer.getComponent(id, GameEngine::ComponentsType::getComponentType("IsPlayer")).value());
    LoadConfig::ConfigData data = LoadConfig::LoadConfig::getInstance().loadConfig("config/Game/powerUp.json");
    auto event = data.getString("powers/" + std::to_string(PowerUp) + "/name");
    auto delay = data.getInt("powers/" + std::to_string(PowerUp) + "/delay");
    eventHandler.scheduleEvent(event, delay, id);
}
