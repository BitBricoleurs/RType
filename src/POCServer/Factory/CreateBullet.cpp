/*
** EPITECH PROJECT, 2023
** RType
** File description:
** CreateNewBullet
*/

#include "EntityFactory.hpp"

size_t
EntityFactory::createPlayerBullet(GameEngine::ComponentsContainer &container,
                                  GameEngine::EventHandler &eventHandler,
                                  GameEngine::Vect2 pos, GameEngine::Vect2 velocity, size_t typeBullet ) {

    try {
        ConfigData data = LoadConfig::getInstance().loadConfig("config/Entity/createBulletPlayer.json");

        std::string bulletKeyPath = "/createBullet/bulletTypes/type" + std::to_string(typeBullet) + "/rect";

        int rectH = data.getInt(bulletKeyPath + "/h");
        int rectW = data.getInt(bulletKeyPath + "/w");

        size_t entityId = createBullet(
            container,
            rectH,
            rectW,
            pos,
            velocity,
            data.getInt("/createBullet/damageValue"),
            data.getBool("/createBullet/isPlayerBullet"),
            data.getFloat("/createBullet/scale")
        );

        std::vector<size_t> ids = {entityId};
        std::vector<std::any> args = {static_cast<int>(BulletOwner::PLAYER)};
        if (typeBullet == 0) {
            args.push_back(static_cast<int>(BulletType::NORMAL));
        } else if (typeBullet == 1) {
            args.push_back(static_cast<int>(BulletType::CHARGED));
        }
        std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("CREATED_BULLET", ids, "INT", args);
        std::shared_ptr<Network::AllUsersMessage> allUserMsg = std::make_shared<Network::AllUsersMessage>(message);
        eventHandler.queueEvent("SEND_NETWORK", allUserMsg);
        EntityFactory::updateEntityNetwork(eventHandler, entityId, pos, velocity);
        return entityId;
    } catch(const std::runtime_error& e) {
        std::cerr << "Error in createPlayerBullet: " << e.what() << std::endl;
        exit(1);
    }
}

size_t
EntityFactory::createBaseEnemyBullet(GameEngine::ComponentsContainer &container,
                                     GameEngine::EventHandler &eventHandler,
                                     GameEngine::Vect2 pos, GameEngine::Vect2 velocity)
                                     {
    try {
        ConfigData data = LoadConfig::getInstance().loadConfig("config/Entity/createBulletEnemy.json");

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
      return entityId;
    } catch(const std::runtime_error& e) {
        std::cerr << "Error in createBaseEnemyBullet: " << e.what() << std::endl;
        exit(1);
    }
}
