#include "EntityFactory.hpp"

namespace Client {

    size_t EntityFactory::createPlayerBullet(GameEngine::ComponentsContainer &container, GameEngine::EventHandler &eventHandler, Utils::Vect2 pos, Utils::Vect2 velocity, size_t typeBullet) {
        try {
            LoadConfig::ConfigData data = LoadConfig::LoadConfig::getInstance().loadConfig("config/Entity/createBulletPlayer.json");

            std::string bulletKeyPath = "/createBullet/bulletTypes/type" + std::to_string(typeBullet);

            int spriteSheetHeight = data.getInt(bulletKeyPath + "/spriteSheetDimensions/h");
            int spriteSheetWidth = data.getInt(bulletKeyPath + "/spriteSheetDimensions/w");
            std::string path = data.getString(bulletKeyPath + "/path");
            size_t entityId = createBullet(
                container,
                path,
                spriteSheetHeight,
                spriteSheetWidth,
                data.getInt(bulletKeyPath + "/frames"),
                data.getBool("/createBullet/twoDirections"),
                data.getBool("/createBullet/reverse"),
                pos,
                velocity,
                data.getBool("/createBullet/isPlayerBullet"),
                data.getInt("/createBullet/playerA"),
                data.getFloat("/createBullet/scale"),
                data.getFloat("/createBullet/rotation"),
                Utils::ColorR(
                    data.getInt("/createBullet/tint/r"),
                    data.getInt("/createBullet/tint/g"),
                    data.getInt("/createBullet/tint/b"),
                    data.getInt("/createBullet/tint/a")
                ),
                data.getInt("/createBullet/layer")
            );

            if (typeBullet > 0) {
                eventHandler.scheduleEvent(
                    "animate", 10, std::make_tuple(std::string("PlayerBullet"), entityId));
            }

            return entityId;
        } catch(const std::runtime_error& e) {
            std::cerr << "Error in createPlayerBullet: " << e.what() << std::endl;
            exit(1);
        }
    }

    size_t
    EntityFactory::createBaseEnemyBullet(GameEngine::ComponentsContainer &container,
                                         GameEngine::EventHandler &eventHandler,
                                         Utils::Vect2 pos, Utils::Vect2 velocity) {
        try {
            LoadConfig::ConfigData data = LoadConfig::LoadConfig::getInstance().loadConfig("config/Entity/createBulletEnemy.json");

            size_t entityId = createBullet(
                container,
                data.getString("/createBullet/spriteSheetPath"),
                data.getInt("/createBullet/spriteSheetHeight"),
                data.getInt("/createBullet/spriteSheetWidth"),
                data.getInt("/createBullet/frames"),
                data.getBool("/createBullet/twoDirections"),
                data.getBool("/createBullet/reverse"),
                pos,
                velocity,
                data.getBool("/createBullet/isPlayerBullet"),
                data.getInt("/createBullet/playerA"),
                data.getFloat("/createBullet/scale"),
                data.getFloat("/createBullet/rotation"),
                Utils::ColorR(
                    data.getInt("/createBullet/tint/r"),
                    data.getInt("/createBullet/tint/g"),
                    data.getInt("/createBullet/tint/b"),
                    data.getInt("/createBullet/tint/a")
                ),
                data.getInt("/createBullet/layer")
            );

            eventHandler.scheduleEvent(
                "animate", 10, std::make_tuple(std::string("EnemyBullet"), entityId));

            return entityId;
        } catch(const std::runtime_error& e) {
            std::cerr << "Error in createBaseEnemyBullet: " << e.what() << std::endl;
            exit(1);
        }
    }

}

