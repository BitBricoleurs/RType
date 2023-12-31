//
// Created by alexandre on 30/10/23.
//

#include "ManagePowerUp.hpp"

void Server::ManagePowerUp::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    try {
        int id = static_cast<int>(std::any_cast<size_t>(eventHandler.getTriggeredEvent().second));

        auto playerType = GameEngine::ComponentsType::getComponentType("IsPlayer");

        auto playerOpt = componentsContainer.getComponent(id, playerType);
        if (!playerOpt.has_value())
            return;

        auto player = std::static_pointer_cast<IsPlayer>(playerOpt.value());

        try {
            LoadConfig::ConfigData data = LoadConfig::LoadConfig::getInstance().loadConfig("config/Game/powerUp.json");
            auto event = data.getString("/powers/" + std::to_string(player->PowerUp) + "/name");
            auto delay = data.getInt("/powers/" + std::to_string(player->PowerUp) + "/delay");
            eventHandler.scheduleEvent(event, delay, id);
            player->PowerUp++;
            if (player->PowerUp == 1 || player->PowerUp == 2) {
                std::vector<size_t> ids = {};
                std::vector<std::any> args = {id, player->PowerUp};
                std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("FORCE_POD_UPGRADE", ids, "INT", args);
                std::shared_ptr<Network::AllUsersMessage> allUserMsg = std::make_shared<Network::AllUsersMessage>(message);
                eventHandler.queueEvent("SEND_NETWORK", allUserMsg);
            }
        } catch (std::exception &e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    } catch (const std::bad_any_cast &e) {
        std::cout << "Error in ManagePowerUp : " << e.what() << std::endl;
    }
}
