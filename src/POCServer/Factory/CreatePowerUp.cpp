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
                    args.emplace_back(static_cast<int>(pos.x * 1000));
                    args.emplace_back(static_cast<int>(pos.y * 1000));
                    args.emplace_back(static_cast<int>(velocity.x) * 1000);
                    args.emplace_back(static_cast<int>(velocity.y) * 1000);
                    std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("CREATED_POWERUP", ids, "INT", args);
                    std::shared_ptr<Network::AllUsersMessage> allUserMsg = std::make_shared<Network::AllUsersMessage>(message);
                    eventHandler.queueEvent("SEND_NETWORK", allUserMsg);
                return entityId;
                }
            }
            return 0;
        } catch(const std::runtime_error& e) {
                std::cerr << "Error in spawnPowerUp: " << e.what() << std::endl;
                exit(1);
        }
    }

    std::vector<size_t> EntityFactory::spawnPowersDualShoot(GameEngine::ComponentsContainer &container,
                                             GameEngine::EventHandler &eventHandler,
                                             PowerType type, Utils::Vect2 pos, Utils::Vect2 pos2)
                                             {
    try {

        LoadConfig::ConfigData data = LoadConfig::LoadConfig::getInstance().loadConfig("config/Game/powerUp.json");
        int size = data.getSize("/powers");
        for (int i = 0; i < size; i++) {
            auto typeJson = static_cast<PowerType>(data.getInt("/powers/" + std::to_string(i) + "/type"));
            if (type == typeJson) {
                int hitBoxHeight = data.getInt("/powers/" + std::to_string(i) + "/shootRed/hitBoxHeight");
                int hitBoxWidth = data.getInt("/powers/" + std::to_string(i) + "/shootRed/hitBoxWidth");
                float scale = data.getFloat("/powers/" + std::to_string(i) + "/shootRed/scale");
                auto velocity = Utils::Vect2(data.getFloat("/powers/" + std::to_string(i) + "/shootRed/velocity/x"), data.getFloat("powers/" + std::to_string(i) + "/shootRed/velocity/y"));
                int damageValue = data.getInt("/powers/" + std::to_string(i) + "/shootRed/damageValue");
                bool isPlayerBullet = data.getBool("/powers/" + std::to_string(i) + "/shootRed/isPlayerBullet");
                size_t entityId = createBullet(
                    container,
                    hitBoxHeight,
                    hitBoxWidth,
                    pos,
                    velocity,
                    damageValue,
                    isPlayerBullet,
                    scale
                );
                hitBoxHeight = data.getInt("/powers/" + std::to_string(i) + "/shootBlue/hitBoxHeight");
                hitBoxWidth = data.getInt("/powers/" + std::to_string(i) + "/shootBlue/hitBoxWidth");
                scale = data.getFloat("/powers/" + std::to_string(i) + "/shootBlue/scale");
                velocity = Utils::Vect2(data.getFloat("/powers/" + std::to_string(i) + "/shootBlue/velocity/x"), data.getFloat("powers/" + std::to_string(i) + "/shootBlue/velocity/y"));
                damageValue = data.getInt("/powers/" + std::to_string(i) + "/shootBlue/damageValue");
                isPlayerBullet = data.getBool("/powers/" + std::to_string(i) + "/shootBlue/isPlayerBullet");
                size_t entityId2 = createBullet(
                    container,
                    hitBoxHeight,
                    hitBoxWidth,
                    pos,
                    velocity,
                    damageValue,
                    isPlayerBullet,
                    scale
                );
                std::vector<size_t> ids = {entityId, entityId2};
                std::vector<std::any> args = {static_cast<int>(type)};
                args.emplace_back(static_cast<int>(pos.x * 1000));
                args.emplace_back(static_cast<int>(pos.y * 1000));
                args.emplace_back(static_cast<int>(pos2.x) * 1000);
                args.emplace_back(static_cast<int>(pos2.y) * 1000);
                std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("CREATED_POWERUP_DUAL", ids, "INT", args);
                std::shared_ptr<Network::AllUsersMessage> allUserMsg = std::make_shared<Network::AllUsersMessage>(message);
                eventHandler.queueEvent("SEND_NETWORK", allUserMsg);
                return {entityId, entityId2};
            }
        }
    } catch (const std::runtime_error& e) {
        std::cerr << "Error in spawnPowersDualShoot: " << e.what() << std::endl;
        exit(1);

    }
    return {};
    }


}
