//
// Created by Theophilus Homawoo on 12/10/2023.
//

#include "ChargeShoot.hpp"

void ChargeShoot::update(GameEngine::ComponentsContainer& componentsContainer, GameEngine::EventHandler& eventHandler)
{
    BulletTypeEntity type = BulletTypeEntity::PlayerBullet;
    std::vector<size_t> ids = {};
    std::vector<std::any> args = {static_cast<int>(type), 0};
    std::shared_ptr<Network::IMessage> message = std::make_shared<Network::Message>("CHARGE_SHOOT", ids, "INT", args);
    eventHandler.queueEvent("SEND_NETWORK", message);
}
