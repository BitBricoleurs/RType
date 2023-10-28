/*
** EPITECH PROJECT, 2023
** RType
** File description:
** CreatePowerUp
*/

#include "EntityFactory.hpp"

namespace Server {

    size_t EntityFactory::spawnPowerUp(GameEngine::ComponentsContainer &container,
                                             GameEngine::EventHandler &eventHandler,
                                             Utils::Vect2 pos, PowerUpType type) {

        try {
            LoadConfig::ConfigData data = LoadConfig::LoadConfig::getInstance().loadConfig("config/Entity/createPowerUp.json");

            int size = data.getSize("/powers");
            for (int i = 0; i < size; i++) {
                PowerUpType typeTab = static_cast<PowerUpType>(data.getInt("/powers/" + std::to_string(i) + "/type"));
                if (typeTab == type) {
                    int hitBoxHeight = data.getInt("/powers/" + std::to_string(i) + "/hitBoxHeight");
                    int hitBoxWidth = data.getInt("/powers/" + std::to_string(i) + "/hitBoxWidth");
                    float scale = data.getFloat("/powers/" + std::to_string(i) + "/scale");
                    auto velocity = Utils::Vect2(0, 0);
                    size_t entityId = createBaseEntity(
                        container,
                        hitBoxHeight,
                        hitBoxWidth,
                        pos,
                        velocity,
                        scale
                    );

                    container.bindComponentToEntity(entityId, std::make_shared<IsPower>(type));
                    std::vector<size_t> ids = {entityId};
                    std::vector<std::any> args = {static_cast<int>(type)};
                    std::cout << "Create PowerUp" << std::endl;
                    std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("CREATED_POWERUP", ids, "INT", args);
                    std::shared_ptr<Network::AllUsersMessage> allUserMsg = std::make_shared<Network::AllUsersMessage>(message);
                    eventHandler.queueEvent("SEND_NETWORK", allUserMsg);
                    EntityFactory::updateEntityNetwork(eventHandler, entityId, pos, velocity);

                return entityId;
                }
            }
            return 0;
        } catch(const std::runtime_error& e) {
                std::cerr << "Error in spawnPowerUp: " << e.what() << std::endl;
                exit(1);
        }
    }
}
