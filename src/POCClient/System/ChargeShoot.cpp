//
// Created by Theophilus Homawoo on 12/10/2023.
//

#include "ChargeShoot.hpp"

void ChargeShoot::update(GameEngine::ComponentsContainer& componentsContainer, GameEngine::EventHandler& eventHandler)
{
    std::vector<size_t> ids = {};
    std::vector<std::any> args = {};
    std::shared_ptr<Network::IMessage> message = std::make_shared<Network::Message>("CHARGE_SHOOT", ids, "", args);
    eventHandler.queueEvent("SEND_NETWORK", message);
}
