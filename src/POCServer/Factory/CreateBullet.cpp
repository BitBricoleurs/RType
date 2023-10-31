/*
** EPITECH PROJECT, 2023
** RType
** File description:
** CreateNewBullet
*/

#include "EntityFactory.hpp"

namespace Server {

    size_t EntityFactory::createPlayerBullet(GameEngine::ComponentsContainer &container,
                                      GameEngine::EventHandler &eventHandler,
                                      Utils::Vect2 pos, Utils::Vect2 velocity, size_t typeBullet) {

        try {
            LoadConfig::ConfigData data = LoadConfig::LoadConfig::getInstance().loadConfig("config/Entity/createBulletPlayer.json");

            std::string bulletKeyPath = "/createBullet/bulletTypes/type" + std::to_string(typeBullet);

            int rectH = data.getInt(bulletKeyPath + "/rect/h");
            int rectW = data.getInt(bulletKeyPath + "/rect/w");

            size_t entityId = createBullet(
                container,
                rectH,
                rectW,
                pos,
                velocity,
                data.getInt(bulletKeyPath + "/damageValue"),
                data.getBool("/createBullet/isPlayerBullet"),
                data.getFloat("/createBullet/scale")
            );

            std::vector<size_t> ids = {entityId};
            std::vector<std::any> args = {static_cast<int>(BulletOwner::PLAYER)};
            if (typeBullet == 0) {
                args.emplace_back(static_cast<int>(BulletType::NORMAL));
            } else if (typeBullet >= 1) {
                args.emplace_back(static_cast<int>(BulletType::CHARGED));
            }
            args.emplace_back(static_cast<int>(pos.x * 1000));
            args.emplace_back(static_cast<int>(pos.y * 1000));
            args.emplace_back(static_cast<int>(velocity.x * 1000));
            args.emplace_back(static_cast<int>(velocity.y * 1000));
            args.emplace_back(static_cast<int>(typeBullet));
            std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("CREATED_BULLET", ids, "INT", args);
            std::shared_ptr<Network::AllUsersMessage> allUserMsg = std::make_shared<Network::AllUsersMessage>(message);
            eventHandler.queueEvent("SEND_NETWORK", allUserMsg);
            return entityId;
        } catch(const std::runtime_error& e) {
            std::cerr << "Error in createPlayerBullet: " << e.what() << std::endl;
            exit(1);
        }
    }

    size_t
    EntityFactory::createBaseEnemyBullet(GameEngine::ComponentsContainer &container,
                                         GameEngine::EventHandler &eventHandler,
                                         Utils::Vect2 pos, Utils::Vect2 velocity)
                                         {
        try {
            LoadConfig::ConfigData data = LoadConfig::LoadConfig::getInstance().loadConfig("config/Entity/createBulletEnemy.json");

            size_t entityId = createBullet(
                container,
                data.getInt("/createBullet/spriteSheetHeight"),
                data.getInt("/createBullet/spriteSheetWidth"),
                pos,
                velocity,
                data.getInt("/createBullet/damageValue"),
                data.getBool("/createBullet/isPlayerBullet"),
                data.getFloat("/createBullet/scale")
            );

            std::vector<size_t> ids = {entityId};
            std::vector<std::any> args = {static_cast<int>(BulletOwner::ENEMY)};
            args.emplace_back(static_cast<int>(BulletType::NORMAL));
            args.emplace_back(static_cast<int>(pos.x * 1000));
            args.emplace_back(static_cast<int>(pos.y * 1000));
            args.emplace_back(static_cast<int>(velocity.x * 1000));
            args.emplace_back(static_cast<int>(velocity.y * 1000));
            args.emplace_back(static_cast<int>(0));
            std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("CREATED_BULLET", ids, "INT", args);
            std::shared_ptr<Network::AllUsersMessage> allUserMsg = std::make_shared<Network::AllUsersMessage>(message);
            eventHandler.queueEvent("SEND_NETWORK", allUserMsg);
            return entityId;
          return entityId;
        } catch(const std::runtime_error& e) {
            std::cerr << "Error in createBaseEnemyBullet: " << e.what() << std::endl;
            exit(1);
        }
    }
}
